/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inGame.cpp
*/

#include "../../includes/scenes.hpp"

zappy::InGame::InGame(Connection& connection, int mapWidth, int mapHeight)
    : _connection(connection), _mapWidth(mapWidth), _mapHeight(mapHeight)
{
    setIndexScene(1);
    createMap();
    loadTextures();
}

zappy::InGame::~InGame() {}

void zappy::InGame::loadTextures()
{
    if (!_font.loadFromFile("gui/assets/font/DeterminationMono.ttf"))
        throw AScene::SceneException("Error: cannot load font");

    if (!_backgroundTexture.loadFromFile("gui/assets/images/space.jpg"))
        throw AScene::SceneException("Error: cannot load in game background texture");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));

    if (!_contentBarTexture.loadFromFile("gui/assets/hud/contentBar.png"))
        throw AScene::SceneException("Error: cannot load contentBar.png");
    setSpriteProperties(_contentBarSprite, _contentBarTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 1005));

    int nbPnjTextures = 3;
    for (int i = 0; i < nbPnjTextures; i++) {
        pnjTextures_t pnjTextures;
        if (!pnjTextures.left.loadFromFile("gui/assets/pnj/pnj" + std::to_string(i + 1) + "_left.png"))
            throw AScene::SceneException("Error: cannot load pnj" + std::to_string(i + 1) + "_left.png");

        if (!pnjTextures.right.loadFromFile("gui/assets/pnj/pnj" + std::to_string(i + 1) + "_right.png"))
            throw AScene::SceneException("Error: cannot load pnj" + std::to_string(i + 1) + "_right.png");

        _pnjTextures.push_back(pnjTextures);
    }

    int nbCrystalsTextures = 6;
    for (int i = 0; i < nbCrystalsTextures; i++) {
        sf::Texture texture;
        if (!texture.loadFromFile("gui/assets/objects/crystals/crystal" + std::to_string(i + 1) + ".png"))
            throw AScene::SceneException("Error: cannot load crystal" + std::to_string(i + 1) + ".png");

        _ressourcesTextures.push_back(texture);
    }

    if (!_foodTexture.loadFromFile("gui/assets/objects/apple.png"))
        throw AScene::SceneException("Error: cannot load apple.png");

    // ! TEMP
    createPnj(10, 4, NORTH);
    createPnj(5, 8, WEST);
    createPnj(5, 8, EAST);
    createPnj(10, 2, SOUTH);
    createPnj(10, 3, SOUTH);

    createRessources(10, 6, {1, 1, 1, 1, 1, 1, 1});
    createRessources(2, 1, {1, 0, 0, 0, 0, 0, 0});
    createRessources(2, 2, {0, 1, 0, 0, 0, 0, 0});
    createRessources(2, 3, {0, 0, 1, 0, 0, 0, 0});
    createRessources(2, 4, {0, 0, 0, 1, 0, 0, 0});
    createRessources(2, 5, {0, 0, 0, 0, 1, 0, 0});
    createRessources(2, 6, {0, 0, 0, 0, 0, 1, 0});
    createRessources(2, 7, {0, 0, 0, 0, 0, 0, 1});
    createRessources(5, 8, {1, 1, 1, 1, 1, 1, 1});
}
