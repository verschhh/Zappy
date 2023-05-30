/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** gui.hpp
*/

#pragma once

#include <iostream>
#include <getopt.h>
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace zappy {
    class Gui {
        public:
            Gui(int port) {
                _port = port;
                _machine = "localhost";
            }

            Gui(int port, std::string machine) {
                _port = port;
                _machine = machine;
            }

            ~Gui() {};

            //* Getters
            int getPort(void) {
                return (_port);
            }
            std::string getMachine(void) {
                return (_machine);
            }

            //* Setters
            void setPort(int port) {
                _port = port;
            }
            void setMachine(std::string machine) {
                _machine = machine;
            }

            //* Exception
            class GuiException : public std::exception {
                public:
                    GuiException(const std::string &message) throw()
                    : _message(message) {};
                    ~GuiException() throw() {};
                    const char *what() const throw() { return (_message.c_str()); };
                private:
                    std::string _message;
            };

            //* Methods
            void run();
            void setIcon(sf::RenderWindow& window);

        private:
            Menu menu;
            int _port;
            std::string _machine;
    };
}
