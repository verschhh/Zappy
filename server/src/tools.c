/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** tools.c
*/

#include "../includes/server.h"

void print_and_exit(char *str)
{
    fprintf(stderr, "%s\n", str);
    exit(84);
}
