/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inGame.cpp
*/

#include "../includes/scenes.hpp"
#include <iostream> //! TEMP

zappy::InGame::InGame(int mapWidth, int mapHeight)
: _mapWidth(mapWidth), _mapHeight(mapHeight), _scaleFactor(1)
{
    setIndexScene(1);
    createMap();
    loadTextures();
}

zappy::InGame::~InGame() {}

static int randomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    int randomNumber = dist(gen);
    return (randomNumber);
}

void zappy::InGame::createMap()
{
    _gridTextures.resize(7);
    for (int i = 0; i < 7; i++) {
        std::string texturePath = "gui/assets/map/grid" + std::to_string(i + 1) + ".png";
        if (!_gridTextures[i].loadFromFile(texturePath))
            throw AScene::SceneException("Error: cannot load grid texture " + std::to_string(i + 1));
    }

    int spriteSize = 60;
    int gap = spriteSize / 5;

    int totalWidth = _mapWidth * (spriteSize + gap) + spriteSize * 4;
    int totalHeight = _mapHeight * (spriteSize + gap) + spriteSize * 4;

    float scaleFactorWidth = static_cast<float>(WINDOW_WIDTH) / totalWidth;
    float scaleFactorHeight = static_cast<float>(WINDOW_HEIGHT) / totalHeight;
    _scaleFactor = std::min(scaleFactorWidth, scaleFactorHeight);

    int scaledSpriteSize = static_cast<int>(spriteSize * _scaleFactor);
    int scaledGap = static_cast<int>(gap * _scaleFactor);

    float spriteHalfWidth = scaledSpriteSize / 2;
    float spriteHalfHeight = scaledSpriteSize / 2;

    int startX = (WINDOW_WIDTH - (_mapWidth * (scaledSpriteSize + scaledGap) - scaledGap)) / 2 + spriteHalfWidth;
    int startY = (WINDOW_HEIGHT - (_mapHeight * (scaledSpriteSize + scaledGap) - scaledGap)) / 2 + spriteHalfHeight - 20;

    _map.resize(_mapWidth);
    for (int i = 0; i < _mapWidth; i++) {
        _map[i].resize(_mapHeight);
        for (int j = 0; j < _mapHeight; j++) {
            setSpriteProperties(
                _map[i][j],
                _gridTextures[randomNumber(0, 6)],
                sf::Vector2f(_scaleFactor, _scaleFactor),
                sf::Vector2f(startX + i * (scaledSpriteSize + scaledGap), startY + j * (scaledSpriteSize + scaledGap))
            );
        }
    }
}

void zappy::InGame::loadTextures() {
    if (!_backgroundTexture.loadFromFile("gui/assets/images/space.jpg"))
        throw AScene::SceneException("Error: cannot load in game background texture");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));
}

void zappy::InGame::handleEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();

        // TEMP: if mouse click
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        }
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
