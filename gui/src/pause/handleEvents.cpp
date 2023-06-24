/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** handleEvents.cpp
*/

#include "../../includes/scenes.hpp"

void zappy::Pause::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Back button events
        if (_backButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            _backButtonSprite.setTexture(_backButtonHoveredTexture);
        } else {
            _backButtonSprite.setTexture(_backButtonTexture);
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (_backButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                _stats->setIndexScene(IN_GAME);
            }
        }

        // Quit button events
        if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            _quitButtonSprite.setTexture(_quitButtonHoveredTexture);
        } else {
            _quitButtonSprite.setTexture(_quitButtonTexture);
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                window.close();
            }
        }
    }
}
