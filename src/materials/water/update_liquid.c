/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

bool vaporize(map_t *map, int x, int y)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature >= 100) {
        map->grid[x][y].data = create_data(steam);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool freeze(map_t *map, int x, int y)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature < 0) {
        map->grid[x][y].data = create_data(ice);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

void update_water(map_t *map, int x, int y)
{
    if (vaporize(map, x, y))
        return;
    if (freeze(map, x, y))
        return;
    move_liquid(map, x, y);
}