/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_sand(map_t *map, int x, int y)
{
    if (melt(map, x, y, 2000, lava))
        return;
    move_movable_solid(map, x, y);
}
