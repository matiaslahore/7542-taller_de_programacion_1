//
// Created by mati on 25/9/19.
//

#include "common_proxy_client.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <string>

common_proxy_client::common_proxy_client(common_ftp *ftp, Socket *skt)
        : protocol(ftp) {
    this->ftp = ftp;
    this->skt = skt;
    this->exit = false;
}

void common_proxy_client::run() {
    std::string response;

    while (!exit) {
        response = this->receive();
        this->send(response);
    }
}

std::string common_proxy_client::receive() {
    std::vector<char> response(MAX_RECV);
    this->skt->receive(response.data(), MAX_RECV);

    int i = 0;
    for (; i < (int) response.size(); i++)
        if (response[i] == '\0') response.resize(i);

    int command_len = this->get_command_len(response);
    std::string command(response.begin(), response.begin() + command_len);

    return this->protocol.executeCommand(command, response);
}

void common_proxy_client::send(const std::string &response) {
    this->skt->send(response.c_str(), strlen(response.c_str()));
}

int common_proxy_client::get_command_len(std::vector<char> &response) {
    if (response.size() < 4) return 3;

    for (int i = 0; i < (int) response.size(); i++)
        if (response[i] == ' ') return i;

    return 4;
}

bool common_proxy_client::is_dead() {
    return this->exit;
}

void common_proxy_client::stop() {
    this->skt->shutdown();
    this->exit = true;
}

common_proxy_client::~common_proxy_client() {
    if (!this->exit)
        this->skt->shutdown();
    delete this->skt;
}
