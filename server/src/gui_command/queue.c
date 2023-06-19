/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** queue.c
*/

#include "../../includes/zappy.h"

int send_queue(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    char msg[0];
    int len = snprintf(msg, 0, "%s", serv->queue);
    char send[len];

    if (len > 0) {
        sprintf(send, "%s", serv->queue);
        write(sockfd, send, len);
        strcpy(serv->queue, "");
    } else {
        write(sockfd, "\n", 2);
    }
    return 0;
}