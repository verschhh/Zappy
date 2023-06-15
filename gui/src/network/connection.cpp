/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** connection.cpp
*/

#include "../../includes/network.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

zappy::Connection::Connection(int port, std::string machine) : _sockfd(-1), _port(port), _machine(machine)
{
    std::memset(&_serverAddress, 0, sizeof(_serverAddress));
    _serverAddress.sin_family = AF_INET;
    _serverAddress.sin_port = htons(_port);
    _serverAddress.sin_addr.s_addr = inet_addr(_machine.c_str());
}

zappy::Connection::~Connection()
{
    disconnect();
}

void zappy::Connection::connect()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1) {
        throw std::runtime_error("Error: Failed to create socket");
    }

    // Connect to the server
    int connectionResult = ::connect(_sockfd, reinterpret_cast<struct sockaddr*>(&_serverAddress), sizeof(_serverAddress));
    if (connectionResult == -1) {
        throw std::runtime_error("Error: Failed to connect to the server");
    }
}

void zappy::Connection::disconnect()
{
    if (_sockfd != -1) {
        close(_sockfd);
        _sockfd = -1;
    }
}

void zappy::Connection::send(const std::string& message)
{
    if (_sockfd == -1) {
        throw std::runtime_error("Error: Cannot send message, not connected to the server");
    }

    int sendResult = ::send(_sockfd, message.c_str(), message.size(), 0);
    if (sendResult == -1) {
        throw std::runtime_error("Error: Failed to send message to the server");
    }
}

std::string zappy::Connection::receive()
{
    if (_sockfd == -1) {
        throw std::runtime_error("Error: Not connected to the server");
    }

    const int bufferSize = 1024;  // Adjust the buffer size as needed
    char buffer[bufferSize];
    int bytesRead = ::recv(_sockfd, buffer, bufferSize - 1, 0);

    if (bytesRead == -1) {
        // Error occurred while receiving
        throw std::runtime_error("Error: Failed to receive data from the server");
    } else if (bytesRead == 0) {
        // Connection closed by the server
        throw std::runtime_error("Error: Connection closed by the server");
    } else {
        // Data received successfully
        buffer[bytesRead] = '\0';  // Null-terminate the received data
        return std::string(buffer);
    }
}
