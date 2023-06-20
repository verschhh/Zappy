/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** look.c
*/

#include "../../includes/zappy.h"

char *tile_to_string(map_t *tile) {
    char *str = malloc(256 * sizeof(char));
    str[0] = '\0';  // initialize the string to be empty

    // TODO: add the player(s) on the tile

    // append each resource multiple times
    for (int i = 0; i < tile->food; i++) {
        strcat(str, "food ");
    }
    for (int i = 0; i < tile->linemate; i++) {
        strcat(str, "linemate ");
    }
    for (int i = 0; i < tile->deraumere; i++) {
        strcat(str, "deraumere ");
    }
    for (int i = 0; i < tile->sibur; i++) {
        strcat(str, "sibur ");
    }
    for (int i = 0; i < tile->mendiane; i++) {
        strcat(str, "mendiane ");
    }
    for (int i = 0; i < tile->phiras; i++) {
        strcat(str, "phiras ");
    }
    for (int i = 0; i < tile->thystame; i++) {
        strcat(str, "thystame ");
    }

    return str;
}

coord_t *get_visible_tile_coords(serv_t *server, player_t *player) {
    int n = player->level + 1;
    int vision_size = (n * (2 * 1 + (n - 1) * 2)) / 2;  // Calculate number of tiles visible
    coord_t *visible_coords = calloc(vision_size, sizeof(coord_t));  // Initialize visible_coords with NULLs

    int k = 0;
    for (int i = 0; i < n; i++) {
        int row_width = 2 * i + 1;
        for (int j = 0; j < row_width; j++) {
            switch (player->orientation) {
                case 1:  // North
                    visible_coords[k].y = (player->y - i + server->max_y) % server->max_y;
                    visible_coords[k].x = (player->x + j - i + server->max_x) % server->max_x;
                    break;
                case 2:  // East
                    visible_coords[k].x = (player->x + i + server->max_x) % server->max_x;
                    visible_coords[k].y = (player->y + j - i + server->max_y) % server->max_y;
                    break;
                case 3:  // South
                    visible_coords[k].y = (player->y + i + server->max_y) % server->max_y;
                    visible_coords[k].x = (player->x - j + i + server->max_x) % server->max_x;
                    break;
                case 4:  // West
                    visible_coords[k].x = (player->x - i + server->max_x) % server->max_x;
                    visible_coords[k].y = (player->y - j + i + server->max_y) % server->max_y;
                    break;
            }
            k++;
        }
    }

    return visible_coords;
}

char *build_look_response(serv_t *server, player_t *player) {
    printf("Swag");
    int n = player->level + 1;
    int vision_size = (n * (2 * 1 + (n - 1) * 2)) / 2;  // Calculate number of tiles visible
    coord_t *visible_coords = get_visible_tile_coords(server, player);
    char *response = malloc(256 * sizeof(char));
    response[0] = '\0';  // initialize the string to be empty

    for (int i = 0; i < vision_size; i++) {
        map_t *tile = find_tile(server, visible_coords[i].x, visible_coords[i].y);
        char *tile_str = tile_to_string(tile);
        strcat(response, tile_str);
        free(tile_str);
    }
    printf("response = %s\n", response);
    return response;
}

int look(int sockfd, serv_t *serv, char *buffer)
{
    client_t *cli = get_correct_client(serv, sockfd);
    player_t *player = cli->player;
    int n = player->level + 1;
    int vision_size = (n * (2 * 1 + (n - 1) * 2)) / 2;

    if (!cli->clocking) {
        update_time_limit(serv, cli, 7, buffer);
        return 0;
    }
    cli->clocking = false;
    coord_t *visible_coords = get_visible_tile_coords(serv, player);
    char *response = build_look_response(serv, player);
    return 0;
}