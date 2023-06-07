/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** player.c
*/

#include "../../includes/zappy.h"

int send_player_position(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char *str = NULL;
    char **array = split_string_at_spaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    char *dir = get_orientation(tmp->orientation);
    int len = snprintf(str, 0, "%d %d %d %s\n", tmp->id, tmp->x, tmp->y, dir);
    char s[len + 4];

    if (tmp == NULL)
        return 84;
    sprintf(s, "ppo %d %d %d %s\n", tmp->id, tmp->x, tmp->y, dir);
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_player_level(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    char *msg = NULL;
    int len = snprintf(msg, 0, "plv %d %d\n", tmp->id, tmp->level);
    char s[len];

    snprintf(s, len, "plv %d %d\n", tmp->id, tmp->level);
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_player_inventory(int sockfd, serv_t *serv, char *buffer)
{
    int count = 0;
    char *msg = NULL;
    char **array = split_string_at_spaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    inv_t *inv = tmp->inventory;
    int len = snprintf(msg, 0, "pin %d %d %d %d %d %d %d %d\n", tmp->id
        , inv->food, inv->linemate, inv->deraumere, inv->sibur, inv->mendiane,
        inv->phiras, inv->thystame);
    char s[len];

    snprintf(s, len, "pin %d %d %d %d %d %d %d %d\n", tmp->id
        , inv->food, inv->linemate, inv->deraumere, inv->sibur, inv->mendiane,
        inv->phiras, inv->thystame);
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_expulsion(int sockfd, serv_t *serv, char *buffer)
{
    
}