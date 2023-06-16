/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** messageHandler.cpp
*/

// #include "../../includes/messangeHandle.hpp"
#include <iostream> //! TEMP
#include <sstream>
#include <string>
#include "../../includes/scenes.hpp"
#include "../../includes/messageHandler.hpp"

void zappy::MessageHandler::handleBctMessage(const std::string& message, std::vector<std::vector<zappy::InGame::tile_t>>& map)
{
    int tileX, tileY;
    zappy::InGame::tile_content_t content;
    parseBctMessage(message, tileX, tileY, content);

    std::cout << "Received BCT message for tile (" << tileX << ", " << tileY << ")" << std::endl;

    // Update the tile information in the map based on the parsed data
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

    std::cout << "Parsed BCT message: Tile (" << tileX << ", " << tileY << ")" << std::endl;
    std::cout << "Food: " << content.quantity.food << std::endl;
    std::cout << "Linemate: " << content.quantity.linemate << std::endl;
    std::cout << "Deraumere: " << content.quantity.deraumere << std::endl;
    std::cout << "Sibur: " << content.quantity.sibur << std::endl;
    std::cout << "Mendiane: " << content.quantity.mendiane << std::endl;
    std::cout << "Phiras: " << content.quantity.phiras << std::endl;
    std::cout << "Thystame: " << content.quantity.thystame << std::endl;

    std::cout << "Parsing done" << std::endl;
}
