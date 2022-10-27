/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_stone(map_t *map, int x, int y)
{
    if (melt(map, x, y, 1000, lava))
        return;
    0;
}
