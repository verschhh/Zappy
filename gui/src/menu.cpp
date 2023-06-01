/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** menu.cpp
*/

#include "../includes/scenes.hpp"

zappy::Menu::Menu() {
    loadTextures();
}

zappy::Menu::~Menu() {}

void zappy::Menu::loadTextures() {
    _backgroundTexture.loadFromFile("gui/assets/images/background_space.png");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(0, 0));

    _logoTexture.loadFromFile("gui/assets/zappyLogo.png");
    setSpriteProperties(_logoSprite, _logoTexture, sf::Vector2f(15, 15), sf::Vector2f(250, 150));

    _playButtonTexture.loadFromFile("gui/assets/buttons/play_button_still.png");
    setSpriteProperties(_playButtonSprite, _playButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(600, 700));

    _quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png");
    setSpriteProperties(_quitButtonSprite, _quitButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(1060, 700));
}

void zappy::Menu::handleHoverButtons(sf::Vector2i mousePosition)
{
    if (_playButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        _playButtonTexture.loadFromFile("gui/assets/buttons/play_button_hovered.png");
        _playButtonSprite.setTexture(_playButtonTexture);
    } else {
        _playButtonTexture.loadFromFile("gui/assets/buttons/play_button_still.png");
        _playButtonSprite.setTexture(_playButtonTexture);
    }

    if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        _quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_hovered.png");
        _quitButtonSprite.setTexture(_quitButtonTexture);
    } else {
        _quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png");
        _quitButtonSprite.setTexture(_quitButtonTexture);
    }
}

void zappy::Menu::handleMouseClicks(sf::RenderWindow &window, sf::Event event, sf::Vector2i mousePosition)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_playButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            // TODO: increment scene index to switch to game scene
        }
        if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            window.close();
        }
    }
}

void zappy::Menu::handleEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        handleMouseClicks(window, event, mousePosition);
        handleHoverButtons(mousePosition);
    }
}

void zappy::Menu::drawScene(sf::RenderWindow& window) {
    window.draw(_backgroundSprite);
    window.draw(_logoSprite);
    window.draw(_playButtonSprite);
    window.draw(_quitButtonSprite);
}
