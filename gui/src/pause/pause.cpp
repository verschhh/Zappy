/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** pause.cpp
*/

#include "../../includes/gui.hpp"

zappy::Pause::Pause(Connection& connection, std::shared_ptr<Stats> stats)
{
    this->_stats = stats;
    (void)connection;
    setIndexScene(3);
    loadTextures();
}

zappy::Pause::~Pause(void)
{

}

void zappy::Pause::loadTextures(void)
{
    loadFont();

    if (!_backgroundTexture.loadFromFile("gui/assets/images/space.jpg"))
        throw AScene::SceneException("Error: cannot load space.png");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));

    if (!_backButtonTexture.loadFromFile("gui/assets/buttons/back_button_still.png"))
        throw AScene::SceneException("Error: cannot load menu back button texture");

    if (!_backButtonHoveredTexture.loadFromFile("gui/assets/buttons/back_button_hovered.png"))
        throw AScene::SceneException("Error: cannot load menu back button texture");

    setSpriteProperties(_backButtonSprite, _backButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(760, 800));

    if (!_quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png"))
        throw AScene::SceneException("Error: cannot load menu quit button texture");

    if (!_quitButtonHoveredTexture.loadFromFile("gui/assets/buttons/quit_button_hovered.png"))
        throw AScene::SceneException("Error: cannot load menu quit button texture");

    setSpriteProperties(_quitButtonSprite, _quitButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(1160, 800));

    if (!_statsLogoTexture.loadFromFile("gui/assets/hud/statisticsLogo.png"))
        throw AScene::SceneException("Error: cannot load stats logo texture");
    setSpriteProperties(_statsLogoSprite, _statsLogoTexture, sf::Vector2f(7, 7), sf::Vector2f(960, 200));

    if (!_pnjsLogoTexture.loadFromFile("gui/assets/hud/pnjsLogo.png"))
        throw AScene::SceneException("Error: cannot load pnjLogo.png");
    setSpriteProperties(_pnjsLogoSprite, _pnjsLogoTexture, sf::Vector2f(5, 5), sf::Vector2f(350, 350));

    if (!_deathsLogoTexture.loadFromFile("gui/assets/hud/deathsLogo.png"))
        throw AScene::SceneException("Error: cannot load deathsLogo.png");
    setSpriteProperties(_deathsLogoSprite, _deathsLogoTexture, sf::Vector2f(5, 5), sf::Vector2f(350, 450));

    if (!_ressourcesLogoTexture.loadFromFile("gui/assets/hud/ressourcesLogo.png"))
        throw AScene::SceneException("Error: cannot load ressourcesLogo.png");
    setSpriteProperties(_ressourcesLogoSprite, _ressourcesLogoTexture, sf::Vector2f(5, 5), sf::Vector2f(350, 550));

    if (!_foodTexture.loadFromFile("gui/assets/objects/apple.png"))
        throw AScene::SceneException("Error: cannot load apple.png");
    setSpriteProperties(_foodSprite, _foodTexture, sf::Vector2f(2, 2), sf::Vector2f(550, 550));

    if (!_linemateTexture.loadFromFile("gui/assets/objects/crystals/crystal1.png"))
        throw AScene::SceneException("Error: cannot load crystal1.png");
    setSpriteProperties(_linemateSprite, _linemateTexture, sf::Vector2f(2, 2), sf::Vector2f(750, 550));

    if (!_deraumereTexture.loadFromFile("gui/assets/objects/crystals/crystal2.png"))
        throw AScene::SceneException("Error: cannot load crystal2.png");
    setSpriteProperties(_deraumereSprite, _deraumereTexture, sf::Vector2f(2, 2), sf::Vector2f(950, 550));

    if (!_siburTexture.loadFromFile("gui/assets/objects/crystals/crystal3.png"))
        throw AScene::SceneException("Error: cannot load crystal3.png");
    setSpriteProperties(_siburSprite, _siburTexture, sf::Vector2f(2, 2), sf::Vector2f(1150, 550));

    if (!_mendianeTexture.loadFromFile("gui/assets/objects/crystals/crystal4.png"))
        throw AScene::SceneException("Error: cannot load crystal4.png");
    setSpriteProperties(_mendianeSprite, _mendianeTexture, sf::Vector2f(2, 2), sf::Vector2f(1350, 550));

    if (!_phirasTexture.loadFromFile("gui/assets/objects/crystals/crystal5.png"))
        throw AScene::SceneException("Error: cannot load crystal5.png");
    setSpriteProperties(_phirasSprite, _phirasTexture, sf::Vector2f(2, 2), sf::Vector2f(1550, 550));

    if (!_thystameTexture.loadFromFile("gui/assets/objects/crystals/crystal6.png"))
        throw AScene::SceneException("Error: cannot load crystal6.png");
    setSpriteProperties(_thystameSprite, _thystameTexture, sf::Vector2f(2, 2), sf::Vector2f(1750, 550));
}
