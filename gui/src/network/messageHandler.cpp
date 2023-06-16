/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** messageHandler.cpp
*/

#include <sstream>
#include <string>
#include "../../includes/scenes.hpp"
#include "../../includes/messageHandler.hpp"

void zappy::MessageHandler::handleBctMessage(const std::string& message, std::vector<std::vector<zappy::InGame::tile_t>>& map)
{
    int tileX, tileY;
    zappy::InGame::tile_content_t content;
    parseBctMessage(message, tileX, tileY, content);

    zappy::InGame::tile_t& tile = map[tileX][tileY];
    tile.content.quantity = content.quantity;
}

void zappy::MessageHandler::parseBctMessage(const std::string& message, int& tileX, int& tileY, zappy::InGame::tile_content_t& content)
{
    std::istringstream iss(message);
    std::string messageType;
    iss >> messageType >> tileX >> tileY;
    iss >> content.quantity.food;
    iss >> content.quantity.linemate;
    iss >> content.quantity.deraumere;
    iss >> content.quantity.sibur;
    iss >> content.quantity.mendiane;
    iss >> content.quantity.phiras;
    iss >> content.quantity.thystame;
}
