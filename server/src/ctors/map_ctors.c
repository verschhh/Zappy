/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map_ctors.c
*/
#include "../../includes/zappy.h"

void fill_new_node_map(map_t *new_node, args_t *arg)
{
    static int save_x = 0;
    static int save_y = 0;

    new_node->x = save_x;
    new_node->y = save_y;
    new_node->food = 0;
    new_node->linemate = 0;
    new_node->deraumere = 0;
    new_node->mendiane = 0;
    new_node->phiras = 0;
    new_node->thystame = 0;
    new_node->sibur = 0;
    new_node->next = NULL;
    save_y++;
    if (save_y >= arg->height) {
        save_x++;
        save_y = 0;
    }
}

map_t *create_map(args_t *arg)
{
    map_t *root = NULL;
    map_t *current = NULL;

    for (int i = 0; i != arg->height * arg->width; i++) {
        map_t *new_node = malloc(sizeof(map_t));
        if (new_node == NULL)
            perror("Memory allocation failed");
        fill_new_node_map(new_node, arg);
        if (root == NULL) {
            root = new_node;
            current = root;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }
    return root;
}
