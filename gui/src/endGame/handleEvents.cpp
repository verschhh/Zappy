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

        //! TEMP: display mouse click position
        // if (event.type == sf::Event::MouseButtonPressed) {
        //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //     std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        // }
    }
}
