/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** menu.cpp
*/

#include "../includes/menu.hpp"
#include <iostream> // TODO: del this include

Menu::Menu() {
    loadTextures();
    setupButtons();
}

void Menu::loadTextures() {
    backgroundTexture.loadFromFile("gui/assets/images/background_space.png");
    backgroundSprite.setTexture(backgroundTexture);
    logoTexture.loadFromFile("gui/assets/zappyLogo.png");
    logoSprite.setTexture(logoTexture);
    logoSprite.setScale(15, 15);
    playButtonTexture.loadFromFile("gui/assets/buttons/play_button_still.png");
    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setScale(4, 4);
    quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png");
    quitButtonSprite.setTexture(quitButtonTexture);
    quitButtonSprite.setScale(4, 4);
}

void Menu::setupButtons() {
    backgroundSprite.setPosition(0, 0);
    logoSprite.setPosition(250, 150);
    playButtonSprite.setPosition(600, 700);
    quitButtonSprite.setPosition(1060, 700);
}

bool Menu::isQuitButtonClicked() {
    return _isQuitButtonClicked;
}

void Menu::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            std::cout << "x: " << event.mouseButton.x;
            std::cout << "y: " << event.mouseButton.y << std::endl;
            // if (event.mouseButton.button == sf::Mouse::Left) {
            //     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            //     if (quitButtonSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            //         _isQuitButtonClicked = true;
            //     }
            // }
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(logoSprite);
    window.draw(playButtonSprite);
    window.draw(quitButtonSprite);
}
