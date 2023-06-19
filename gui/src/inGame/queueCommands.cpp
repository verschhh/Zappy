/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** queueCommands.cpp
*/

#include "../../includes/scenes.hpp"
#include "../../includes/messageHandler.hpp"
#include <iostream>

void zappy::InGame::command1Handler(std::vector<std::string>& arguments)
{
    std::cout << "Command 1 handler" << std::endl;
    for (const std::string& arg : arguments) {
        std::cout << arg << std::endl;
    }
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
