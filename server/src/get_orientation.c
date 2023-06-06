/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** get_orientation.c
*/

#include "../includes/zappy.h"

char *get_orientation(enum orientation orientation)
{
    switch (orientation) {
        case NORTH:
            return "NORTH";
        case EAST:
            return "EAST";
        case SOUTH:
            return "SOUTH";
        case WEST:
            return "WEST";
        default:
            return NULL;
    }
}
