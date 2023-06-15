/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** handleEvents.cpp
*/

#include "../../includes/scenes.hpp"
#include "../../includes/messageHandler.hpp"
#include <iostream> //! TEMP

// void zappy::InGame::handleEvents(sf::RenderWindow& window)
// {
//     sf::Event event;

//     while (window.pollEvent(event)) {
//         if (event.type == sf::Event::Closed
//         || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
//             window.close();

//         // TEMP: if mouse click
//         if (event.type == sf::Event::MouseButtonPressed) {
//             sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//             std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
//         }

//     }
// }

void zappy::InGame::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        // if (event.type == sf::Event::MouseButtonPressed) {
        //     sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //     std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        // }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

            // Find the tile at the clicked position
            for (int x = 0; x < _mapWidth; x++) {
                for (int y = 0; y < _mapHeight; y++) {
                    const sf::Sprite& gridSprite = _map[x][y].gridSprite;
                    sf::FloatRect bounds = gridSprite.getGlobalBounds();
                    if (bounds.contains(worldPosition)) {
                        // Toggle selection of the clicked tile
                        if (_selectedTile == sf::Vector2i(x, y)) {
                            _selectedTile = sf::Vector2i(-1, -1);  // Deselect the tile
                        } else {
                            _selectedTile = sf::Vector2i(x, y);    // Select the tile
                        }
                        std::cout << "Selected tile: " << _selectedTile.x << ", " << _selectedTile.y << std::endl;
                        std::string command = "bct " + std::to_string(x) + " " + std::to_string(y) + "\n";
                        // _connection.send(command);

                        // // Receive the response from the server
                        // std::string response = _connection.receive();
                        // std::cout << "Response: " << response << std::endl;

                        // // Handle the received message using the MessageHandler
                        // MessageHandler::handleBctMessage(response, _map);

                        std::cout << "after message handler" << std::endl;
                        // Send the appropriate command to the server using the Connection class
                        // Handle the response and update the information to display on the selected tile
                    }
                }
            }
        }
    }
}
