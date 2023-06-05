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
    NB_CMD = 6
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
    struct player_s *next;
} player_t;

typedef struct client_s {
    char *team_name;
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addrlen;
    int slot;
    struct player_s *player;
    struct client_s *next;
} client_t;

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
    int map_x;
    int map_y;
    int sockfd;
    int portno;
    int max_sd;
    struct sockaddr_in addr;
    pid_t pid;
    int global_uid;
    client_t *clients;
    map_t *map;
    int freq;
} serv_t;

typedef struct cmd_s {
    char *command;
    int(*pointer)(int, serv_t *, char *);
} cmd_t;

//* Arguments parsing
int parse_arguments(int ac, char **av, args_t *args);
args_t *args_constructor(void);
int parse_names(char **av, args_t *args);
int parse_default(void);
int parse_port_width_height(int option, char *optarg, args_t *args);
int parse_names_clients_nb_freq(int option, char *optarg, args_t *args,
    char **av);
player_t *parse_player(int sockfd, serv_t *serv, int nb);

//* Constructors
serv_t *serv_ctor(args_t *arg);
map_t *create_map(args_t *arg);
client_t *root_client_ctor(args_t *arg);
client_t *client_ctor(client_t *root);
client_t *pop_client(client_t *client);
inv_t *inv_ctor(void);
player_t *player_root_ctor(int nb_client);
player_t *add_player(player_t *player);

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
char** splitStringAtSpaces(const char* input, int* count);
char *get_orientation(enum orientation orientation);

//* Commands
int map_size(int sockfd, serv_t *serv, char *buffer);
int tile_content(int sockef, serv_t *serv, char *buffer);
int map_content(int sockf, serv_t *serv, char *buffer);
int get_all_names_group(int sockfd, serv_t *serv, char *buffer);
int send_unit_time(int sockfd, serv_t *serv, char *buffer);
int send_player_position(int sockfd, serv_t *serv, char *buffer);

#endif
