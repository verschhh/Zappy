/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-zappy-kentin.paille
** File description:
** gui.cpp
*/

#include "../includes/gui.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

zappy::Gui::Gui(int port, std::string machine) : _connection(port, machine), _indexScene(0)
{
    try {
        _connection.connect();
        std::string response = _connection.receive();
        std::cout << response << std::endl;
    } catch (const std::runtime_error& e) {
        throw GuiException("Gui error: cannot connect to the server");
        return;
    }

    if (!_backgroundMusic.openFromFile("gui/assets/sfx/Aphex-Twin-Flim-Extended-Version.ogg"))
        throw GuiException("Gui error: cannot load background music");

    try {
        this->_stats = std::make_shared<Stats>();

        _scenes.push_back(std::make_shared<Menu>(_connection, this->_stats));

        int width = 20;
        int height = 10;

        _connection.send("msz\n");
        std::string response = _connection.receive();
        std::istringstream iss(response);
        std::string cmd;
        iss >> cmd >> width >> height;

        _scenes.push_back(std::make_shared<InGame>(_connection, width, height, this->_stats));

        _scenes.push_back(std::make_shared<EndGame>(_connection, this->_stats));

        _scenes.push_back(std::make_shared<Pause>(_connection, this->_stats));
    } catch (AScene::SceneException& e) {
        std::cerr << e.what() << std::endl;
        throw GuiException("Gui error: cannot load scenes");
    }
}

void zappy::Gui::setIcon(sf::RenderWindow& window) {
    sf::Image icon;
    if (!icon.loadFromFile("gui/assets/icons/zappyFavicon.png")) {
        throw GuiException("Error: cannot load icon");
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void zappy::Gui::run() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy", sf::Style::Fullscreen);
    setIcon(window);

    sf::Clock clock;

    _backgroundMusic.setLoop(true);
    _backgroundMusic.play();

    while (window.isOpen()) {
        _scenes[_indexScene]->setIndexScene(_indexScene);
        _scenes[_indexScene]->handleEvents(window);
        setIndexScene(_scenes[_indexScene]->getIndexScene());
        window.clear();
        _scenes[_indexScene]->drawScene(window);
        window.display();
    }
}
