/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** destroy.c
*/

#include "prototypes.h"

void destroy_acid(map_t *map, int x, int y)
{
    float temp = map->grid[x][y].data.temperature;
    if (random_number(-100, 100) > 0)
        destroy_voxel(&map->grid[x][y].data);
    map->grid[x][y].data.temperature += temp + 70;
}