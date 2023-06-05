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
    char **array = splitStringAtSpaces(buffer, &count);
    player_t *tmp = parse_player(sockfd, serv, atoi(array[1]));
    char *msg = NULL;
    int len = 0;
    char *dir = get_orientation(tmp->orientation);

    if (tmp == NULL)
        return 84;
    len = snprintf(msg, 0, "ppo %d %d %d %s\n", tmp->nb, tmp->x, tmp->y, dir);
    msg = malloc(sizeof(char) * (len + 1));
    msg[len] = '\0';
    sprintf(msg, "ppo %d %d %d %s\n", tmp->nb, tmp->x, tmp->y, dir);
    if (write(sockfd, msg, len) == -1)
        return 84;
    free(msg);
    return 0;
}

int send_player_level(player_t *player, int sockfd)
{
    char *msg;
    int len = 6 + strlen((char *)player->nb) + strlen((char *) player->level);

    msg = malloc(sizeof(char) * (len + 1));
    msg[len] = '\0';
    sprintf(msg, "plv %d %d\n", player->nb, player->level);
    if (write(sockfd, msg, len) == -1)
        return 84;
    return 0;
}

// int send_player_inventory(player_t *player, int sockfd)
// {
//     inv_t *inventory = player->inventory;
//     char *msg;
//     int len = 6 + strlen((char *)player->nb) + strlen((char *) inventory->food);

//     len += strlen((char *) inventory->linemate) + strlen((char *) inventory->deraumere);
//     len += strlen((char *) inventory->sibur) + strlen((char *) inventory->mendiane);
//     len += strlen((char *) inventory->phiras) + strlen((char *) inventory->thystame);
//     msg = malloc(sizeof(char) * (len + 1));
//     msg[len] = '\0';
//     sprintf(msg, "pin %d %d %d %d %d %d %d %d %d %d\n", player->nb, inventory->food,
//         inventory->linemate, inventory->deraumere, inventory->sibur, inventory->mendiane,
//         inventory->phiras, inventory->thystame);
//     if (write(sockfd, msg, len) == -1)
//         return 84;
//     return 0;
// }