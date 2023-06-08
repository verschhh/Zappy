/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** parse_player.c
*/

#include "../../includes/zappy.h"

player_t *parse_player(int sockfd, serv_t *serv, int nb)
{
    serv_t *tmp = serv;
    printf("JE SUIS RENTRE\n");
    while (tmp->clients->next != NULL) {
        printf("%d %d %d\n", tmp->clients->player->id, nb, tmp->clients->next->player->id);
        if (tmp->clients->player->id == nb) {
            return tmp->clients->player;
        }
        printf("J'AI TOURNÉ\n");
        tmp->clients = tmp->clients->next;
    }
    printf("J'AI PAS TROUVE LE N#%d\n", nb);
    return NULL;
}