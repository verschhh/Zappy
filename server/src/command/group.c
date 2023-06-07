/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** group.c
*/

#include "../../includes/zappy.h"

int get_all_names_group(int sockfd, serv_t *serv, char *buffer)
{
}

void send_connection_msg(client_t *client)
{
    char msg[26];

    sprintf(msg, "pnw #%d %d %d %d %d", client->player->id, client->player->x,
        client->player->y, client->player->orientation,
            client->player->level, client->team_name);
    write(client->sockfd, msg, 26);
}