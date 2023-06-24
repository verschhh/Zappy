/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** inventory.c
*/

#include "../../includes/zappy.h"

char *get_inv(inv_t *inv)
{
    char msg[1024];
    char tmp[1024];
    int len = 0;
    char *buf = NULL;
    sprintf(msg, "food %d, linemate %d, deraumere %d, ", inv->food,
        inv->linemate, inv->deraumere);
    sprintf(tmp, "sibur %d, mendiane %d, phiras %d, thystame %d\n",
        inv->sibur, inv->mendiane, inv->phiras, inv->thystame);
    strcat(msg, tmp);
    len = strlen(msg);
    buf = malloc(sizeof(char) * (len + 1));
    strcpy(buf, msg);
    return buf;
}

int inventory(int sockfd, serv_t *serv, char *buffer)
{
    client_t *cpy = get_correct_client(serv, sockfd);

    if (!cpy->clocking) {
        update_time_limit(serv, cpy, 1, buffer);
        return 0;
    }
    inv_t *tmp = cpy->player->inventory;
    char *msg = get_inv(tmp);
    int len = strlen(msg);
    if (cpy->clocking) {
        if (write(sockfd, msg, len + 1) == -1)
            return 84;
    }
    cpy->clocking = false;
    return 0;
}
