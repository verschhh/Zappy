/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** main.cpp
*/

#include "../includes/gui.hpp"

void usage(void)
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cout << "\tport\tis the port number" << std::endl;
    std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

int main(int ac, char **av)
{
    if (ac == 2 && std::string(av[1]) == "-help") {
        usage();
        return (0);
    } else if (ac != 5) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return (84);
    }
    std::cout << "GUI" << std::endl;
    return (0);
}
