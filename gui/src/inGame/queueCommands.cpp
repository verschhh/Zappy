/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** queueCommands.cpp
*/

#include "../../includes/scenes.hpp"
#include "../../includes/messageHandler.hpp"
#include <iostream>

void zappy::InGame::pnwHandler(std::vector<std::string>& arguments)
{
    if (arguments.size() != 7)
        throw AScene::SceneException("Error: pnw command has wrong number of arguments");

    int number = std::stoi(arguments[1].substr(1));
    int x = std::stoi(arguments[2]);
    int y = std::stoi(arguments[3]);
    pnjOrientation orientation = static_cast<pnjOrientation>(std::stoi(arguments[4]));
    int level = std::stoi(arguments[5]);

    createPnj(number, x, y, orientation, level);
}

void zappy::InGame::command2Handler(std::vector<std::string>& arguments)
{
    std::cout << "Command 2 handler" << std::endl;
    for (const std::string& arg : arguments) {
        std::cout << arg << std::endl;
    }
}

void zappy::InGame::command3Handler(std::vector<std::string>& arguments)
{
    std::cout << "Command 3 handler" << std::endl;
    for (const std::string& arg : arguments) {
        std::cout << arg << std::endl;
    }
}
