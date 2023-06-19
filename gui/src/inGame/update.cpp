/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update.cpp
*/

#include "../../includes/scenes.hpp"
#include "../../includes/messageHandler.hpp"
#include <iostream>

void zappy::InGame::updateScene(void)
{
    std::cout << "Update scene" << std::endl;

    updateMap();
    parseQueue();
}

void zappy::InGame::updateMap(void)
{
    std::cout << "Update map" << std::endl;

    std::string command = "mct\n";
    _connection.send(command);

    int mctBufferSize = _mapHeight * _mapWidth * MAX_BCT_SIZE;
    std::string response = _connection.receive(mctBufferSize);

    std::vector<std::string> lines = splitString(response, '\n');

    MessageHandler handler;
    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            handler.handleBctMessage(lines[i * _mapWidth + j], _map);
        }
    }
}

void zappy::InGame::parseQueue(void)
{
    std::cout << "Parse queue" << std::endl;

    std::string command = "queue\n";
    _connection.send(command);

    int maxBufferSize = 1000;

    std::string response = _connection.receive(maxBufferSize);
    std::cout << "Response: " << response << std::endl;
}
