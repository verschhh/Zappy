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
    std::cout << "___________________________" << std::endl;
    std::cout << "Response: " << response << std::endl;
    std::cout << "___________________________" << std::endl;

    std::vector<std::string> lines = splitString(response, '\n');

    std::string cmd;
    std::cout << "before selection" << std::endl;
    for (const std::string& line : lines) {
    std::vector<std::string> arguments = splitString(line, ' ');

        if (!arguments.empty()) {
            std::string cmd = arguments[0];
            std::cout << "line: " << line << std::endl;

            if (cmd == "pnw") { // Connection of new player
                std::cout << "pnw command" << std::endl;
                pnwHandler(arguments);
            }
            else if (cmd == "enw") { // Egg laid by player
                std::cout << "enw command" << std::endl;
                command2Handler(arguments);
            }
            else if (cmd == "ebo") { // Egg hatched
                std::cout << "ebo command" << std::endl;
                command3Handler(arguments);
            }
            else if (cmd == "pdi") { // Player died
                std::cout << "pdi command" << std::endl;
            }
            else if (cmd == "seg") { // End of game
                std::cout << "seg command" << std::endl;
            }
            else { // Unknown command
                std::cout << "Unknown command" << std::endl;
            }
        }
    }
}
