/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** handleEvents.cpp
*/

#include "../../includes/scenes.hpp"
#include <iostream> //! TEMP

void zappy::InGame::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();

        // TEMP: if mouse click
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        }
    }
}
