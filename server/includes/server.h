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
    #include <signal.h>
    #include <termios.h>

static const int MAX_NAMES = 10;

enum nb_command {
    NB_CMD = 1
};

enum enum_slot {
    FULL,
    NOT_FULL,
    CONTINUE = 100
};

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
    int slot;
} client_t;

typedef struct serv_s {
    int map_x;
    int map_y;
    int sockfd;
    int portno;
    int max_sd;
    struct sockaddr_in addr;
    pid_t pid;
    int global_uid;
    client_t *clients;
} serv_t;

typedef struct cmd_s {
    char *command;
    int(*pointer)(int, serv_t *);
} cmd_t;

//* Arguments parsing
int parse_arguments(int ac, char **av, args_t *args);
args_t *args_constructor(void);
int parse_names(char **av, args_t *args);
int parse_default(void);
int parse_port_width_height(int option, char *optarg, args_t *args);
int parse_names_clients_nb_freq(int option, char *optarg, args_t *args,
    char **av);

//* Constructors
serv_t *serv_ctor(args_t *arg);
client_t *root_client_ctor(args_t *arg);
client_t *client_ctor(client_t *root);
client_t *pop_client(client_t *client);

//* Server
int start_server(args_t *args);
int receive_client_msg(int sockfd, fd_set *readfds, serv_t *serv);
client_t *accept_new_client(fd_set *readfds, serv_t *serv);
// void get_group_name(client_t *client, serv_t *serv, fd_set *readfds);
int check_name_team(serv_t *serv, char *buffer);
void send_x_y_ai(int sockfd, serv_t *serv, char *number);
char *send_nb_slot_ai(int slot);

//* Tools
void usage(void);
void print_and_exit(char *str);
void usage(void);

//* Commands
int map_command(int sockfd, serv_t *serv);

#endif
