/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** draw.cpp
*/

#include "../../includes/scenes.hpp"
#include <iostream>

//! Kentin's version
void zappy::InGame::drawPnjs(sf::RenderWindow& window)
{
    int nbPnj = _pnjs.size();
    for (int i = 0; i < nbPnj; i++) {
        int mapX = _pnjs[i].position.x;
        int mapY = _pnjs[i].position.y;

        sf::Vector2f mapPosition = _map[mapX][mapY].gridSprite.getPosition();
        if (_pnjMoveClocks[i].getElapsedTime().asSeconds() > 0.5) {
            float xOffset = randomNumber(-25, 25.0);
            float yOffset = randomNumber(-25, 25.0);

            if (_pnjs[i].offset.x < xOffset) {
                _pnjs[i].sprite.setTexture(_pnjTextures[i].right);
            }
            else if (_pnjs[i].offset.x > xOffset) {
                _pnjs[i].sprite.setTexture(_pnjTextures[i].left);
            }


            sf::Vector2f spritePosition = mapPosition + sf::Vector2f(xOffset, yOffset);
            _pnjs[i].sprite.setPosition(spritePosition);

            _pnjs[i].offset = sf::Vector2f(xOffset, yOffset);

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

void zappy::InGame::drawRessources(sf::RenderWindow& window)
{
    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            int foodSize = _map[i][j].content.quantity.food;
            // std::cout << "Food size: " << foodSize << std::endl;
            for (int k = 0; k < foodSize; k++) {
                window.draw(_map[i][j].content.foodSprites[k]);
                // std::cout << "Drawing food sprite" << std::endl;
            }

            int linemateSize = _map[i][j].content.quantity.linemate;
            // std::cout << "Linemate size: " << linemateSize << std::endl;
            for (int k = 0; k < linemateSize; k++) {
                window.draw(_map[i][j].content.linemateSprites[k]);
                // std::cout << "Drawing linemate sprite" << std::endl;
            }

            int deraumereSize = _map[i][j].content.quantity.deraumere;
            // std::cout << "Deraumere size: " << deraumereSize << std::endl;
            for (int k = 0; k < deraumereSize; k++) {
                window.draw(_map[i][j].content.deraumereSprites[k]);
                // std::cout << "Drawing deraumere sprite" << std::endl;
            }

            int siburSize = _map[i][j].content.quantity.sibur;
            // std::cout << "Sibur size: " << siburSize << std::endl;
            for (int k = 0; k < siburSize; k++) {
                window.draw(_map[i][j].content.siburSprites[k]);
                // std::cout << "Drawing sibur sprite" << std::endl;
            }

            int mendianeSize = _map[i][j].content.quantity.mendiane;
            // std::cout << "Mendiane size: " << mendianeSize << std::endl;
            for (int k = 0; k < mendianeSize; k++) {
                window.draw(_map[i][j].content.mendianeSprites[k]);
                // std::cout << "Drawing mendiane sprite" << std::endl;
            }

            int phirasSize = _map[i][j].content.quantity.phiras;
            // std::cout << "Phiras size: " << phirasSize << std::endl;
            for (int k = 0; k < phirasSize; k++) {
                window.draw(_map[i][j].content.phirasSprites[k]);
                // std::cout << "Drawing phiras sprite" << std::endl;
            }

            int thystameSize = _map[i][j].content.quantity.thystame;
            // std::cout << "Thystame size: " << thystameSize << std::endl;
            for (int k = 0; k < thystameSize; k++) {
                window.draw(_map[i][j].content.thystameSprites[k]);
                // std::cout << "Drawing thystame sprite" << std::endl;
            }
        }
    }
}

void zappy::InGame::drawScene(sf::RenderWindow& window)
{
    std::cout << "draw scene" << std::endl;
    window.draw(_backgroundSprite);
    std::cout << "draw background complete" << std::endl;
    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            window.draw(_map[i][j].gridSprite);
        }
    };
    std::cout << "draw grid complete" << std::endl;
    if (_selectedTile.x >= 0 && _selectedTile.y >= 0 && _selectedTile.x < _mapWidth && _selectedTile.y < _mapHeight) {
        const sf::Sprite& gridSprite = _map[_selectedTile.x][_selectedTile.y].gridSprite;
        sf::FloatRect bounds = gridSprite.getGlobalBounds();
        // Draw a colored border around the selected tile
        sf::RectangleShape border;
        border.setSize(sf::Vector2f(bounds.width, bounds.height));
        border.setPosition(bounds.left, bounds.top);
        border.setOutlineThickness(5.0f);
        border.setOutlineColor(sf::Color::Red);
        border.setFillColor(sf::Color::Transparent);
        window.draw(border);
        window.draw(_contentBarSprite);

        // Display the received information on the selected tile
        // Modify the code according to your specific requirements
        // const tile_content_t& tileContent = _map[_selectedTile.x][_selectedTile.y].content;
        // Draw the received information on the selected tile
        // ...
    }
    std::cout << "draw selected tile complete" << std::endl;
    drawRessources(window);
    std::cout << "draw resources complete" << std::endl;
    drawPnjs(window);
    std::cout << "draw pnjs complete" << std::endl;
}

