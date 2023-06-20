/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** handle.cpp
*/

#include "../../includes/scenes.hpp"

void zappy::EndGame::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        if (event.type == sf::Event::MouseButtonPressed) {
            if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                window.close();
            }
        }

        if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            _quitButtonSprite.setTexture(_quitButtonHoveredTexture);
        } else {
            _quitButtonSprite.setTexture(_quitButtonTexture);
        }

        //! TEMP: display mouse click position
        // if (event.type == sf::Event::MouseButtonPressed) {
        //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //     std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        // }
    }
}
