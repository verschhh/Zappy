/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** gui.hpp
*/

#pragma once

#include <iostream>

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

            ~Gui() {

            }

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
        private:
            int _port;
            std::string _machine;
    };
}
