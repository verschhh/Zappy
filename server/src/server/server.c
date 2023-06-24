/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** server.c
*/

#include "../includes/zappy.h"

void reset_timeval(serv_t *serv)
{
    double min = 1;
    double freq = serv->freq;
    double res = min / freq;

    serv->new_tick = true;
    serv->tv.tv_sec = res;
    serv->tv.tv_usec = res * 1000000;
}

struct termios init_signal(void)
{
    struct termios old_termios;
    struct termios new_termios;

    setvbuf(stdout, NULL, _IONBF, 0);
    tcgetattr(0, &old_termios);
    signal(SIGINT, crtld_handler);
    new_termios = old_termios;
    new_termios.c_cc[VEOF] = 3;
    new_termios.c_cc[VINTR] = 4;
    tcsetattr(0, TCSANOW, &new_termios);
    return old_termios;
}

void game_state(serv_t *serv, fd_set *readfds, fd_set tmpfds)
{
    for (int i = 0; i <= serv->max_sd; i++) {
        if (!FD_ISSET(i, &tmpfds))
            continue;
        if (i == serv->sockfd) {
            accept_new_client(readfds, serv);
            serv->new_tick = false;
        }
        if (serv->new_tick)
            receive_client_msg(i, readfds, serv);
    }
    return;
}

int server(fd_set *readfds, serv_t *serv)
{
    fd_set tmpfds;

    FD_ZERO(&tmpfds);
    tmpfds = *readfds;
    reset_timeval(serv);
    if (select(serv->max_sd + 1, &tmpfds, NULL, NULL, NULL) < 0)
        print_and_exit("ERROR on select");
    game_state(serv, readfds, tmpfds);
    return 0;
}

int start_server(args_t *args)
{
    struct termios old_termios = init_signal();
    serv_t *serv = serv_ctor(args);
    fd_set readfds;
    FD_ZERO(&readfds);
    if (serv == NULL) {
        free(args);
        return 84;
    }
    FD_SET(serv->sockfd, &readfds);
    serv->max_sd = serv->sockfd;
    signal(SIGINT, crtld_handler);
    while (1) {
        server(&readfds, serv);
    }
    tcsetattr(0, TCSANOW, &old_termios);
    free(args);
    return 0;
}
