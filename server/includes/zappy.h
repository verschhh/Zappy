/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** server.h
*/

#ifndef _SERVER_H_
    #define _SERVER_H_

    #include "struct.h"

static const int MAX_NAMES = 10;

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
client_t *client_ctor(serv_t *serv);
client_t *pop_client(client_t *client);
inv_t *inv_ctor(void);
slot_t *slot_ctor(args_t *arg);
player_t *player_ctor(serv_t *server);
slot_t *new_slot(slot_t *slot, char *name);
int fill_client_struct(int sockfd, serv_t *serv, char *buffer);

//* Server
int start_server(args_t *args);
int receive_client_msg(int sockfd, fd_set *readfds, serv_t *serv);
client_t *accept_new_client(fd_set *readfds, serv_t *serv);
// void get_group_name(client_t *client, serv_t *serv, fd_set *readfds);
int check_name_team(serv_t *serv, char *buffer);
void send_x_y_ai(int sockfd, serv_t *serv, int slot);
char *send_nb_slot_ai(int slot);

//* Tools
void usage(void);
void print_and_exit(char *str);
void usage(void);
char** split_string_at_spaces(const char* input, int* count);
char *get_orientation(enum orientation orientation);
client_t *get_correct_client(serv_t *serv, int sockfd);

//* Commands
int map_size(int sockfd, serv_t *serv, char *buffer);
int tile_content(int sockef, serv_t *serv, char *buffer);
int map_content(int sockf, serv_t *serv, char *buffer);
int get_all_names_group(int sockfd, serv_t *serv, char *buffer);
int send_unit_time(int sockfd, serv_t *serv, char *buffer);
int send_player_position(int sockfd, serv_t *serv, char *buffer);
int send_player_level(int sockfd, serv_t *serv, char *buffer);
int send_player_inventory(int sockfd, serv_t *serv, char *buffer);
int modify_unit_time(int sockfd, serv_t *serv, char *buffer);

//* Server Commands
void send_connection_msg(client_t *client);
int send_death_player(int sockfd, serv_t *serv, char *buffer);
int send_expulsion(int sockfd, serv_t *serv, char *buffer);
int send_egg_laying(int sockfd, serv_t *serv, char *buffer);
int send_serv_msg(int sockfd, serv_t *serv, char *buffer);

#endif
