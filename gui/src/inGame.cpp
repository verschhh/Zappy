/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inGame.cpp
*/

#include "../includes/scenes.hpp"

zappy::InGame::InGame(int mapWidth, int mapHeight)
: _mapWidth(mapWidth), _mapHeight(mapHeight)
{
    setIndexScene(1);
    loadTextures();
    createMap();
}

zappy::InGame::~InGame() {}

void zappy::InGame::createMap()
{
    // TODO: idea -> create mutliple grid textures and choose one randomly
    if (!_gridTexture.loadFromFile("gui/assets/grid.png")) {
        throw SceneException("InGame error: cannot load grid texture");
    }

    _map.resize(_mapWidth);
    for (int i = 0; i < _mapWidth; i++) {
        _map[i].resize(_mapHeight);
        for (int j = 0; j < _mapHeight; j++) {
            // TODO: set a scale factor accoring to grid size (for all sprites)
            setSpriteProperties(_map[i][j], _gridTexture, sf::Vector2f(1.5, 1.5), sf::Vector2f(i * 60 * 1.6, j * 60 * 1.6));
        }
    }
}

void zappy::InGame::loadTextures() {
    _backgroundTexture.loadFromFile("gui/assets/images/test.jpg");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));
}

void zappy::InGame::handleEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();
    }
}

void zappy::InGame::drawScene(sf::RenderWindow& window, sf::Clock clock) {
    (void) clock;
    window.draw(_backgroundSprite);

    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            window.draw(_map[i][j]);
        }
    };
}
