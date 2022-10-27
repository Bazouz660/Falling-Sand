/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

static bool melt(map_t *map, int x, int y)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature > 1000) {
        map->grid[x][y].data = create_data(lava);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

void update_stone(map_t *map, int x, int y)
{
    if (melt(map, x, y))
        return;
    0;
}
