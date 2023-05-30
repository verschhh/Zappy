/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** gui.cpp
*/

#include "../includes/gui.hpp"

void zappy::Gui::run() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy");
    menu.loadTextures();
    menu.setupButtons();

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        menu.handleEvents(window);
        
        if (menu.isQuitButtonClicked()) {
            window.close();
        }

        menu.draw(window);

        // Display the updated window
        window.display();
    }
}
