/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** scenes.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

static const int WINDOW_WIDTH = 1920;
static const int WINDOW_HEIGHT = 1080;

namespace zappy {
    class IScene {
        public:
            virtual void handleEvents(sf::RenderWindow& window) = 0;
            virtual void drawScene(sf::RenderWindow& window, sf::Clock clock) = 0;
            virtual void setSpriteProperties(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position) = 0;

            virtual int getIndexScene(void) = 0;
            virtual void setIndexScene(int indexScene) = 0;
    };

    class AScene : public IScene {
        public:
            AScene() = default;
            ~AScene() = default;

            int getIndexScene(void) {
                return (_indexScene);
            }
            void setIndexScene(int indexScene) {
                _indexScene = indexScene;
            }

            void setSpriteProperties(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position) {
                sprite.setTexture(texture);
                sprite.setScale(scale);
                sprite.setPosition(position);

                sf::FloatRect spriteBounds = sprite.getLocalBounds();
                sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
            }

            class SceneException : public std::exception {
                public:
                    SceneException(const std::string &message) throw()
                    : _message(message) {};
                    ~SceneException() throw() {};
                    const char *what() const throw() { return (_message.c_str()); };
                private:
                    std::string _message;
            };

            private:
                int _indexScene;
    };

    class Menu : public AScene {
        public:
            Menu();
            ~Menu();

            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window, sf::Clock clock);

            void loadTextures();
            void handleHoverButtons(sf::Vector2i mousePosition);
            void handleMouseClicks(sf::RenderWindow &window, sf::Event event, sf::Vector2i mousePosition);
            void animateStar(sf::Clock clock, float baseScale);

        private:
            sf::Texture _backgroundTexture;
            sf::Sprite _backgroundSprite;

            sf::Texture _logoTexture;
            sf::Sprite _logoSprite;

            sf::Texture _playButtonTexture;
            sf::Sprite _playButtonSprite;

            sf::Texture _quitButtonTexture;
            sf::Sprite _quitButtonSprite;

            sf::Texture _shiningLightTexture;
            sf::Sprite _shiningLightSprite;
    };

    class InGame : public AScene {
        public:
            InGame(int mapWidth, int mapHeight);
            ~InGame();

            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window, sf::Clock clock);

            void loadTextures();
            void createMap();

        private:
            int _mapWidth;
            int _mapHeight;
            sf::Texture _gridTexture;
            std::vector<std::vector<sf::Sprite>> _map;

            sf::Texture _backgroundTexture;
            sf::Sprite _backgroundSprite;
    };
}
