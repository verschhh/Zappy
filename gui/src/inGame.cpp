/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inGame.cpp
*/

#include "../includes/scenes.hpp"

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
        _gridTextures[i].loadFromFile(texturePath);
    }

    int spriteSize = 60;
    int gap = spriteSize / 5;

    int totalWidth = _mapWidth * (spriteSize + gap) + spriteSize * 4;
    int totalHeight = _mapHeight * (spriteSize + gap) + spriteSize * 4;

    _scaleFactor = std::min((WINDOW_WIDTH / static_cast<float>(totalWidth)), WINDOW_HEIGHT / static_cast<float>(totalHeight));

    int scaledSpriteSize = static_cast<int>(spriteSize * _scaleFactor);
    int scaledGap = static_cast<int>(gap * _scaleFactor);

    int scaledTotalWidth = _mapWidth * (scaledSpriteSize + scaledGap) - scaledGap;
    int scaledTotalHeight = _mapHeight * (scaledSpriteSize + scaledGap) - scaledGap;

    int startX = (WINDOW_WIDTH - scaledTotalWidth) / 2;
    int startY = (WINDOW_HEIGHT - scaledTotalHeight) / 2;

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
    _backgroundTexture.loadFromFile("gui/assets/images/space.jpg");
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
