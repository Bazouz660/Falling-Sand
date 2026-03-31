/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_wood(map_t *map, int x, int y)
{
    if (burn(&GRID(map, x, y).data, 600))
        return;
    0;
}
