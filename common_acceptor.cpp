//
// Created by mati on 30/9/19.
//

#include "common_acceptor.h"
#include "Except.h"

/** Constructor
 *  @param ftp reference to ftp object
 *  @param skt reference of socket server
 */
common_acceptor::common_acceptor(common_ftp *ftp, Socket &skt): skt(skt) {
    this->ftp = ftp;
}

void common_acceptor::run() {
    try {
        while (!exit) {
            Socket socket;
            socket = this->skt.accept();
            common_proxy_client *client;
            client = new common_proxy_client(this->ftp, std::move(socket));
            client->start();
            this->clients.push_back(client);

            for (int i = 0; i < (int) this->clients.size(); i++) {
                if (this->clients[i]->is_dead()) {
                    this->clients[i]->join();
                    delete this->clients[i];
                }
            }
        }
    } catch (...) {} //skt accept exception
}

void common_acceptor::stop() {
    for (int i = 0; i < (int) this->clients.size(); i++) {
        this->clients[i]->stop();
        this->clients[i]->join();
        delete this->clients[i];
    }
    this->exit = true;
}

common_acceptor::~common_acceptor() = default;
