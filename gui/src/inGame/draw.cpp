/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** draw.cpp
*/

#include "../../includes/scenes.hpp"

//! Kentin's version
void zappy::InGame::drawPnjs(sf::RenderWindow& window)
{
    int nbPnj = _pnjs.size();
    for (int i = 0; i < nbPnj; i++) {
        int mapX = _pnjs[i].position.x;
        int mapY = _pnjs[i].position.y;

        sf::Vector2f mapPosition = _map[mapX][mapY].getPosition();
        if (_pnjMoveClocks[i].getElapsedTime().asSeconds() > 0.5) {
            float xOffset = randomNumber(-25, 25.0);
            float yOffset = randomNumber(-25, 25.0);

            sf::Vector2f spritePosition = mapPosition + sf::Vector2f(xOffset, yOffset);
            _pnjs[i].sprite.setPosition(spritePosition);

            _pnjMoveClocks[i].restart();
        }


        window.draw(_pnjs[i].sprite);
    }
}

//! TEMP: keep this version of the function without the animation
// void zappy::InGame::drawPnjs(sf::RenderWindow& window, sf::Clock clock) {
//     (void) clock;

//     _pnjMoveClock.restart();

//     float elapsedTime = _pnjMoveClock.getElapsedTime().asSeconds();

//     int nbPnj = _pnjs.size();
//     for (int i = 0; i < nbPnj; i++) {
//         int mapX = _pnjs[i].position.x;
//         int mapY = _pnjs[i].position.y;

//         sf::Vector2f mapPosition = _map[mapX][mapY].getPosition();

//         _pnjs[i].sprite.setPosition(mapPosition);

//         window.draw(_pnjs[i].sprite);
//     };
// }

void zappy::InGame::drawRessources(sf::RenderWindow& window, sf::Clock clock)
{
    (void) clock;
    (void) window;
}

void zappy::InGame::drawScene(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);

    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            window.draw(_map[i][j]);
        }
    };

    drawPnjs(window);
}
