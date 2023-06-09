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
    printf("max_x = %d and max_y = %d\n", server->max_x, server->max_y);
    // player->x = (rand() % (server->max_x - 0 + 1) + 0);
    // player->y = (rand() % (server->max_y - 0 + 1) + 0);
    player->x = 2;
    player->y = 10;
    printf("nb_client = %d\n", server->nb_client);
    player->id = server->nb_client;
    server->nb_client++;
    player->level = 1;
    player->orientation = NORTH;
    player->inventory = inv_ctor();
    return player;
}
