/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** create.cpp
*/

#include "../../includes/scenes.hpp"
#include <iostream> //! TEMP

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

void zappy::InGame::createPnj(int x, int y, pnjOrientation orientation)
{
    pnj_t pnj;

    int rnd = randomNumber(1, 3);
    pnj.type = rnd;

    pnj.sprite.setTexture(_pnjTextures[rnd - 1].left);

    pnj.sprite.setTextureRect(pnj.rect);

    // TODO: tweak scale
    pnj.sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));

    //? set origin
    pnj.sprite.setOrigin(32 / 2, 32 / 2);

    pnj.position = sf::Vector2f(x, y);
    pnj.orientation = orientation;

    _pnjMoveClocks.push_back(sf::Clock());
    _pnjs.push_back(pnj);
}

void zappy::InGame::createRessources(int x, int y, ressources_t ressources)
{
    // std::cout << "Ressources" << std::endl;
    // std::cout << "Food: " << ressources.food << std::endl;
    // std::cout << "Linemate: " << ressources.linemate << std::endl;
    // std::cout << "Deraumere: " << ressources.deraumere << std::endl;
    // std::cout << "Sibur: " << ressources.sibur << std::endl;
    // std::cout << "Mendiane: " << ressources.mendiane << std::endl;
    // std::cout << "Phiras: " << ressources.phiras << std::endl;
    // std::cout << "Thystame: " << ressources.thystame << std::endl;

    tile_content_t tileContent;

    tileContent.quantity = ressources;

    for (int i = 0; i < ressources.food; i++) {
        sf::Sprite sprite;
        sprite.setTexture(_foodTexture);
        sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
        sprite.setOrigin(20 / 2, 20 / 2);
        sf::Vector2f position = _map[x][y].gridSprite.getPosition();
        int randomX = randomNumber(-25, 25);
        int randomY = randomNumber(-25, 25);
        sprite.setPosition(position.x + randomX, position.y + randomY);
        tileContent.foodSprites.push_back(sprite);
    }

    for (int i = 0; i < ressources.linemate; i++) {
        sf::Sprite sprite;
        sprite.setTexture(_ressourcesTextures[0]);
        sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
        sprite.setOrigin(20 / 2, 20 / 2);
        sf::Vector2f position = _map[x][y].gridSprite.getPosition();
        int randomX = randomNumber(-25, 25);
        int randomY = randomNumber(-25, 25);
        sprite.setPosition(position.x + randomX, position.y + randomY);
        tileContent.linemateSprites.push_back(sprite);
    }

    for (int i = 0; i < ressources.deraumere; i++) {
        sf::Sprite sprite;
        sprite.setTexture(_ressourcesTextures[1]);
        sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
        sprite.setOrigin(20 / 2, 20 / 2);
        sf::Vector2f position = _map[x][y].gridSprite.getPosition();
        int randomX = randomNumber(-25, 25);
        int randomY = randomNumber(-25, 25);
        sprite.setPosition(position.x + randomX, position.y + randomY);
        tileContent.deraumereSprites.push_back(sprite);
    }

    for (int i = 0; i < ressources.sibur; i++) {
        sf::Sprite sprite;
        sprite.setTexture(_ressourcesTextures[2]);
        sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
        sprite.setOrigin(20 / 2, 20 / 2);
        sf::Vector2f position = _map[x][y].gridSprite.getPosition();
        int randomX = randomNumber(-25, 25);
        int randomY = randomNumber(-25, 25);
        sprite.setPosition(position.x + randomX, position.y + randomY);
        tileContent.siburSprites.push_back(sprite);
    }

    for (int i = 0; i < ressources.mendiane; i++) {
        sf::Sprite sprite;
        sprite.setTexture(_ressourcesTextures[3]);
        sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
        sprite.setOrigin(20 / 2, 20 / 2);
        sf::Vector2f position = _map[x][y].gridSprite.getPosition();
        int randomX = randomNumber(-25, 25);
        int randomY = randomNumber(-25, 25);
        sprite.setPosition(position.x + randomX, position.y + randomY);
        tileContent.mendianeSprites.push_back(sprite);
    }

    for (int i = 0; i < ressources.phiras; i++) {
        sf::Sprite sprite;
        sprite.setTexture(_ressourcesTextures[4]);
        sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
        sprite.setOrigin(20 / 2, 20 / 2);
        sf::Vector2f position = _map[x][y].gridSprite.getPosition();
        int randomX = randomNumber(-25, 25);
        int randomY = randomNumber(-25, 25);
        sprite.setPosition(position.x + randomX, position.y + randomY);
        tileContent.phirasSprites.push_back(sprite);
    }

    for (int i = 0; i < ressources.thystame; i++) {
        sf::Sprite sprite;
        sprite.setTexture(_ressourcesTextures[5]);
        sprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
        sprite.setOrigin(20 / 2, 20 / 2);
        sf::Vector2f position = _map[x][y].gridSprite.getPosition();
        int randomX = randomNumber(-25, 25);
        int randomY = randomNumber(-25, 25);
        sprite.setPosition(position.x + randomX, position.y + randomY);
        tileContent.thystameSprites.push_back(sprite);
    }

    _map[x][y].content = tileContent;
}
