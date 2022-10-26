/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

static void destroy_acid(map_t *map, int x, int y)
{
    if (random_number(-100, 100) > 0)
        destroy_voxel(&map->grid[x][y].data);
}

void update_acid(map_t *map, int x, int y, data_t *data)
{
    if (map->grid[x][y + 1].data.id != data->id && random_number(-50 * map->grid[x][y + 1].data.density, 5) > 0 && map->grid[x][y + 1].data.id != 0) {
        destroy_voxel(&map->grid[x][y + 1].data);
        destroy_acid(map, x, y);
        return;
    }
    if (map->grid[x][y - 1].data.id != data->id && random_number(-50 * map->grid[x][y - 1].data.density, 5) > 0 && map->grid[x][y - 1].data.id != 0) {
        destroy_voxel(&map->grid[x][y - 1].data);
        destroy_acid(map, x, y);
        return;
    }

    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (map->grid[x + 1][y].data.id != data->id && random_number(-50 * map->grid[x + 1][y].data.density, 5) > 0 && map->grid[x + 1][y].data.id != 0) {
            destroy_voxel(&map->grid[x + 1][y].data);
            destroy_acid(map, x, y);
            return;
        }

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (map->grid[x - 1][y].data.id != data->id && random_number(-50 * map->grid[x - 1][y].data.density, 5) > 0 && map->grid[x - 1][y].data.id != 0) {
            destroy_voxel(&map->grid[x - 1][y].data);
            destroy_acid(map, x, y);
            return;
        }

    move_liquid(map, x, y, data);
}