/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** sound_dir.c
*/

#include "../../includes/zappy.h"

int res_over_zero(int y_res)
{
    int i = 0;
    if (y_res > 0)
        i = 8;
    if (y_res == 0)
        i = 7;
    if (y_res < 0)
        i = 6;
    return i;
}

int res_equal_zero(int y_res)
{
    int i = 0;
    if (y_res > 0)
        i = 1;
    if (y_res < 0)
        i = 5;
    return i;
}

int res_under_zero(int y_res)
{
    int i = 0;
    if (y_res > 0)
        i = 2;
    if (y_res == 0)
        i = 3;
    if (y_res < 0)
        i = 4;
    return i;
}

int get_facing(player_t *start, player_t *goal)
{
    int x_res = goal->x - start->x;
    int y_res = goal->y - start->y;
    int orientation = 0;
    if (x_res > 0)
        orientation = res_over_zero(y_res);
    if (x_res == 0)
        orientation = res_equal_zero(y_res);
    if (x_res < 0)
        orientation = res_under_zero(y_res);
    if (orientation == 0)
        return 0;
    return (orientation);
}
