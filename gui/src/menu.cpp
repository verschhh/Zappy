/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** menu.cpp
*/

#include "../includes/scenes.hpp"

zappy::Menu::Menu(Connection& connection) : _connection(connection)
{
    setIndexScene(0);
    loadTextures();
}

zappy::Menu::~Menu() {}

void zappy::Menu::loadTextures() {
    if (!_backgroundTexture.loadFromFile("gui/assets/images/background_space.png"))
        throw AScene::SceneException("Error: cannot load menu background texture");
    setSpriteProperties(_backgroundSprite, _backgroundTexture, sf::Vector2f(1, 1), sf::Vector2f(960, 540));

    if (!_logoTexture.loadFromFile("gui/assets/zappyLogo.png"))
        throw AScene::SceneException("Error: cannot load menu logo texture");
    setSpriteProperties(_logoSprite, _logoTexture, sf::Vector2f(15, 15), sf::Vector2f(960, 420));

    if (!_playButtonTexture.loadFromFile("gui/assets/buttons/play_button_still.png"))
        throw AScene::SceneException("Error: cannot load menu play button texture");
    setSpriteProperties(_playButtonSprite, _playButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(760, 800));

    if (!_quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png"))
        throw AScene::SceneException("Error: cannot load menu quit button texture");
    setSpriteProperties(_quitButtonSprite, _quitButtonTexture, sf::Vector2f(4, 4), sf::Vector2f(1160, 800));

    if (!_shiningLightTexture.loadFromFile("gui/assets/objects/shiningLight.png"))
        throw AScene::SceneException("Error: cannot load menu shining light texture");
    setSpriteProperties(_shiningLightSprite, _shiningLightTexture, sf::Vector2f(6, 6), sf::Vector2f(1610, 275));
}

void zappy::Menu::handleHoverButtons(sf::Vector2i mousePosition)
{
    if (_playButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        _playButtonTexture.loadFromFile("gui/assets/buttons/play_button_hovered.png");
        _playButtonSprite.setTexture(_playButtonTexture);
    } else {
        _playButtonTexture.loadFromFile("gui/assets/buttons/play_button_still.png");
        _playButtonSprite.setTexture(_playButtonTexture);
    }

    if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        _quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_hovered.png");
        _quitButtonSprite.setTexture(_quitButtonTexture);
    } else {
        _quitButtonTexture.loadFromFile("gui/assets/buttons/quit_button_still.png");
        _quitButtonSprite.setTexture(_quitButtonTexture);
    }
}

void zappy::Menu::handleMouseClicks(sf::RenderWindow &window, sf::Event event, sf::Vector2i mousePosition)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_playButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            setIndexScene(1);
        }
        if (_quitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            window.close();
        }
    }
}

void zappy::Menu::handleEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        handleMouseClicks(window, event, mousePosition);
        handleHoverButtons(mousePosition);
    }
}

void zappy::Menu::animateStar(float baseScale)
{
    float initialRotation = 0.0f;
    float targetRotation = 360.0f;
    float animationDuration = 1.5f;


    float initialScale = 1.0f;
    float targetScale = 1.5f;

    float elapsedTime = _shiningLightClock.getElapsedTime().asSeconds();

    float scaledElapsedTime = std::fmod(elapsedTime, animationDuration);

    float rotation = initialRotation + (targetRotation - initialRotation) * (scaledElapsedTime / animationDuration);
    _shiningLightSprite.setRotation(rotation);

    float scale;
    if (scaledElapsedTime < animationDuration / 2.0f) {
        scale = initialScale + ((targetScale - initialScale) * 2.0f * scaledElapsedTime) / animationDuration;
    } else {
        scale = targetScale - ((targetScale - initialScale) * 2.0f * (scaledElapsedTime - animationDuration / 2.0f)) / animationDuration;
    }
    _shiningLightSprite.setScale(scale * baseScale, scale * baseScale);

}

void zappy::Menu::drawScene(sf::RenderWindow& window) {
    window.draw(_backgroundSprite);
    window.draw(_logoSprite);
    window.draw(_playButtonSprite);
    window.draw(_quitButtonSprite);

    animateStar(6.0f);
    window.draw(_shiningLightSprite);
}
