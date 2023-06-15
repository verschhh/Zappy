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
    // Receive message from serv
    // if !message, skip function
    // else, parse message

    std::string message = _connection.receive();
    std::cout << "Message received: " << message << std::endl;
    if (message.empty()) {
        return;
    } else {
        std::cout << "Message received: " << message << std::endl;
    }
}
