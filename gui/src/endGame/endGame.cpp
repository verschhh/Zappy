/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** endGame.cpp
*/

#include "../../includes/scenes.hpp"

zappy::EndGame::EndGame(Connection& connection)
{
    (void)connection;
    setIndexScene(2);
    loadTextures();
}

zappy::EndGame::~EndGame(void)
{

}

void zappy::EndGame::loadTextures(void)
{
    if (!_backgroundTexture.loadFromFile("gui/assets/images/background_space.png"))
        throw AScene::SceneException("Error: cannot load background_space.png");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));
}
