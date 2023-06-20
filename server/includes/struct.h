/*
** EPITECH PROJECT, 2022
** server
** File description:
** strcut.h
*/

#pragma once

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
    #include <time.h>
    #include <stdbool.h>


enum nb_command {
    NB_CMD = 16
};

enum enum_slot {
    FULL,
    NOT_FULL,
    CONTINUE = 100
};

enum orientation {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};


typedef struct args_s {
    int port;
    int width;
    int height;
    char **names;
    int clientsnb;
    float freq;
    int namescount;
} args_t;

typedef struct inv_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inv_t;

typedef struct player_s {
    int x;
    int y;
    int level;
    int id;
    inv_t *inventory;
    enum orientation orientation;
} player_t;

typedef struct client_s {
    char *team_name;
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    int slot;
    unsigned int tickleft;
    char *cpy_buffer;
    bool is_ticking;
    struct player_s *player;
    struct client_s *next;
} client_t;

typedef struct slot_s {
    char *team_name;
    int nb;
    client_t *team_member;
    struct slot_s *next;
} slot_t;

typedef struct map_s {
    int x;
    int y;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    struct map_s *next;
} map_t;

typedef struct serv_s {
    int max_x;
    int max_y;
    int sockfd;
    int max_sd;
    int freq;
    int nb_client;
    struct timeval tv;
    bool new_tick;
    struct sockaddr_in addr;
    clock_t start;
    char queue[5000];
    client_t *clients;
    map_t *map;
    slot_t *slots;
} serv_t;

typedef struct cmd_s {
    char *command;
    int(*pointer)(int, serv_t *, char *);
} cmd_t;

#define FOOD(map) (map->food)
#define LINEMATE(map) (map->linemate)
#define DERAUMERE(map) (map->deraumere)
#define SIBUR(map) (map->sibur)
#define MENDIANE(map) (map->mendiane)
#define PHIRAS(map) (map->phiras)
#define THYSTAME(map) (map->thystame)

typedef int (*MapFieldFunc)(map_t* map);
