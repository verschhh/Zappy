/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** connection.hpp
*/

#pragma once

#include <string>
#include <netinet/in.h>

namespace zappy {
    class Connection {
        public:
            Connection(int port, std::string machine);
            ~Connection();

            void connect();
            void disconnect();
            void send(const std::string& message);
            std::string receive();

        private:
            int _sockfd;
            int _port;
            std::string _machine;
            struct sockaddr_in _serverAddress;
    };
}
