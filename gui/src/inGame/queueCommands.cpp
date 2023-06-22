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

void zappy::InGame::enwHandler(std::vector<std::string>& arguments)
{
    for (const std::string& arg : arguments) {
        std::cout << arg << std::endl;
    }
}

void zappy::InGame::eboHandler(std::vector<std::string>& arguments)
{
    for (const std::string& arg : arguments) {
        std::cout << arg << std::endl;
    }
}

void zappy::InGame::pdiHandler(std::vector<std::string>& arguments)
{
    if (arguments.size() != 2)
        throw AScene::SceneException("Error: pdi command has wrong number of arguments");

    int number = std::stoi(arguments[1]);
    std::cout << "Pdi handler: player " << number << " died" << std::endl;

    // int nbPnj = _pnjs.size();
    for (auto it = _pnjs.begin(); it != _pnjs.end(); ++it) {
        if (it->number == number) {
            std::cout << "DELETE HERE " << it->number << std::endl;
            _pnjs.erase(it);
            break;
        }
    }
    // for (int i = 0; i < nbPnj; i++) {
    //     if (_pnjs[i].number == number) {
    //         _pnjs.erase(_pnjs.begin() + i);
    //         _pnjMoveClocks.erase(_pnjMoveClocks.begin() + i);
    //         break;
    //     }
    // }

    _deathCounter++;
}

void zappy::InGame::segHandler(std::vector<std::string>& arguments)
{
    if (arguments.size() != 2)
        throw AScene::SceneException("Error: seg command has wrong number of arguments");

    std::string winnerName = arguments[1];

    std::cout << "Seg handler: team " << winnerName << " won" << std::endl;

    setWinnerName(winnerName);

    setIndexScene(2);
}
