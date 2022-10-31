/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_smoke(clock_st clock, map_t *map, int x, int y)
{
    if (!update_voxel_life_time(clock, &map->grid[x][y].data))
        return;
    move_gas(map, x, y);
}