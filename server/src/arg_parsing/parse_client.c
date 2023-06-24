/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** parse_player.c
*/

#include "../../includes/zappy.h"

player_t *parse_player(int sockfd, serv_t *serv, int id)
{
    client_t *temp = serv->clients;

    (void) sockfd;
    while (temp != NULL) {
        if (temp->player->id == id) {
            return temp->player;
        }
        temp = temp->next;
    }
    return NULL;
}
