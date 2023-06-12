/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** draw.cpp
*/

#include "../../includes/scenes.hpp"

//! Kentin's version
void zappy::InGame::drawPnjs(sf::RenderWindow& window)
{
    int nbPnj = _pnjs.size();
    for (int i = 0; i < nbPnj; i++) {
        int mapX = _pnjs[i].position.x;
        int mapY = _pnjs[i].position.y;

        sf::Vector2f mapPosition = _map[mapX][mapY].gridSprite.getPosition();
        if (_pnjMoveClocks[i].getElapsedTime().asSeconds() > 0.5) {
            float xOffset = randomNumber(-25, 25.0);
            float yOffset = randomNumber(-25, 25.0);

            if (_pnjs[i].offset.x < xOffset) {
                _pnjs[i].sprite.setTexture(_pnjTextures[_pnjs[i].type - 1].right);
            }
            else if (_pnjs[i].offset.x > xOffset) {
                _pnjs[i].sprite.setTexture(_pnjTextures[_pnjs[i].type - 1].left);
            }

            sf::Vector2f spritePosition = mapPosition + sf::Vector2f(xOffset, yOffset);
            _pnjs[i].sprite.setPosition(spritePosition);

            _pnjs[i].offset = sf::Vector2f(xOffset, yOffset);

            _pnjMoveClocks[i].restart();
        }


        window.draw(_pnjs[i].sprite);
    }
}

//! TEMP: keep this version of the function without the animation
// void zappy::InGame::drawPnjs(sf::RenderWindow& window) {
//     int nbPnj = _pnjs.size();
//     for (int i = 0; i < nbPnj; i++) {
//         int mapX = _pnjs[i].position.x;
//         int mapY = _pnjs[i].position.y;

//         sf::Vector2f mapPosition = _map[mapX][mapY].gridSprite.getPosition();

//         _pnjs[i].sprite.setPosition(mapPosition);

//         window.draw(_pnjs[i].sprite);
//     };
// }

void zappy::InGame::drawRessources(sf::RenderWindow& window)
{
    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            int foodSize = _map[i][j].content.quantity.food;
            for (int k = 0; k < foodSize; k++) {
                window.draw(_map[i][j].content.foodSprites[k]);
            }

            int linemateSize = _map[i][j].content.quantity.linemate;
            for (int k = 0; k < linemateSize; k++) {
                window.draw(_map[i][j].content.linemateSprites[k]);
            }

            int deraumereSize = _map[i][j].content.quantity.deraumere;
            for (int k = 0; k < deraumereSize; k++) {
                window.draw(_map[i][j].content.deraumereSprites[k]);
            }

            int siburSize = _map[i][j].content.quantity.sibur;
            for (int k = 0; k < siburSize; k++) {
                window.draw(_map[i][j].content.siburSprites[k]);
            }

            int mendianeSize = _map[i][j].content.quantity.mendiane;
            for (int k = 0; k < mendianeSize; k++) {
                window.draw(_map[i][j].content.mendianeSprites[k]);
            }

            int phirasSize = _map[i][j].content.quantity.phiras;
            for (int k = 0; k < phirasSize; k++) {
                window.draw(_map[i][j].content.phirasSprites[k]);
            }

            int thystameSize = _map[i][j].content.quantity.thystame;
            for (int k = 0; k < thystameSize; k++) {
                window.draw(_map[i][j].content.thystameSprites[k]);
            }
        }
    }
}

sf::Text zappy::InGame::setText(std::string content, sf::Vector2f pos, int charSize, sf::Color color)
{
    sf::Text text;
    text.setFont(_font);
    text.setString(content);
    text.setCharacterSize(charSize);
    text.setFillColor(color);
    text.setPosition(pos);
    return text;
}

void zappy::InGame::drawScene(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);

    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            window.draw(_map[i][j].gridSprite);
        }
    };

    if (_selectedTile.x >= 0 && _selectedTile.y >= 0 && _selectedTile.x < _mapWidth && _selectedTile.y < _mapHeight) {
        const sf::Sprite& gridSprite = _map[_selectedTile.x][_selectedTile.y].gridSprite;
        sf::FloatRect bounds = gridSprite.getGlobalBounds();
        // Draw a colored border around the selected tile
        sf::RectangleShape border;
        border.setSize(sf::Vector2f(bounds.width, bounds.height));
        border.setPosition(bounds.left, bounds.top);
        border.setOutlineThickness(5.0f);
        border.setOutlineColor(sf::Color::Red);
        border.setFillColor(sf::Color::Transparent);
        window.draw(border);

        // Draw the content bar
        window.draw(_contentBarSprite);

        ressources_t quantity = _map[_selectedTile.x][_selectedTile.y].content.quantity;

        sf::Text food_text = setText(
            std::to_string(quantity.food),
            sf::Vector2f(710, 985),
            30,
            sf::Color::White);
        window.draw(food_text);

        sf::Text linemate_text = setText(
            std::to_string(quantity.linemate),
            sf::Vector2f(802, 1015),
            20,
            sf::Color::White
        );
        window.draw(linemate_text);

        sf::Text deraumere_text = setText(
            std::to_string(quantity.deraumere),
            sf::Vector2f(892, 1015),
            20,
            sf::Color::White
        );
        window.draw(deraumere_text);

        sf::Text sibur_text = setText(
            std::to_string(quantity.sibur),
            sf::Vector2f(982, 1015),
            20,
            sf::Color::White
        );
        window.draw(sibur_text);

        sf::Text mendiane_text = setText(
            std::to_string(quantity.mendiane),
            sf::Vector2f(1072, 1015),
            20,
            sf::Color::White
        );
        window.draw(mendiane_text);

        sf::Text phiras_text = setText(
            std::to_string(quantity.phiras),
            sf::Vector2f(1162, 1015),
            20,
            sf::Color::White
        );
        window.draw(phiras_text);

        sf::Text thystame_text = setText(
            std::to_string(quantity.thystame),
            sf::Vector2f(1252, 1015),
            20,
            sf::Color::White
        );
        window.draw(thystame_text);
    }

    drawRessources(window);
    drawPnjs(window);
}
