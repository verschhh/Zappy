/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** scenes.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <random>
#include "network.hpp"
#include <array>
#include <memory>

static const int WINDOW_WIDTH = 1920;
static const int WINDOW_HEIGHT = 1080;

namespace zappy {
    enum scenes {
        MENU,
        IN_GAME,
        END_GAME,
        PAUSE
    };

    class Stats {
        public:
            Stats(int indexScene) {
                _indexScene = indexScene;

                _pnjCounter = 0;
                _deathCounter = 0;
                _foodCounter = 0;
                _linemateCounter = 0;
                _deraumereCounter = 0;
                _siburCounter = 0;
                _mendianeCounter = 0;
                _phirasCounter = 0;
                _thystameCounter = 0;
                _winnerName = "default";
            }

            ~Stats() = default;

            //* Index Scene
            void setIndexScene(int indexScene) {
                _indexScene = indexScene;
            }
            int getIndexScene(void) {
                return (_indexScene);
            }

            //* Getters
            int getPnjCounter(void) {
                return (_pnjCounter);
            }
            int getDeathCounter(void) {
                return (_deathCounter);
            }
            int getFoodCounter(void) {
                return (_foodCounter);
            }
            int getLinemateCounter(void) {
                return (_linemateCounter);
            }
            int getDeraumereCounter(void) {
                return (_deraumereCounter);
            }
            int getSiburCounter(void) {
                return (_siburCounter);
            }
            int getMendianeCounter(void) {
                return (_mendianeCounter);
            }
            int getPhirasCounter(void) {
                return (_phirasCounter);
            }
            int getThystameCounter(void) {
                return (_thystameCounter);
            }
            std::string getWinnerName(void) {
                return (_winnerName);
            }

            //* Setters
            void setPnjCounter(int pnjCounter) {
                _pnjCounter = pnjCounter;
            }
            void increaseDeathCounter(void) {
                _deathCounter++;
            }
            void setFoodCounter(int foodCounter) {
                _foodCounter = foodCounter;
            }
            void setLinemateCounter(int linemateCounter) {
                _linemateCounter = linemateCounter;
            }
            void setDeraumereCounter(int deraumereCounter) {
                _deraumereCounter = deraumereCounter;
            }
            void setSiburCounter(int siburCounter) {
                _siburCounter = siburCounter;
            }
            void setMendianeCounter(int mendianeCounter) {
                _mendianeCounter = mendianeCounter;
            }
            void setPhirasCounter(int phirasCounter) {
                _phirasCounter = phirasCounter;
            }
            void setThystameCounter(int thystameCounter) {
                _thystameCounter = thystameCounter;
            }
            void setWinnerName(std::string winnerName) {
                _winnerName = winnerName;
            }

        private:
            int _indexScene;

            int _pnjCounter;
            int _deathCounter;
            int _foodCounter;
            int _linemateCounter;
            int _deraumereCounter;
            int _siburCounter;
            int _mendianeCounter;
            int _phirasCounter;
            int _thystameCounter;
            std::string _winnerName;
    };

    class IScene {
        public:
            virtual void handleEvents(sf::RenderWindow& window) = 0;
            virtual void drawScene(sf::RenderWindow& window) = 0;
            virtual void setSpriteProperties(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position) = 0;
    };

    class AScene : public IScene {
        protected:
            std::shared_ptr<Stats> _stats;

        public:
            AScene() = default;
            ~AScene() = default;

            void loadFont(void) {
                if (!_font.loadFromFile("gui/assets/font/DeterminationMono.ttf"))
                    throw AScene::SceneException("Error: cannot load DeterminationMono.ttf");
            }
            sf::Font getFont(void) {
                return (_font);
            }

            void setSpriteProperties(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position) {
                sprite.setTexture(texture);
                sprite.setScale(scale);
                sprite.setPosition(position);

                sf::FloatRect spriteBounds = sprite.getLocalBounds();
                sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
            }

            sf::Text setText(std::string content, sf::Vector2f pos, int charSize, sf::Color color)
            {
                sf::Text text;
                text.setFont(_font);
                text.setString(content);
                text.setCharacterSize(charSize);
                text.setFillColor(color);
                text.setPosition(pos);
                return text;
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
                sf::Font _font;
    };

    class Menu : public AScene {
        public:
            //* Constructor / Destructor
            Menu(Connection& connection, std::shared_ptr<Stats> stats);
            ~Menu(void);

            void loadTextures(void);

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
            InGame(Connection& _connection, int mapWidth, int mapHeight, std::shared_ptr<Stats> stats);
            ~InGame(void);

            void createMap(void);
            void loadTextures(void);
            void setRessourcesInMap(void);

            //* Abstract functions
            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window);

            //* Events
            void clickTile(sf::RenderWindow& window);

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
                int number;
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
            void createPnj(int number, int x, int y, pnjOrientation orientation, int level);
            void erasePnj(int number);

            void drawPnjs(sf::RenderWindow& window);
            void drawRessources(sf::RenderWindow& window);
            void drawRessourceBar(sf::RenderWindow& window);
            void drawLevelsBar(sf::RenderWindow& window);
            void drawDeathCounter(sf::RenderWindow& window);

            void updateScene(void);
            void updateMap(void);
            void parseQueue(void);
            void pnwHandler(std::vector<std::string>& arguments);
            void enwHandler(std::vector<std::string>& arguments);
            void eboHandler(std::vector<std::string>& arguments);
            void pdiHandler(std::vector<std::string>& arguments);
            void segHandler(std::vector<std::string>& arguments);
            void updatePnj(void);
            void updateStats(void);

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
            sf::Text _foodText;
            sf::Text _linemateText;
            sf::Text _deraumereText;
            sf::Text _siburText;
            sf::Text _mendianeText;
            sf::Text _phirasText;
            sf::Text _thystameText;

            //* Class Values
            float _scaleFactor;

            //* Tile selection
            sf::Vector2i _selectedTile;
            sf::Texture _contentBarTexture;
            sf::Sprite _contentBarSprite;

            //* Levels Bar
            sf::Texture _levelBarTexture;
            sf::Sprite _levelBarSprite;

            //* Death Counter
            sf::Texture _deathCounterTexture;
            sf::Sprite _deathCounterSprite;
    };

    class EndGame : public AScene {
        public:
            //* Constructor / Destructor
            EndGame(Connection &connection, std::shared_ptr<Stats> stats);
            ~EndGame(void);

            //* Abstract functions
            void loadTextures(void);
            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window);
        private:
            //* Background
            sf::Texture _backgroundTexture;
            sf::Sprite _backgroundSprite;

            sf::Texture _quitButtonTexture;
            sf::Texture _quitButtonHoveredTexture;
            sf::Sprite _quitButtonSprite;

            sf::Text _winnerText;
    };

    class Pause : public AScene {
        public:
            //* Constructor / Destructor
            Pause(Connection &connection, std::shared_ptr<Stats> stats);
            ~Pause(void);

            //* Abstract functions
            void loadTextures(void);
            void handleEvents(sf::RenderWindow& window);
            void drawScene(sf::RenderWindow& window);

        private:
            sf::Texture _backgroundTexture;
            sf::Sprite _backgroundSprite;

            sf::Texture _quitButtonTexture;
            sf::Texture _quitButtonHoveredTexture;
            sf::Sprite _quitButtonSprite;

            sf::Texture _backButtonTexture;
            sf::Texture _backButtonHoveredTexture;
            sf::Sprite _backButtonSprite;

            //* Stats
            sf::Texture _statsLogoTexture;
            sf::Sprite _statsLogoSprite;

            sf::Texture _pnjsLogoTexture;
            sf::Sprite _pnjsLogoSprite;
            sf::Text _pnjText;

            sf::Texture _deathsLogoTexture;
            sf::Sprite _deathsLogoSprite;
            sf::Text _deathText;

            sf::Texture _ressourcesLogoTexture;
            sf::Sprite _ressourcesLogoSprite;

            sf::Texture _foodTexture;
            sf::Sprite _foodSprite;
            sf::Text _foodText;

            sf::Texture _linemateTexture;
            sf::Sprite _linemateSprite;
            sf::Text _linemateText;

            sf::Texture _deraumereTexture;
            sf::Sprite _deraumereSprite;
            sf::Text _deraumereText;

            sf::Texture _siburTexture;
            sf::Sprite _siburSprite;
            sf::Text _siburText;

            sf::Texture _mendianeTexture;
            sf::Sprite _mendianeSprite;
            sf::Text _mendianeText;

            sf::Texture _phirasTexture;
            sf::Sprite _phirasSprite;
            sf::Text _phirasText;

            sf::Texture _thystameTexture;
            sf::Sprite _thystameSprite;
            sf::Text _thystameText;
    };
}
