/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update.cpp
*/

#include "../../includes/gui.hpp"
#include "../../includes/messageHandler.hpp"

void zappy::InGame::updateScene(void)
{
    updateMap();
    parseQueue();
    updatePnj();
    updateStats();
}

void zappy::InGame::updateMap(void)
{
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
    std::string command = "queue\n";
    _connection.send(command);

    int maxBufferSize = 1000;

    std::string response = _connection.receive(maxBufferSize);

    std::vector<std::string> lines = splitString(response, '\n');

    std::string cmd;
    for (const std::string& line : lines) {
    std::vector<std::string> arguments = splitString(line, ' ');

        if (!arguments.empty()) {
            std::string cmd = arguments[0];
            std::cout << "line: " << line << std::endl;

            if (cmd == "pnw") { // Connection of new player
                pnwHandler(arguments);
            }
            else if (cmd == "enw") { // Egg laid by player
                enwHandler(arguments);
            }
            else if (cmd == "ebo") { // Egg hatched
                eboHandler(arguments);
            }
            else if (cmd == "pdi") { // Player died
                pdiHandler(arguments);
            }
            else if (cmd == "seg") { // End of game
                segHandler(arguments);
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

        if (response == "ko\n") {
            std::cout << "Player " << _pnjs[i].number << " died" << std::endl;
            erasePnj(_pnjs[i].number);
            return;
        }

        std::vector<std::string> arguments = splitString(response, ' ');
        int newX = std::stoi(arguments[2]);
        int newY = std::stoi(arguments[3]);


        _pnjs[i].position = sf::Vector2f(newX, newY);

        // send command plv & update level
        std::string levelCommand = "plv #" + std::to_string(_pnjs[i].number) + "\n";

        _connection.send(levelCommand);

        response = _connection.receive(maxBufferSize);

        if (response == "ko\n") {
            std::cout << "Player " << _pnjs[i].number << " died" << std::endl;
            erasePnj(_pnjs[i].number);
            return;
        }

        arguments = splitString(response, ' ');

        int newLevel = std::stoi(arguments[2]);

        _pnjs[i].level = newLevel;
    }
}

void zappy::InGame::updateStats(void)
{
    int numberPnj = _pnjs.size();

    int nbFood = 0;
    int nbLinemate = 0;
    int nbDeraumere = 0;
    int nbSibur = 0;
    int nbMendiane = 0;
    int nbPhiras = 0;
    int nbThystame = 0;

    for (int i = 0; i < _mapHeight; i++) {
        for (int j = 0; j < _mapWidth; j++) {
            nbFood += _map[i][j].content.quantity.food;
            nbLinemate += _map[i][j].content.quantity.linemate;
            nbDeraumere += _map[i][j].content.quantity.deraumere;
            nbSibur += _map[i][j].content.quantity.sibur;
            nbMendiane += _map[i][j].content.quantity.mendiane;
            nbPhiras += _map[i][j].content.quantity.phiras;
            nbThystame += _map[i][j].content.quantity.thystame;
        }
    }

    _stats->setPnjCounter(numberPnj);
    _stats->setFoodCounter(nbFood);
    _stats->setLinemateCounter(nbLinemate);
    _stats->setDeraumereCounter(nbDeraumere);
    _stats->setSiburCounter(nbSibur);
    _stats->setMendianeCounter(nbMendiane);
    _stats->setPhirasCounter(nbPhiras);
    _stats->setThystameCounter(nbThystame);
}
