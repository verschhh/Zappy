/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** gui.cpp
*/

#include "../includes/gui.hpp"

void zappy::Gui::run() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Zappy");

    // Game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Handle other events as needed
        }

        // Update game logic and render the GUI elements

        // Clear the window
        window.clear();

        // Draw GUI elements

        // Display the updated window
        window.display();
    }
}
