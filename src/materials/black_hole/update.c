/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_black_hole(map_t *map, int x, int y)
{
    if (map->grid[x][y + 1].data.id != 4)
        destroy_voxel(&map->grid[x][y + 1].data);
    if (map->grid[x][y - 1].data.id != 4)
        destroy_voxel(&map->grid[x][y - 1].data);

    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (map->grid[x + 1][y].data.id != 4)
            destroy_voxel(&map->grid[x + 1][y].data);

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (map->grid[x - 1][y].data.id != 4)
            destroy_voxel(&map->grid[x - 1][y].data);
}
