/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** server.h
*/

#ifndef _SERVER_H_
    #define _SERVER_H_

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

static const int MAX_NAMES = 10;

enum orientation {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct args_s {
    int port;
    int width;
    int height;
    char **names;
    int clientsNb;
    float freq;
    int namesCount;
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

typedef struct client_s {
    char *team_name;
    int x;
    int y;
    int level;
    inv_t *inventory;
    int orientation;
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    struct client_s *next;
} client_t;

typedef struct serv_s {
    int sockfd;
    int portno;
    int max_sd;
    struct sockaddr_in addr;
    pid_t pid;
    int global_uid;
    client_t *clients;
} serv_t;

//* Arguments parsing
int parse_arguments(int ac, char **av, args_t *args);
args_t *args_constructor(void);

//* Constructors
serv_t *serv_ctor(args_t *arg);
client_t *root_client_ctor(void);
client_t *client_ctor(client_t *root);
client_t *pop_client(client_t *client);

//* Tools
void usage(void);
void print_and_exit(char *str);

#endif
