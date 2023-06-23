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

    std::string winnerString = "The winner is: " + getWinnerName();

    _winnerText = setText(
        winnerString,
        sf::Vector2f(350, 350),
        100,
        sf::Color::White
    );

    window.draw(_winnerText);
}
