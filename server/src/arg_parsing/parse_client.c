/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** parse_player.c
*/

#include "../../includes/zappy.h"

player_t *parse_player(int sockfd, serv_t *serv, int nb)
{
    client_t *temp = serv->clients;
    while (temp->player->next != NULL) {
        if (temp->player->id == nb) {
            return temp->player;
        }
        temp->player = temp->player->next;
    }
    return NULL;
}