//
// Created by mati on 30/9/19.
//

#include "common_acceptor.h"


common_acceptor::common_acceptor(common_ftp *ftp, Socket *skt) {
    this->skt = skt;
    this->ftp = ftp;
}

void common_acceptor::run() {
    while (!exit) {
        Socket *sktAccepted = new Socket();
        *sktAccepted = this->skt->accept();

        common_proxy_client *client;
        client = new common_proxy_client(this->ftp, sktAccepted);
        client->start();

        this->clients.push_back(client);

        for (int i = 0; i < (int) this->clients.size(); i++) {
            if (this->clients[i]->is_dead()) {
                this->clients[i]->join();
                delete this->clients[i];
            }
        }
    }
}

void common_acceptor::stop() {
    for (int i = 0; i < (int) this->clients.size(); i++) {
        this->clients[i]->stop();
        this->clients[i]->join();
        delete this->clients[i];
    }
    this->exit = true;
    this->skt->shutdown();
}

common_acceptor::~common_acceptor() {}
