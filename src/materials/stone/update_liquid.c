/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update_liquid.c
*/

#include "prototypes.h"

void update_lava(clock_st clock, map_t *map, int x, int y)
{
    if (solidify(map, x, y, 1000, stone))
        return;
    move_liquid(map, x, y);
}
