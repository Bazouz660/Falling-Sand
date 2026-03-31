/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** gas.c
*/

#include "prototypes.h"

static bool can_move(map_t *map, int x, int y)
{
    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (GRID(map, x, y).data.density > GRID(map, x, y - 1).data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x + 1, y - 1}))
        if (GRID(map, x, y).data.density > GRID(map, x + 1, y - 1).data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x - 1, y - 1}))
        if (GRID(map, x, y).data.density > GRID(map, x - 1, y - 1).data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (GRID(map, x, y).data.density > GRID(map, x + 1, y).data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (GRID(map, x, y).data.density > GRID(map, x - 1, y).data.density);
            return true;
    return false;
}

static bool move_up(map_t *map, int x, int y)
{
    data_t data = GRID(map, x, y).data;
    unsigned int moved = 0;

    for (int i = 1; i < data.velocity.y - 1; i++) {
        if (is_in_grid(map, (sfVector2i){x, y - i})) {
            if (GRID(map, x, y - i + 1).data.density > GRID(map, x, y - i).data.density && GRID(map, x, y - i).data.state != static_solid) {
                swap_voxel(&GRID(map, x, y - i).data, &GRID(map, x, y - i + 1).data);
                GRID(map, x, y - i).data.inertia.y = -1;
                moved++;
            } else {
                GRID(map, x, y - i + 1).data.inertia.y = 0;
                break;
            }
        } else {
            GRID(map, x, y - i + 1).data.inertia.y = 0;
            break;
        }
    }
    return moved;
}

static bool move_right(map_t *map, int x, int y)
{
    data_t data = GRID(map, x, y).data;
    unsigned int moved = 0;
    int avail_moves = data.velocity.x;
    int i = 1;

    while (i < avail_moves) {
        moved = 0;
        if (moved = move_up(map, x, y))
            if (random_number(-100, 100) <= 0)
                break;
        y -= moved;
        if (is_in_grid(map, (sfVector2i){x + i, y})) {
            if (GRID(map, x + i - 1, y).data.density > GRID(map, x + i, y).data.density && GRID(map, x + i, y).data.state != static_solid) {
                swap_voxel(&GRID(map, x + i, y).data, &GRID(map, x + i - 1, y).data);
                GRID(map, x + i, y).data.inertia.x = 1;
                i++;
            } else if (!move_up(map, x + i - 1, y)) {
                if (GRID(map, x + i - 1, y).data.inertia.x != GRID(map, x + i, y).data.inertia.x)
                    GRID(map, x + i - 1, y).data.inertia.x = 0;
                break;
            }
        } else {
            GRID(map, x + i - 1, y).data.inertia.x = 0;
            break;
        }
    }
    return i;
}

static bool move_left(map_t *map, int x, int y)
{
    data_t data = GRID(map, x, y).data;
    unsigned int moved = 0;
    int avail_moves = data.velocity.x;
    int i = 1;

    while (i < avail_moves) {
        moved = 0;
        if (moved = move_up(map, x, y))
            if (random_number(-100, 100) <= 0)
                break;
        y -= moved;
        if (is_in_grid(map, (sfVector2i){x - i, y})) {
            if (GRID(map, x - i + 1, y).data.density > GRID(map, x - i, y).data.density && GRID(map, x - i, y).data.state != static_solid) {
                swap_voxel(&GRID(map, x - i, y).data, &GRID(map, x - i + 1, y).data);
                GRID(map, x - i, y).data.inertia.x = -1;
                i++;
            } else if (!move_up(map, x - i + 1, y)) {
                if (GRID(map, x - i, y).data.inertia.x != GRID(map, x - i + 1, y).data.inertia.x)
                    GRID(map, x - i + 1, y).data.inertia.x = 0;
                break;
            }
        } else {
            GRID(map, x - i + 1, y).data.inertia.x = 0;
            break;
        }
    }
    return i;
}

static bool choose_side(map_t *map, int x, int y)
{
    data_t data = GRID(map, x, y).data;
    bool side;

    if (data.inertia.x == 0)
        side = random_number(0, 1);
    else if (data.inertia.x == 1)
        side = 1;
    else if (data.inertia.x == -1)
        side = 0;

    if (side) {
        if (!move_right(map, x, y))
            return move_left(map, x, y);
    } else
        if (!move_left(map, x, y))
            return move_right(map, x, y);
}

void move_gas(map_t *map, int x, int y)
{
    if (!can_move(map, x, y)) {
        return;
    }
    choose_side(map, x, y);
}