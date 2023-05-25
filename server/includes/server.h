/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** server.h
*/

#ifndef _SERVER_H_
    #define _SERVER_H_

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <getopt.h>

static const int MAX_NAMES = 10;

typedef struct args_s {
    int port;
    int width;
    int height;
    char **names;
    int clientsNb;
    float freq;
    int namesCount;
} args_t;

//* Parsing
int parse_arguments(int ac, char **av, args_t *args);

//* Tools
void print_and_exit(char *str);

#endif
