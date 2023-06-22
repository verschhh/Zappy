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
    {"queue", &send_queue}
};

int parse_command(char *buffer)
{
    char *cmd = malloc(sizeof(char) * strlen(buffer) + 1);
    int index = 0;

    if (buffer == NULL)
        printf("Buffer is NULL\n");

    while (buffer[index] != ' ' && buffer[index] != '\0') {
        cmd[index] = buffer[index];
        index++;
    }
    cmd[index] = '\0';
    for (int i = 0; i != NB_CMD; i++) {
        if (strstr(cmd, cmd_list[i].command) != NULL)
            return i;
    }
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
        if (current->player->id == value) {
            if (previous == NULL)
                *client = current->next;
            else
                previous->next = current->next;
            free(current);
            printf("Node with value %d deleted.\n", value);
            return;
        }
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
        printf("food = %d\n", cpy->player->inventory->food);
        if (cpy->player->inventory->food == 0) {
            printf("DEATH\n");
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
    int next = 0;
    if (bytes_read <= 0) {
        close(sockfd);
        FD_CLR(sockfd, readfds);
    } else {
        cmd = parse_command(buffer);
        if (cmd == -1) {
            next = check_name_team(serv, buffer);
            if (next >= 0) {
                fill_client_struct(sockfd, serv, buffer);
                send_x_y_ai(sockfd, serv, next);
                send_connection_msg(serv->clients, serv);
            } else
                write(sockfd, "suc\n", 4);
            return 0;
        }
        if (serv->clients != NULL)
            clock_action(serv);
        lauch_cmd(cmd, sockfd, serv, buffer); //TODO: launch here and in decrement tick strange
        check_death(serv);
    }
    return 0;
}
