/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** retrieve_command.c
*/

#include "../includes/zappy.h"

const cmd_t cmd_list[NB_CMD] = {
    {"msz", &map_size},
    {"bct", &tile_content},
    {"mct", &map_content},
    {"tna", &get_all_names_group},
    {"sgt", &send_unit_time},
    {"sst", &modify_unit_time},
    {"ppo", &send_player_position},
    {"plv", &send_player_level},
    {"pin", &send_player_inventory},
    {"Forward", &forward},
    {"Left", &left},
    {"Right", &right},
    {"Take", &take_object},
    {"Set", &set_object},
    {"Inventory", &inventory},
    {"Broadcast", &broadcast},
    {"Incantation", &incantation},
    {"Look", &look},
    {"Connect_nbr", &unused_slot},
    {"queue", &send_queue},
    {"Fork", &fork_cmd}
};

int parse_command(char *buffer)
{
    if (buffer == NULL)
        return -1;
    char *cmd = malloc(sizeof(char) * strlen(buffer) + 1);
    int index = 0;
    while (buffer[index] != ' ' && buffer[index] != '\0') {
        cmd[index] = buffer[index];
        index++;
    }
    cmd[index] = '\0';
    for (int i = 0; i != NB_CMD; i++) {
        if (strstr(cmd, cmd_list[i].command) != NULL) {
            free(cmd);
            return i;
        }
    }
    free(cmd);
    return -1;
}

int lauch_cmd(int cmd, int sockfd, serv_t *serv, char *buffer)
{
    if (cmd_list[cmd].pointer(sockfd, serv, buffer) == 84)
        return 84;
    return 0;
}

void destroy_node(client_t **client, int value)
{
    client_t *current = *client;
    client_t *previous = NULL;

    if (*client == NULL)
        return;
    while (current != NULL) {
        if (change_node(client, current, previous, value) == 1)
            return;
        previous = current;
        current = current->next;
    }
}

void check_death(serv_t *serv)
{
    client_t *next;
    client_t *cpy = serv->clients;

    while (cpy != NULL) {
        next = cpy->next;
        if (cpy->player->inventory->food <= 0) {
            write(cpy->sockfd, "dead\n", 5);
            send_death_player(serv, cpy->player->id);
            destroy_node(&serv->clients, cpy->player->id);
        }
        if (serv->clients == NULL)
            return;
        cpy = next;
    }
}

int receive_client_msg(int sockfd, fd_set *readfds, serv_t *serv)
{
    char buffer[1024] = {0};
    int cmd = 0;
    int bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_read <= 0) {
        close(sockfd);
        FD_CLR(sockfd, readfds);
    } else {
        if (buffer != NULL)
            cmd = parse_command(buffer);
        if (init_new_client(serv, buffer, cmd, sockfd) == 1)
            return 0;
        clock_action(serv);
        lauch_cmd(cmd, sockfd, serv, buffer);
        check_death(serv);
    }
    return 0;
}
