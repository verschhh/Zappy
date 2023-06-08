/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** player_ctors.c
*/

#include "../includes/zappy.h"

player_t *player_ctor(serv_t *server, int nb)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        perror("Memory allocation failed");
    player->x = (rand() % (server->max_x - 0 + 1) + 0);
    player->y = (rand() % (server->max_y - 0 + 1) + 0);
    player->id = nb;
    printf("ID SALE FDP DE MERDE:%d\n", player->id);
    player->level = 1;
    player->orientation = NORTH;
    player->inventory = inv_ctor();
    return player;
}
