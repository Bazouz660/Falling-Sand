/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update_solid.c
*/

#include "prototypes.h"

bool vaporize(map_t *map, int x, int y);

static bool melt(map_t *map, int x, int y)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature > 0) {
        map->grid[x][y].data = create_data(water);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

void update_ice(map_t *map, int x, int y)
{
    if (vaporize(map, x, y))
        return;
    if (melt(map, x, y))
        return;
    0;
}