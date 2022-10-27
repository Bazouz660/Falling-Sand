/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update_gas.c
*/

#include "prototypes.h"

void update_steam(clock_st clock, map_t *map, int x, int y)
{
    if (!update_voxel_life_time(clock, &map->grid[x][y].data))
        return;
    if (solidify(map, x, y, 0, ice))
        return;
    if (condensate(map, x, y, 100, water))
        return;
    move_gas(map, x, y);
}