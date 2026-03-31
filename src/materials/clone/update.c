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

    
    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (GRID(map, x, y + 1).data.id != id && GRID(map, x, y + 1).data.id != empty)
            copy_voxel(&GRID(map, x, y).stored_data, &GRID(map, x, y + 1).data);
    else if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (GRID(map, x, y - 1).data.id != id && GRID(map, x, y - 1).data.id != empty)
            copy_voxel(&GRID(map, x, y).stored_data, &GRID(map, x, y - 1).data);
    else if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (GRID(map, x + 1, y).data.id != id && GRID(map, x + 1, y).data.id != empty)
            copy_voxel(&GRID(map, x, y).stored_data, &GRID(map, x + 1, y).data);
    else if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (GRID(map, x - 1, y).data.id != id && GRID(map, x - 1, y).data.id != empty)
            copy_voxel(&GRID(map, x, y).stored_data, &GRID(map, x - 1, y).data);

    if (GRID(map, x, y).stored_data.id == 0)
        return;
    copy_voxel(&stored_data, &GRID(map, x, y).stored_data);

    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (GRID(map, x, y + 1).data.id == 0)
            copy_voxel(&GRID(map, x, y + 1).data, &stored_data);

    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (GRID(map, x, y - 1).data.id == 0)
            copy_voxel(&GRID(map, x, y - 1).data, &stored_data);
    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (GRID(map, x + 1, y).data.id == 0)
            copy_voxel(&GRID(map, x + 1, y).data, &stored_data);

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (GRID(map, x - 1, y).data.id == 0)
            copy_voxel(&GRID(map, x - 1, y).data, &stored_data);
}
