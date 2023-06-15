/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** server.c
*/

#include "../../includes/zappy.h"

int send_serv_msg(int sockfd, serv_t *serv, char *buffer)
{
    (void) serv;
    write(sockfd, buffer, strlen(buffer));
    return 0;
}