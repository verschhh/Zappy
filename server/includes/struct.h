/*
** EPITECH PROJECT, 2022
** server
** File description:
** strcut.h
*/

#pragma once

    #include "server.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <getopt.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/select.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <error.h>
    #include <string.h>
    #include <signal.h>
    #include <termios.h>

typedef struct serv_s {
    int max_x;
    int max_y;
    int sockfd;
    int max_sd;
    struct sockaddr_in addr;
    client_t *clients;
    map_t *map;
    int freq;
} serv_t;