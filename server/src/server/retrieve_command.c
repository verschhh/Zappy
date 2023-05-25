/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** retrieve_command.c
*/

#include "../includes/server.h"

int retrieve_command(int sockfd, fd_set *readfds, serv_t *serv)
{
    // char buffer[1024] = {0};
    // int bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
    // if (bytes_read <= 0) {
    //     close(sockfd);
    //     FD_CLR(sockfd, readfds);
    // } else {
    //     message_t message = parse_message(buffer);
    //     handle_command(message, serv, sockfd);
    // }
    return 0;
}
