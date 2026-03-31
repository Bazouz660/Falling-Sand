/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_black_hole(map_t *map, int x, int y)
{
    

    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (GRID(map, x, y + 1).data.id != 4)
            destroy_voxel(&GRID(map, x, y + 1).data);

    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (GRID(map, x, y - 1).data.id != 4)
            destroy_voxel(&GRID(map, x, y - 1).data);

    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (GRID(map, x + 1, y).data.id != 4)
            destroy_voxel(&GRID(map, x + 1, y).data);

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (GRID(map, x - 1, y).data.id != 4)
            destroy_voxel(&GRID(map, x - 1, y).data);
}
