/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update_gas.c
*/

#include "prototypes.h"

bool freeze(map_t *map, int x, int y);

bool condensate(map_t *map, int x, int y)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature < 100
        && map->grid[x][y].data.temperature > 0) {
        map->grid[x][y].data = create_data(water);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

void update_steam(clock_st clock, map_t *map, int x, int y)
{
    if (!update_voxel_life_time(clock, &map->grid[x][y].data))
        return;
    if (freeze(map, x, y))
        return;
    if (condensate(map, x, y))
        return;
    move_gas(map, x, y);
}