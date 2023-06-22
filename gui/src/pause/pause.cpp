/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pause.cpp
*/

#include "../../includes/scenes.hpp"

zappy::Pause::Pause(Connection& connection)
{
    (void)connection;
    setIndexScene(3);
    loadTextures();
}

zappy::Pause::~Pause(void)
{

}

void zappy::Pause::loadTextures(void)
{
    if (!_backgroundTexture.loadFromFile("gui/assets/images/space.jpg"))
        throw AScene::SceneException("Error: cannot load space.png");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));

    if (!_backButtonTexture.loadFromFile("gui/assets/buttons/back_button_still.png"))
        throw AScene::SceneException("Error: cannot load menu back button texture");

    if (!_backButtonHoveredTexture.loadFromFile("gui/assets/buttons/back_button_hovered.png"))
        throw AScene::SceneException("Error: cannot load menu back button texture");

    setSpriteProperties(_backButtonSprite, _backButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(760, 800));

    if (!_quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png"))
        throw AScene::SceneException("Error: cannot load menu quit button texture");

    if (!_quitButtonHoveredTexture.loadFromFile("gui/assets/buttons/quit_button_hovered.png"))
        throw AScene::SceneException("Error: cannot load menu quit button texture");

    setSpriteProperties(_quitButtonSprite, _quitButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(1160, 800));
}
