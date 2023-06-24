/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** inventory.c
*/

#include "../../includes/zappy.h"

int write_player_inventory(int sockfd, player_t *player)
{
    char msg[0];
    int len = snprintf(msg, 0, "pin %d %d %d %d %d %d %d %d%s\n", player->id,
        player->inventory->food, player->inventory->linemate,
            player->inventory->deraumere, player->inventory->sibur,
                player->inventory->mendiane,
                    player->inventory->phiras,
                        player->inventory->thystame, "\n");
    char s[len + 1];

    snprintf(s, len, "pin %d %d %d %d %d %d %d %d%s\n", player->id,
        player->inventory->food, player->inventory->linemate,
            player->inventory->deraumere, player->inventory->sibur,
                player->inventory->mendiane,
                    player->inventory->phiras,
                        player->inventory->thystame, "\n");
    if (write(sockfd, s, len) == -1)
        return 84;
    return 0;
}

int send_player_inventory(int sockfd, serv_t *serv, char *buffer)
{
    (void)buffer;
    int count = 0;
    char **array = split_string_at_spaces(buffer, &count);
    erase_first_characters(array[1], 1);
    player_t *player = parse_player(sockfd, serv, atoi(array[1]));

    if (player == NULL)
        return unknown_command(sockfd, serv, buffer);
    write_player_inventory(sockfd, player);
    return 0;
}
