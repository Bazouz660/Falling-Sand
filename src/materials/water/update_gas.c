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

    move_gas(map, x, y, map->grid[x][y].data);
}