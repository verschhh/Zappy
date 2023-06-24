/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** handleEvents.cpp
*/

#include "../../includes/scenes.hpp"
#include "../../includes/messageHandler.hpp"

void zappy::InGame::clickTile(sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

    for (int x = 0; x < _mapWidth; x++) {
        for (int y = 0; y < _mapHeight; y++) {
            const sf::Sprite& gridSprite = _map[x][y].gridSprite;
            sf::FloatRect bounds = gridSprite.getGlobalBounds();
            if (bounds.contains(worldPosition)) {
                if (_selectedTile == sf::Vector2i(x, y)) {
                    _selectedTile = sf::Vector2i(-1, -1);  // Deselect the tile
                } else {
                    _selectedTile = sf::Vector2i(x, y);    // Select the tile
                }
            }
        }
    }
}

void zappy::InGame::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            setIndexScene(3);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            clickTile(window);
        }
    }
}
