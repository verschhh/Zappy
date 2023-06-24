/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** look.c
*/

#include "../../includes/zappy.h"

char *tile_to_string(map_t *tile, client_t *client)
{
    char *str = malloc(sizeof(char) * (calc_tile_to_string(tile, client) + 1));
    str[0] = '\0';
    while (client != NULL) {
        if (client->player->x == tile->x && client->player->y == tile->y)
            strcat(str, "player ");
        client = client->next;
    }
    for (int i = 0; i < tile->food; i++)
        strcat(str, "food ");
    for (int i = 0; i < tile->linemate; i++)
        strcat(str, "linemate ");
    for (int i = 0; i < tile->deraumere; i++)
        strcat(str, "deraumere ");
    for (int i = 0; i < tile->sibur; i++)
        strcat(str, "sibur ");
    for (int i = 0; i < tile->mendiane; i++)
        strcat(str, "mendiane ");
    for (int i = 0; i < tile->phiras; i++)
        strcat(str, "phiras ");
    for (int i = 0; i < tile->thystame; i++)
        strcat(str, "thystame ");
    if (strlen(str) > 0)
        str[strlen(str) - 1] = '\0';
    return str;
}

coord_t *get_visible_tile_coords(serv_t *server, player_t *player)
{
    int n = player->level + 1;
    int vision_size = (n * (2 * 1 + (n - 1) * 2)) / 2;
    coord_t *visible_coords = calloc(vision_size, sizeof(coord_t));
    int k = 0;
    for (int i = 0; i < n; i++) {
        int row_width = 2 * i + 1;
        for (int j = 0; j < row_width; j++) {
            switch (player->orientation) {
                case 1:
                    visible_coords[k].y = (player->y - i + server->max_y) % server->max_y;
                    visible_coords[k].x = (player->x + j - i + server->max_x) % server->max_x;
                    break;
                case 2:
                    visible_coords[k].x = (player->x + i + server->max_x) % server->max_x;
                    visible_coords[k].y = (player->y + j - i + server->max_y) % server->max_y;
                    break;
                case 3:
                    visible_coords[k].y = (player->y + i + server->max_y) % server->max_y;
                    visible_coords[k].x = (player->x - j + i + server->max_x) % server->max_x;
                    break;
                case 4:
                    visible_coords[k].x = (player->x - i + server->max_x) % server->max_x;
                    visible_coords[k].y = (player->y - j + i + server->max_y) % server->max_y;
                    break;
            }
            k++;
        }
    }
    return visible_coords;
}

char *build_look_response(serv_t *server, player_t *player)
{
    int n = player->level + 1;
    int vision_size = (n * (2 * 1 + (n - 1) * 2)) / 2;
    coord_t *visible_coords = get_visible_tile_coords(server, player);
    char *response = malloc(sizeof(char) * (256));
    strcpy(response, "[");

    for (int i = 0; i < vision_size; i++) {
        if (i != 0)
            strcat(response, ",");
        client_t *copy = server->clients;
        map_t *tile = find_tile(server, visible_coords[i].x, visible_coords[i].y);
        char *tile_str = tile_to_string(tile, copy);
        size_t tile_str_len = strlen(tile_str);
        response = realloc(response, sizeof(char) * (strlen(response) + tile_str_len + 6));
        if (strlen(tile_str) > 1 && i > 0) {
            strcat(response, " ");
        }
        strcat(response, tile_str);
        free(tile_str);
    }
    strcat(response, "]\n");
    return response;
}

int look(int sockfd, serv_t *serv, char *buffer)
{
    client_t *cli = get_correct_client(serv, sockfd);
    player_t *player = cli->player;

    if (!cli->clocking) {
        update_time_limit(serv, cli, 7, buffer);
        return 0;
    }
    if (cli->clocking) {
        get_visible_tile_coords(serv, player);
        char *response = build_look_response(serv, player);
        write(sockfd, response, strlen(response));
        cli->clocking = false;
    }
    return 0;
}