/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inGame.cpp
*/

#include "../includes/scenes.hpp"

zappy::InGame::InGame()
{
    setIndexScene(1);
    loadTextures();
}

zappy::InGame::~InGame() {}

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
}
