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

    printf("JE SUIS RENTRE\n");

    while (temp != NULL) {
        printf("id in parse = %d and nb = %d\n", temp->player->id, nb);
        if (temp->player->id == nb) {
            return temp->player;
        }
        printf("J'AI TOURNÉ\n");
        tmp->clients = tmp->clients->next;
    }
    printf("J'AI PAS TROUVE LE N#%d\n", nb);
    return NULL;
}