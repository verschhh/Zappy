/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** set_switch_case.c
*/

#include "../../includes/zappy.h"

void switch_case_set_four(int i, map_t *map_cpy, client_t *c_cpy, int sockfd)
{
    switch (i) {
        case 5:
            if (check_inventory_material(c_cpy->player->inventory->phiras,
                sockfd) == 1) {
                map_cpy->phiras++;
                c_cpy->player->inventory->phiras--;
            }
            break;
        case 6:
            if (check_inventory_material(c_cpy->player->inventory->thystame,
                sockfd) == 1) {
                map_cpy->thystame++;
                c_cpy->player->inventory->thystame--;
            }
            break;
    }
}

void switch_case_set_three(int i, map_t *map_cpy, client_t *c_cpy, int sockfd)
{
    switch (i) {
        case 3:
            if (check_inventory_material(c_cpy->player->inventory->sibur
                , sockfd) == 1) {
                map_cpy->sibur++;
                c_cpy->player->inventory->sibur--;
            }
            break;
        case 4:
            if (check_inventory_material(c_cpy->player->inventory->mendiane
                , sockfd) == 1) {
                map_cpy->mendiane++;
                c_cpy->player->inventory->mendiane--;
            }
            break;
        default:
            switch_case_set_four(i, map_cpy, c_cpy, sockfd);
            break;
    }
}

void switch_case_set_two(int i, map_t *map_cpy, client_t *c_cpy, int sockfd)
{
    switch (i) {
        case 1:
            if (check_inventory_material(c_cpy->player->inventory->linemate
                , sockfd) == 1) {
                map_cpy->linemate++;
                c_cpy->player->inventory->linemate--;
            }
            break;
        case 2:
            if (check_inventory_material(c_cpy->player->inventory->deraumere
                , sockfd) == 1) {
                map_cpy->deraumere++;
                c_cpy->player->inventory->deraumere--;
            }
            break;
        default:
            switch_case_set_three(i, map_cpy, c_cpy, sockfd);
            break;
    }
}

void switch_case_set(int i, map_t *map_cpy, client_t *c_cpy, int sockfd)
{
    switch (i) {
        case 0:
            if (check_inventory_material(c_cpy->player->inventory->food, sockfd) == 1) {
                map_cpy->food++;
                c_cpy->player->inventory->food--;
            }
            break;
        default:
            switch_case_set_two(i, map_cpy, c_cpy, sockfd);
            break;
    }
}
