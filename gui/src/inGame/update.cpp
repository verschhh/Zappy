/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update.cpp
*/

#include "../../includes/scenes.hpp"
#include <iostream> //! TEMP

void zappy::InGame::updateScene(void)
{
    std::cout << "update scene" << std::endl;
    // TODO:
    // Send mct to get all map content
    // Parse mct message
    // Update map

    std::string command = "mct\n";
    _connection.send(command);

    int mctBufferSize = _mapHeight * _mapWidth * MAX_BCT_SIZE;
    std::string response = _connection.receive(mctBufferSize);
    std::cout << "response: " << response << std::endl;
}
