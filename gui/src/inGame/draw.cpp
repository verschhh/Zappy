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
        std::cout << "DRAW Pnj num " << _pnjs[i].number << " level " << _pnjs[i].level << " at " << _pnjs[i].position.x << ", " << _pnjs[i].position.y << std::endl;
        int mapX = _pnjs[i].position.x;
        int mapY = _pnjs[i].position.y;

        sf::Vector2f mapPosition = _map[mapX][mapY].gridSprite.getPosition();
        if (_pnjMoveClocks[i].getElapsedTime().asSeconds() > 0.5) {
            float xOffset = randomNumber(-25, 25.0);
            float yOffset = randomNumber(-25, 25.0);

            if (_pnjs[i].offset.x < xOffset) {
                _pnjs[i].sprite.setTexture(_pnjTextures[_pnjs[i].type - 1].right);
            }
            else if (_pnjs[i].offset.x > xOffset) {
                _pnjs[i].sprite.setTexture(_pnjTextures[_pnjs[i].type - 1].left);
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
// void zappy::InGame::drawPnjs(sf::RenderWindow& window) {
//     int nbPnj = _pnjs.size();
//     for (int i = 0; i < nbPnj; i++) {
//         int mapX = _pnjs[i].position.x;
//         int mapY = _pnjs[i].position.y;

//         sf::Vector2f mapPosition = _map[mapX][mapY].gridSprite.getPosition();

//         _pnjs[i].sprite.setPosition(mapPosition);

//         window.draw(_pnjs[i].sprite);
//     };
// }

void zappy::InGame::drawRessources(sf::RenderWindow& window)
{
    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            if (_map[i][j].content.quantity.food > 0) {
                window.draw(_map[i][j].content.foodSprite);
            }
            if (_map[i][j].content.quantity.linemate > 0) {
                window.draw(_map[i][j].content.linemateSprite);
            }
            if (_map[i][j].content.quantity.deraumere > 0) {
                window.draw(_map[i][j].content.deraumereSprite);
            }
            if (_map[i][j].content.quantity.sibur > 0) {
                window.draw(_map[i][j].content.siburSprite);
            }
            if (_map[i][j].content.quantity.mendiane > 0) {
                window.draw(_map[i][j].content.mendianeSprite);
            }
            if (_map[i][j].content.quantity.phiras > 0) {
                window.draw(_map[i][j].content.phirasSprite);
            }
            if (_map[i][j].content.quantity.thystame > 0) {
                window.draw(_map[i][j].content.thystameSprite);
            }
        }
    }
}

void zappy::InGame::drawRessourceBar(sf::RenderWindow& window)
{
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

    // Draw the content bar
    window.draw(_contentBarSprite);
    ressources_t quantity = _map[_selectedTile.x][_selectedTile.y].content.quantity;
    _foodText = setText(
        std::to_string(quantity.food),
        sf::Vector2f(710, 985),
        30,
        sf::Color::White);
    window.draw(_foodText);

    _linemateText = setText(
        std::to_string(quantity.linemate),
        sf::Vector2f(802, 1015),
        20,
        sf::Color::White
    );
    window.draw(_linemateText);

    _deraumereText = setText(
        std::to_string(quantity.deraumere),
        sf::Vector2f(892, 1015),
        20,
        sf::Color::White
    );
    window.draw(_deraumereText);

    _siburText = setText(
        std::to_string(quantity.sibur),
        sf::Vector2f(982, 1015),
        20,
        sf::Color::White
    );
    window.draw(_siburText);

    _mendianeText = setText(
        std::to_string(quantity.mendiane),
        sf::Vector2f(1072, 1015),
        20,
        sf::Color::White
    );
    window.draw(_mendianeText);

    _phirasText = setText(
        std::to_string(quantity.phiras),
        sf::Vector2f(1162, 1015),
        20,
        sf::Color::White
    );
    window.draw(_phirasText);

    _thystameText = setText(
        std::to_string(quantity.thystame),
        sf::Vector2f(1252, 1015),
        20,
        sf::Color::White
    );
    window.draw(_thystameText);
}

void zappy::InGame::drawLevelsBar(sf::RenderWindow& window)
{
    // Draw level bar
    window.draw(_levelBarSprite);

    // Draw level count
    int pnjSize = _pnjs.size();
    std::array<int, 8> levelCount = {};
    for (int i = 0; i < pnjSize; i++) {
        levelCount[_pnjs[i].level - 1]++;
    }

    for (int i = 0; i < 8; i++) {
        sf::Text level_text = setText(
            std::to_string(levelCount[i]),
            sf::Vector2f(1884, 228 + (i * 50)),
            30,
            sf::Color::White
        );
        window.draw(level_text);
    }
}

void zappy::InGame::drawDeathCounter(sf::RenderWindow& window)
{
    window.draw(_deathCounterSprite);
    sf::Text death_text = setText(
        std::to_string(_stats->getDeathCounter()),
        sf::Vector2f(1868, 827),
        30,
        sf::Color::White
    );
    window.draw(death_text);
}

void zappy::InGame::drawScene(sf::RenderWindow& window)
{
    // Update scene
    updateScene();

    // Draw scene (map, pnjs, ressources, etc.)
    window.draw(_backgroundSprite);
    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            window.draw(_map[i][j].gridSprite);
        }
    };

    drawRessources(window);
    drawPnjs(window);

    drawLevelsBar(window);
    if (_selectedTile.x >= 0 && _selectedTile.y >= 0 && _selectedTile.x < _mapWidth && _selectedTile.y < _mapHeight) {
        drawRessourceBar(window);
    }
    drawDeathCounter(window);
}
