/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** time.c
*/

#include "../../includes/zappy.h"

int send_unit_time(int sockfd, serv_t *serv, char *buffer)
{
    char msg[6];

    sprintf(msg, "%s %d", "sgt", serv->freq);
    write(sockfd, msg, 6);
}