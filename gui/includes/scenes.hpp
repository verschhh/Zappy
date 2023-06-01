/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** scenes.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace zappy {
    class IScene {
        public:
            virtual void handleEvents(sf::RenderWindow& window) = 0;
            virtual void drawScene(sf::RenderWindow& window) = 0;
            virtual void setSpriteProperties(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position) = 0;
    };

    class AScene : public IScene {
        public:
            AScene() = default;
            ~AScene() = default;

            void setSpriteProperties(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position) {
                sprite.setTexture(texture);
                sprite.setScale(scale);
                sprite.setPosition(position);
            }
    };

    class Menu : public AScene {
        public:
            Menu();
            ~Menu();

            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window);

            void loadTextures();
            void handleHoverButtons(sf::Vector2i mousePosition);
            void handleMouseClicks(sf::RenderWindow &window, sf::Event event, sf::Vector2i mousePosition);

        private:
            sf::Texture _backgroundTexture;
            sf::Sprite _backgroundSprite;

            sf::Texture _logoTexture;
            sf::Sprite _logoSprite;

            sf::Texture _playButtonTexture;
            sf::Sprite _playButtonSprite;

            sf::Texture _quitButtonTexture;
            sf::Sprite _quitButtonSprite;
    };
}