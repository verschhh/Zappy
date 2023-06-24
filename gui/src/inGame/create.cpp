/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** create.cpp
*/

#include "../../includes/scenes.hpp"

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
                _map[i][j].gridSprite,
                _gridTextures[randomNumber(0, 6)],
                sf::Vector2f(_scaleFactor, _scaleFactor),
                sf::Vector2f(startX + i * (scaledSpriteSize + scaledGap), startY + j * (scaledSpriteSize + scaledGap))
            );
        }
    }
}

void zappy::InGame::createPnj(int number, int x, int y, pnjOrientation orientation, int level)
{
    if (x < 0 || x >= _mapWidth || y < 0 || y >= _mapHeight)
        throw AScene::SceneException("Error: cannot create pnj outside of the map");

    pnj_t pnj;

    pnj.number = number;

    int rnd = randomNumber(1, 3);
    pnj.type = rnd;

    pnj.level = level;

    pnj.sprite.setTexture(_pnjTextures[rnd - 1].left);

    pnj.sprite.setTextureRect(pnj.rect);

    pnj.sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));

    pnj.sprite.setOrigin(32 / 2, 32 / 2);

    pnj.position = sf::Vector2f(x, y);
    pnj.orientation = orientation;

    _pnjMoveClocks.push_back(sf::Clock());
    _pnjs.push_back(pnj);

    _stats->increasePnjCounter();
}
