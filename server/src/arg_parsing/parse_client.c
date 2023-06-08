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
    while (temp->next != NULL) {
        if (temp->player->id == nb) {
            return temp->player;
        }
        printf("J'AI TOURNÉ\n");
        temp = temp->next;
    }
    printf("JE SUIS SORTI\n");
    return NULL;
}