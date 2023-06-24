/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** inventory_ctors.c
*/

#include "../includes/zappy.h"

inv_t *inv_ctor(void)
{
    inv_t *inv = malloc(sizeof(inv_t));

    if (inv == NULL)
        perror("Memory allocation failed");
    inv->food = 10;
    inv->linemate = 0;
    inv->deraumere = 0;
    inv->sibur = 0;
    inv->mendiane = 0;
    inv->phiras = 0;
    inv->thystame = 0;
    return inv;
}
