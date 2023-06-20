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
    updatePnj();
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

void zappy::InGame::updatePnj(void)
{
    int numberPnj = _pnjs.size();

    for (int i = 0; i < numberPnj; i++) {
        // send command ppo & update position
        std::string posCommand = "ppo #" + std::to_string(_pnjs[i].number) + "\n";
        _connection.send(posCommand);

        int maxBufferSize = 1024;
        std::string response = _connection.receive(maxBufferSize);

        std::vector<std::string> arguments = splitString(response, ' ');
        int newX = std::stoi(arguments[2]);
        int newY = std::stoi(arguments[3]);

        std::cout << "New position: " << newX << " " << newY << std::endl;

        _pnjs[i].position = sf::Vector2f(newX, newY);

        // send command plv & update level
        std::string levelCommand = "plv #" + std::to_string(_pnjs[i].number) + "\n";

        _connection.send(levelCommand);

        response = _connection.receive(maxBufferSize);

        arguments = splitString(response, ' ');

        int newLevel = std::stoi(arguments[2]);

        std::cout << "New level: " << newLevel << std::endl;

        _pnjs[i].level = newLevel;
    }
}
