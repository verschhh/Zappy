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
            for (int k = 0; k < foodSize; k++) {
                window.draw(_map[i][j].content.foodSprites[k]);
            }

            int linemateSize = _map[i][j].content.quantity.linemate;
            for (int k = 0; k < linemateSize; k++) {
                window.draw(_map[i][j].content.linemateSprites[k]);
            }

            int deraumereSize = _map[i][j].content.quantity.deraumere;
            for (int k = 0; k < deraumereSize; k++) {
                window.draw(_map[i][j].content.deraumereSprites[k]);
            }

            int siburSize = _map[i][j].content.quantity.sibur;
            for (int k = 0; k < siburSize; k++) {
                window.draw(_map[i][j].content.siburSprites[k]);
            }

            int mendianeSize = _map[i][j].content.quantity.mendiane;
            for (int k = 0; k < mendianeSize; k++) {
                window.draw(_map[i][j].content.mendianeSprites[k]);
            }

            int phirasSize = _map[i][j].content.quantity.phiras;
            for (int k = 0; k < phirasSize; k++) {
                window.draw(_map[i][j].content.phirasSprites[k]);
            }

            int thystameSize = _map[i][j].content.quantity.thystame;
            for (int k = 0; k < thystameSize; k++) {
                window.draw(_map[i][j].content.thystameSprites[k]);
            }
        }
    }
}

void zappy::InGame::drawScene(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);

    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            window.draw(_map[i][j].gridSprite);
        }
    };

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
        // Display the received information on the selected tile
        // Modify the code according to your specific requirements
        // const tile_content_t& tileContent = _map[_selectedTile.x][_selectedTile.y].content;
        // Draw the received information on the selected tile
        // ...
    }

    drawRessources(window);
    drawPnjs(window);
}
