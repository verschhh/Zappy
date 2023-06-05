/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** player_ctors.c
*/

#include "../includes/zappy.h"

player_t *player_root_ctor(int nb_client)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        perror("Memory allocation failed");
    player->x = 0;
    player->y = 0;
    player->id = 0;
    player->level = 1;
    player->orientation = NORTH;
    player->inventory = inv_ctor();
    return player;
}

player_t *add_player(player_t *player)
{
    player_t *new_player = malloc(sizeof(player_t));
    player_t *tmp = player;

    if (player == NULL)
        return NULL;
    new_player->x = 0;
    new_player->y = 0;
    new_player->id = tmp->id + 1;
    new_player->level = 1;
    new_player->orientation = NORTH;
    new_player->inventory = inv_ctor();
    printf("Player %d created\n", new_player->id);
    return new_player;
}