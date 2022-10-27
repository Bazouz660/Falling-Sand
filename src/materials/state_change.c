/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** state_change.c
*/

#include "prototypes.h"

bool condensate(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature < threshold
        && map->grid[x][y].data.temperature > 0) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool vaporize(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature >= threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool solidify(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature < threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool melt(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature > threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool sublimate(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature > threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}
