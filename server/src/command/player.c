/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** player.c
*/

#include "../../includes/server.h"

int send_player_position(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    char *msg = NULL;
    int len = 0;
    char *dir = get_orientation(tmp->orientation);

    if (tmp == NULL)
        return 84;
    len = snprintf(msg, 0, "ppo %d %d %d %s\n", tmp->id, tmp->x, tmp->y, dir);
    msg = malloc(sizeof(char) * (len + 1));
    msg[len] = '\0';
    sprintf(msg, "ppo %d %d %d %s\n", tmp->id, tmp->x, tmp->y, dir);
    if (write(sockfd, msg, len) == -1)
        return 84;
    free(msg);
    return 0;
}

int send_player_level(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    char *msg = NULL;
    int len = 0;

    msg = malloc(sizeof(char) * (len + 1));
    msg[len] = '\0';
    len = snprintf(msg, 0, "plv %d %d\n", tmp->id, tmp->level);
    if (write(sockfd, msg, len) == -1)
        return 84;
    return 0;
}

int send_player_inventory(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char **array = splitStringAtSpaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    inv_t *inv = tmp->inventory;
    char *msg = NULL;
    int len = 0;

    len = snprintf(msg, 0, "pin %d %d %d %d %d %d %d %d\n", tmp->id
        , inv->food, inv->linemate, inv->deraumere, inv->sibur, inv->mendiane,
        inv->phiras, inv->thystame);
    msg = malloc(sizeof(char) * (len + 1));
    msg[len] = '\0';
    snprintf(msg, len, "pin %d %d %d %d %d %d %d %d\n", tmp->id
        , inv->food, inv->linemate, inv->deraumere, inv->sibur, inv->mendiane,
        inv->phiras, inv->thystame);
    if (write(sockfd, msg, len) == -1)
        return 84;
    return 0;
}