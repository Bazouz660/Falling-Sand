/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update_liquid.c
*/

#include "prototypes.h"

bool solidfy(map_t *map, int x, int y)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature <= 1000) {
        map->grid[x][y].data = create_data(stone);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

void update_lava(clock_st clock, map_t *map, int x, int y)
{
    if (solidfy(map, x, y))
        return;
    move_liquid(map, x, y);
}
