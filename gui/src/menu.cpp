/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** menu.cpp
*/

#include "../includes/scenes.hpp"
#include <iostream> // TODO: del this include

zappy::Menu::Menu() {
    loadTextures();
    setupButtons();
}

zappy::Menu::~Menu() {
    // ? Do we need to free textures here ?
}

void zappy::Menu::loadTextures() {
    _backgroundTexture.loadFromFile("gui/assets/images/background_space.png");
    _backgroundSprite.setTexture(_backgroundTexture);
    _logoTexture.loadFromFile("gui/assets/zappyLogo.png");
    _logoSprite.setTexture(_logoTexture);
    _logoSprite.setScale(15, 15);
    _playButtonTexture.loadFromFile("gui/assets/buttons/play_button_still.png");
    _playButtonSprite.setTexture(_playButtonTexture);
    _playButtonSprite.setScale(4, 4);
    _quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png");
    _quitButtonSprite.setTexture(_quitButtonTexture);
    _quitButtonSprite.setScale(4, 4);
}

void zappy::Menu::setupButtons() {
    _backgroundSprite.setPosition(0, 0);
    _logoSprite.setPosition(250, 150);
    _playButtonSprite.setPosition(600, 700);
    _quitButtonSprite.setPosition(1060, 700);
}

void zappy::Menu::handleEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // ? Duplicate ? Not if we make an handle events functions for each scene (scene selector)
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }
}

void zappy::Menu::drawScene(sf::RenderWindow& window) {
    window.draw(_backgroundSprite);
    window.draw(_logoSprite);
    window.draw(_playButtonSprite);
    window.draw(_quitButtonSprite);
}
