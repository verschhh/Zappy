/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** inGame.cpp
*/

#include "../../includes/scenes.hpp"

zappy::InGame::InGame(Connection& connection, int mapWidth, int mapHeight, std::shared_ptr<int> deathCounter)
    : _connection(connection), _mapWidth(mapWidth), _mapHeight(mapHeight)
{
    this->_deathCounter = deathCounter;
    setIndexScene(1);
    createMap();
    loadTextures();
    setRessourcesInMap();
}

zappy::InGame::~InGame() {}

void zappy::InGame::loadTextures()
{
    loadFont();

    if (!_backgroundTexture.loadFromFile("gui/assets/images/space.jpg"))
        throw AScene::SceneException("Error: cannot load in game background texture");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));

    if (!_contentBarTexture.loadFromFile("gui/assets/hud/contentBar.png"))
        throw AScene::SceneException("Error: cannot load contentBar.png");
    setSpriteProperties(_contentBarSprite, _contentBarTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 1005));

    if (!_levelBarTexture.loadFromFile("gui/assets/hud/levelBar.png"))
        throw AScene::SceneException("Error: cannot load levelBar.png");
    setSpriteProperties(_levelBarSprite, _levelBarTexture, sf::Vector2f(1.25, 1.25), sf::Vector2f(1873, 400));

    if (!_deathCounterTexture.loadFromFile("gui/assets/hud/deathCounter.png"))
        throw AScene::SceneException("Error: cannot load deathCounter.png");
    setSpriteProperties(_deathCounterSprite, _deathCounterTexture, sf::Vector2f(1.25, 1.25), sf::Vector2f(1873, 800));

    int nbPnjTextures = 3;
    for (int i = 0; i < nbPnjTextures; i++) {
        pnjTextures_t pnjTextures;
        if (!pnjTextures.left.loadFromFile("gui/assets/pnj/pnj" + std::to_string(i + 1) + "_left.png"))
            throw AScene::SceneException("Error: cannot load pnj" + std::to_string(i + 1) + "_left.png");

        if (!pnjTextures.right.loadFromFile("gui/assets/pnj/pnj" + std::to_string(i + 1) + "_right.png"))
            throw AScene::SceneException("Error: cannot load pnj" + std::to_string(i + 1) + "_right.png");

        _pnjTextures.push_back(pnjTextures);
    }

    int nbCrystalsTextures = 6;
    for (int i = 0; i < nbCrystalsTextures; i++) {
        sf::Texture texture;
        if (!texture.loadFromFile("gui/assets/objects/crystals/crystal" + std::to_string(i + 1) + ".png"))
            throw AScene::SceneException("Error: cannot load crystal" + std::to_string(i + 1) + ".png");

        _ressourcesTextures.push_back(texture);
    }

    if (!_foodTexture.loadFromFile("gui/assets/objects/apple.png"))
        throw AScene::SceneException("Error: cannot load apple.png");

    // ! TEMP
    // createPnj(10, 4, NORTH);
    // createPnj(5, 8, WEST);
    // createPnj(5, 8, EAST);
    // createPnj(10, 2, SOUTH);
    // createPnj(10, 3, SOUTH);

    // createRessources(10, 6, {1, 1, 1, 1, 1, 1, 1});
    // createRessources(2, 1, {1, 0, 0, 0, 0, 0, 0});
    // createRessources(2, 2, {0, 1, 0, 0, 0, 0, 0});
    // createRessources(2, 3, {0, 0, 1, 0, 0, 0, 0});
    // createRessources(2, 4, {0, 0, 0, 1, 0, 0, 0});
    // createRessources(2, 5, {0, 0, 0, 0, 1, 0, 0});
    // createRessources(2, 6, {0, 0, 0, 0, 0, 1, 0});
    // createRessources(2, 7, {0, 0, 0, 0, 0, 0, 1});
    // createRessources(5, 8, {1, 1, 1, 1, 1, 1, 1});
}

void zappy::InGame::setRessourcesInMap(void)
{
    for (int i = 0; i < _mapWidth; i++) {
        for (int j = 0; j < _mapHeight; j++) {
            sf::Sprite foodSprite;
            foodSprite.setTexture(_foodTexture);
            foodSprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
            foodSprite.setOrigin(20 / 2, 20 / 2);
            sf::Vector2f foodPosition = _map[i][j].gridSprite.getPosition();
            int randomOffsetX = randomNumber(-25, 25);
            int randomOffsetY = randomNumber(-25, 25);
            foodSprite.setPosition(foodPosition.x + randomOffsetX, foodPosition.y + randomOffsetY);
            _map[i][j].content.foodSprite = foodSprite;

            sf::Sprite linemateSprite;
            linemateSprite.setTexture(_ressourcesTextures[0]);
            linemateSprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
            linemateSprite.setOrigin(20 / 2, 20 / 2);
            sf::Vector2f linematePosition = _map[i][j].gridSprite.getPosition();
            randomOffsetX = randomNumber(-25, 25);
            randomOffsetY = randomNumber(-25, 25);
            linemateSprite.setPosition(linematePosition.x + randomOffsetX, linematePosition.y + randomOffsetY);
            _map[i][j].content.linemateSprite = linemateSprite;

            sf::Sprite deraumereSprite;
            deraumereSprite.setTexture(_ressourcesTextures[1]);
            deraumereSprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
            deraumereSprite.setOrigin(20 / 2, 20 / 2);
            sf::Vector2f deraumerePosition = _map[i][j].gridSprite.getPosition();
            randomOffsetX = randomNumber(-25, 25);
            randomOffsetY = randomNumber(-25, 25);
            deraumereSprite.setPosition(deraumerePosition.x + randomOffsetX, deraumerePosition.y + randomOffsetY);
            _map[i][j].content.deraumereSprite = deraumereSprite;

            sf::Sprite siburSprite;
            siburSprite.setTexture(_ressourcesTextures[2]);
            siburSprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
            siburSprite.setOrigin(20 / 2, 20 / 2);
            sf::Vector2f siburPosition = _map[i][j].gridSprite.getPosition();
            randomOffsetX = randomNumber(-25, 25);
            randomOffsetY = randomNumber(-25, 25);
            siburSprite.setPosition(siburPosition.x + randomOffsetX, siburPosition.y + randomOffsetY);
            _map[i][j].content.siburSprite = siburSprite;

            sf::Sprite mendianeSprite;
            mendianeSprite.setTexture(_ressourcesTextures[3]);
            mendianeSprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
            mendianeSprite.setOrigin(20 / 2, 20 / 2);
            sf::Vector2f mendianePosition = _map[i][j].gridSprite.getPosition();
            randomOffsetX = randomNumber(-25, 25);
            randomOffsetY = randomNumber(-25, 25);
            mendianeSprite.setPosition(mendianePosition.x + randomOffsetX, mendianePosition.y + randomOffsetY);
            _map[i][j].content.mendianeSprite = mendianeSprite;

            sf::Sprite phirasSprite;
            phirasSprite.setTexture(_ressourcesTextures[4]);
            phirasSprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
            phirasSprite.setOrigin(20 / 2, 20 / 2);
            sf::Vector2f phirasPosition = _map[i][j].gridSprite.getPosition();
            randomOffsetX = randomNumber(-25, 25);
            randomOffsetY = randomNumber(-25, 25);
            phirasSprite.setPosition(phirasPosition.x + randomOffsetX, phirasPosition.y + randomOffsetY);
            _map[i][j].content.phirasSprite = phirasSprite;

            sf::Sprite thystameSprite;
            thystameSprite.setTexture(_ressourcesTextures[5]);
            thystameSprite.setScale(sf::Vector2f(_scaleFactor, _scaleFactor));
            thystameSprite.setOrigin(20 / 2, 20 / 2);
            sf::Vector2f thystamePosition = _map[i][j].gridSprite.getPosition();
            randomOffsetX = randomNumber(-25, 25);
            randomOffsetY = randomNumber(-25, 25);
            thystameSprite.setPosition(thystamePosition.x + randomOffsetX, thystamePosition.y + randomOffsetY);
            _map[i][j].content.thystameSprite = thystameSprite;

            //! Temp values
            // _map[i][j].content.quantity = {randomNumber(0, 5), randomNumber(0, 5), randomNumber(0, 5), randomNumber(0, 5), randomNumber(0, 5), randomNumber(0, 5), randomNumber(0, 5)};
        }
    }
}
