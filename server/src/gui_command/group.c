/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** group.c
*/

#include "../../includes/zappy.h"

int get_all_names_group(int sockfd, serv_t *serv, char *buffer)
{
    slot_t *copy = serv->slots;
    int len = 0;
    (void)buffer;

    while (copy->next != NULL) {
        len = strlen(copy->team_name);
        char msg[len];
        sprintf(msg, "tna %s\n", copy->team_name);
        write(sockfd, msg, len + 8);
        copy = copy->next;
    }
    return 0;
}

void send_connection_msg(client_t *client, serv_t *serv)
{
    client_t *cpy = client;

    while (cpy != NULL && cpy->next != NULL)
        cpy = cpy->next;
    if (cpy != NULL) {
        sprintf(serv->queue + strlen(serv->queue), "pnw #%d %d %d %d %d %s",
            cpy->player->id, cpy->player->x,
                cpy->player->y, cpy->player->orientation,
                    cpy->player->level, cpy->team_name);
    }
}
