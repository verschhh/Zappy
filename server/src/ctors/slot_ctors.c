/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** slot_ctors.c
*/

#include "../includes/zappy.h"

void new_slot(slot_t *slot, char *name)
{
    slot_t *new_slot = malloc(sizeof(slot_t));
    slot_t *tmp = slot;

    if (slot == NULL)
        return;
    new_slot->team_name = name;
    new_slot->nb = slot->nb;
    new_slot->next = NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_slot;
}

slot_t *slot_ctor(args_t *arg)
{
    slot_t *slot = malloc(sizeof(slot_t));

    if (slot == NULL)
        perror("Memory allocation failed");
    slot->team_name = arg->names[0];
    slot->nb = arg->clientsnb;
    slot->next = NULL;
    printf("Namescout = %d\n", arg->namescount);
    for (int i = 0; i < arg->namescount; i++) {
        new_slot(slot, arg->names[i]);
    }
    return slot;
}