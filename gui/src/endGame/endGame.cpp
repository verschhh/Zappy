/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** endGame.cpp
*/

#include "../../includes/gui.hpp"

zappy::EndGame::EndGame(Connection& connection, std::shared_ptr<Stats> stats)
{
    this->_stats = stats;
    (void)connection;
    loadTextures();
}

zappy::EndGame::~EndGame(void)
{

}

void zappy::EndGame::loadTextures(void)
{
    loadFont();

    if (!_backgroundTexture.loadFromFile("gui/assets/images/background_space.png"))
        throw AScene::SceneException("Error: cannot load background_space.png");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));

    if (!_quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png"))
        throw AScene::SceneException("Error: cannot load menu quit button texture");
    if (!_quitButtonHoveredTexture.loadFromFile("gui/assets/buttons/quit_button_hovered.png"))
        throw AScene::SceneException("Error: cannot load menu quit button texture");
    setSpriteProperties(_quitButtonSprite, _quitButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(960, 800));
}
