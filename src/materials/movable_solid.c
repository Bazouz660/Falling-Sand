/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** movable_solid.c
*/

#include "prototypes.h"

static bool move_down(map_t *map, int x, int y)
{
    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (GRID(map, x, y).data.density > GRID(map, x, y + 1).data.density && GRID(map, x, y + 1).data.state != static_solid) {
            swap_voxel(&GRID(map, x, y + 1).data, &GRID(map, x, y).data);
            return true;
        }
    return false;
}

static bool move_up(map_t *map, int x, int y)
{
    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (GRID(map, x, y).data.density > GRID(map, x, y - 1).data.density && GRID(map, x, y - 1).data.state != static_solid) {
            swap_voxel(&GRID(map, x, y - 1).data, &GRID(map, x, y).data);
            return true;
        }
    return false;
}

static bool move_down_left(map_t *map, int x, int y)
{
    if (is_in_grid(map, (sfVector2i){x + 1, y + 1}))
        if (GRID(map, x, y).data.density > GRID(map, x + 1, y + 1).data.density && GRID(map, x + 1, y + 1).data.state != static_solid) {
            swap_voxel(&GRID(map, x + 1, y + 1).data, &GRID(map, x, y).data);
            return true;
        }
    return false;
}

static bool move_down_right(map_t *map, int x, int y)
{
    if (is_in_grid(map, (sfVector2i){x - 1, y + 1}))
        if (GRID(map, x, y).data.density > GRID(map, x - 1, y + 1).data.density && GRID(map, x - 1, y + 1).data.state != static_solid) {
            swap_voxel(&GRID(map, x - 1, y + 1).data, &GRID(map, x, y).data);
            return true;
        }
    return false;
}

void move_movable_solid(map_t *map, int x, int y)
{
    if (!move_down(map, x, y)) {
        if (random_number(-100, 100) > 0) {
            if (!move_down_right(map, x, y))
                move_down_left(map, x, y);
        } else {
            if (!move_down_left(map, x, y))
                move_down_right(map, x, y);
        }
    }
}
