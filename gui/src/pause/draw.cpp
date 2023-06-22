/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** draw.cpp
*/

#include "../../includes/scenes.hpp"

void zappy::Pause::drawScene(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);
    window.draw(_backButtonSprite);
    window.draw(_quitButtonSprite);
}
