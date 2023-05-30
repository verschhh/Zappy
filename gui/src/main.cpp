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

int guiStart(int port, std::string machine)
{
    zappy::Gui gui(port, machine);

    try {
        gui.run();
    } catch (zappy::Gui::GuiException &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }

    return (0);
}

int guiSetup(int ac, char **av)
{
    int port = 0;
    std::string machine = "localhost";

    int option;
    while ((option = getopt(ac, av, "p:h:")) != -1) {
        switch (option) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'h':
                machine = optarg;
                break;
            default:
                std::cerr << "Invalid argument" << std::endl;
                return (84);
        }
    }

    if (port == 0) {
        std::cerr << "Port is missing" << std::endl;
        return (84);
    }

    return (guiStart(port, machine));
}

int main(int ac, char **av)
{
    if (ac == 2 && std::string(av[1]) == "-help") {
        usage();
        return (0);
    } else if (ac != 5 && ac != 3) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return (84);
    }
    if (guiSetup(ac, av) == 84)
        return (84);
    return (0);
}
