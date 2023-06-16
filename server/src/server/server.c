/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** server.c
*/

#include "../includes/zappy.h"

void crtld_handler(int signal)
{
    (void)signal;
    exit(0);
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

void check_seconds_passed(clock_t clock_start) {
    double elapsed_seconds;
    clock_t current_time;

    current_time = clock();  // Get the current time
    elapsed_seconds = (double)(current_time - clock_start) / CLOCKS_PER_SEC;

    if (elapsed_seconds >= 1.0) {
        printf("EUREKA\n");
    }
}

int server(fd_set *readfds, serv_t *serv)
{
    fd_set tmpfds;

    FD_ZERO(&tmpfds);
    tmpfds = *readfds;
    check_seconds_passed(serv->clock);
    if (select(serv->max_sd + 1, &tmpfds, NULL, NULL, NULL) < 0)
        print_and_exit("ERROR on select");
    for (int i = 0; i <= serv->max_sd; i++) {
        if (!FD_ISSET(i, &tmpfds)) { // Valgrind HERE
            continue;
        }
    printf("serv = %d %d\n", serv->max_x, serv->max_y);
        if (i == serv->sockfd) {
            accept_new_client(readfds, serv);
        } else {
            receive_client_msg(i, readfds, serv);
        }
    }
    return 0;
}

int start_server(args_t *args)
{
    struct termios old_termios = init_signal();
    serv_t *serv = serv_ctor(args);
    printf("serv = %d %d\n", serv->max_x, serv->max_y);
    fd_set readfds;
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


