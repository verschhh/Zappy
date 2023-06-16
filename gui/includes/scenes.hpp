/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** scenes.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "network.hpp"
#include <array>

static const int WINDOW_WIDTH = 1920;
static const int WINDOW_HEIGHT = 1080;

namespace zappy {
    class IScene {
        public:
            virtual void handleEvents(sf::RenderWindow& window) = 0;
            virtual void drawScene(sf::RenderWindow& window) = 0;
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
            //* Constructor / Destructor
            Menu(Connection& connection);
            ~Menu();

            void loadTextures();

            //* Abstract functions
            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window);

            //* Class methods
            void handleHoverButtons(sf::Vector2i mousePosition);
            void handleMouseClicks(sf::RenderWindow &window, sf::Event event, sf::Vector2i mousePosition);
            void animateStar(float baseScale);

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
            sf::Clock _shiningLightClock;

            Connection& _connection;
    };

    class InGame : public AScene {
        public:
            //* Constructor / Destructor
            InGame(Connection& _connection, int mapWidth, int mapHeight);
            ~InGame();

            void createMap();
            void loadTextures();
            void setRessourcesInMap(void);

            //* Abstract functions
            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window);

            //* Tools
            int randomNumber(int min, int max);
            std::vector<std::string> splitString(std::string str, char delimiter);

            //* Structures
            typedef struct pnjTextures_s {
                sf::Texture left;
                sf::Texture right;
            } pnjTextures_t;

            typedef struct ressources_s {
                int food = 0;
                int linemate = 0;
                int deraumere = 0;
                int sibur = 0;
                int mendiane = 0;
                int phiras = 0;
                int thystame = 0;
            } ressources_t;

            enum pnjOrientation {
                NORTH,
                EAST,
                SOUTH,
                WEST
            };

            typedef struct pnj_s {
                int type;
                sf::IntRect rect = sf::IntRect(0, 0, 32, 32);
                sf::Sprite sprite;
                sf::Vector2f position;
                sf::Vector2f offset;
                ressources_t inventory;
                int level = 1;
                pnjOrientation orientation;
            } pnj_t;

            typedef struct tile_content_s {
                ressources_t quantity;
                sf::Sprite foodSprite;
                sf::Sprite linemateSprite;
                sf::Sprite deraumereSprite;
                sf::Sprite siburSprite;
                sf::Sprite mendianeSprite;
                sf::Sprite phirasSprite;
                sf::Sprite thystameSprite;
            } tile_content_t;

            typedef struct tile_s {
                sf::Sprite gridSprite;
                tile_content_t content;
            } tile_t;

            //* Class methods
            void createPnj(int x, int y, pnjOrientation orientation);

            void drawPnjs(sf::RenderWindow& window);
            void drawRessources(sf::RenderWindow& window);
            void drawRessourceBar(sf::RenderWindow& window);
            void drawLevelsBar(sf::RenderWindow& window);

            void updateScene(void);

            sf::Text setText(std::string content, sf::Vector2f pos, int charSize, sf::Color color);

        private:
            //* Background
            sf::Texture _backgroundTexture;
            sf::Sprite _backgroundSprite;

            //* Connection
            Connection& _connection;

            //* Map
            int _mapWidth;
            int _mapHeight;
            std::vector<sf::Texture> _gridTextures;
            std::vector<std::vector<tile_t>> _map;

            //* PNJ
            std::vector<pnjTextures_t> _pnjTextures;
            std::vector<pnj_t> _pnjs;
            std::vector<sf::Clock> _pnjMoveClocks;

            //* Ressources
            sf::Texture _foodTexture;
            std::vector<sf::Texture> _ressourcesTextures;

            //* Class Values
            float _scaleFactor;
            sf::Font _font;

            //* Tile selection
            sf::Vector2i _selectedTile;
            sf::Texture _contentBarTexture;
            sf::Sprite _contentBarSprite;

            //* Levels Bar
            sf::Texture _levelBarTexture;
            sf::Sprite _levelBarSprite;
    };
}
