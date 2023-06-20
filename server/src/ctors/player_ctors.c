/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** player_ctors.c
*/

#include "../includes/zappy.h"

player_t *player_ctor(serv_t *server)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        perror("Memory allocation failed");
    player->x = (rand() % (server->max_x - 0 + 1) + 0);
    player->y = (rand() % (server->max_y - 0 + 1) + 0);
    printf("Player spawned at X%d Y%d\n", player->x, player->y);
    player->id = server->nb_client;
    server->nb_client++;
    player->level = 1;
    player->orientation = (rand() % (4 - 1 + 1) + 1);
    player->inventory = inv_ctor();
    return player;
}
