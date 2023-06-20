/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** draw.cpp
*/

#include "../../includes/scenes.hpp"

void zappy::EndGame::drawScene(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);
    window.draw(_quitButtonSprite);
}
