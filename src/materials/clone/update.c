/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_clone(map_t *map, int x, int y)
{
    data_t stored_data;
    int id = clone;

    if (map->grid[x][y + 1].data.id != id && map->grid[x][y + 1].data.id != empty)
        copy_voxel(&map->grid[x][y].stored_data, &map->grid[x][y + 1].data);
    else if (map->grid[x][y - 1].data.id != id && map->grid[x][y - 1].data.id != empty)
        copy_voxel(&map->grid[x][y].stored_data, &map->grid[x][y - 1].data);
    else if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (map->grid[x + 1][y].data.id != id && map->grid[x + 1][y].data.id != empty)
            copy_voxel(&map->grid[x][y].stored_data, &map->grid[x + 1][y].data);
    else if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (map->grid[x - 1][y].data.id != id && map->grid[x - 1][y].data.id != empty)
            copy_voxel(&map->grid[x][y].stored_data, &map->grid[x - 1][y].data);

    if (map->grid[x][y].stored_data.id == 0)
        return;
    copy_voxel(&stored_data, &map->grid[x][y].stored_data);
    if (map->grid[x][y + 1].data.id == 0)
        copy_voxel(&map->grid[x][y + 1].data, &stored_data);
    if (map->grid[x][y - 1].data.id == 0)
        copy_voxel(&map->grid[x][y - 1].data, &stored_data);
    return;
    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (map->grid[x + 1][y].data.id == 0)
            copy_voxel(&map->grid[x + 1][y].data, &stored_data);

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (map->grid[x - 1][y].data.id == 0)
            copy_voxel(&map->grid[x - 1][y].data, &stored_data);
}
