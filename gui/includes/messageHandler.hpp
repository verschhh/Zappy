/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** messageHandler.hpp
*/

#pragma once

#include <sstream>
#include <string>
#include "scenes.hpp"

namespace zappy {
    class MessageHandler {
    public:
        static void handleBctMessage(const std::string& message, std::vector<std::vector<zappy::InGame::tile_t>>& map);
        static void parseBctMessage(const std::string& message, int& tileX, int& tileY, zappy::InGame::tile_content_t& content);
    };
}
