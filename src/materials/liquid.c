/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** liquid.c
*/

#include "prototypes.h"

static bool can_displace(data_t *src, data_t *dst)
{
    if (dst->state == static_solid)
        return false;
    if (src->density > dst->density)
        return true;
    return false;
}

static bool can_move(map_t *map, int x, int y)
{
    sfVector2i dirs[] = {{0, 1}, {1, 1}, {-1, 1}, {1, 0}, {-1, 0}};

    for (int i = 0; i < 5; i++) {
        int nx = x + dirs[i].x;
        int ny = y + dirs[i].y;
        if (is_in_grid(map, (sfVector2i){nx, ny})
            && can_displace(&GRID(map, x, y).data, &GRID(map, nx, ny).data))
            return true;
    }
    return false;
}

static int move_down(map_t *map, int x, int y)
{
    data_t data = GRID(map, x, y).data;
    int moved = 0;

    for (int i = 1; i <= data.velocity.y; i++) {
        if (!is_in_grid(map, (sfVector2i){x, y + i}))
            break;
        if (can_displace(&GRID(map, x, y + i - 1).data,
            &GRID(map, x, y + i).data)) {
            swap_voxel(&GRID(map, x, y + i).data,
                &GRID(map, x, y + i - 1).data);
            GRID(map, x, y + i).data.inertia.y = 1;
            moved++;
        } else {
            GRID(map, x, y + i - 1).data.inertia.y = 0;
            break;
        }
    }
    return moved;
}

static int move_horizontal(map_t *map, int x, int y, int dir)
{
    data_t data = GRID(map, x, y).data;
    int moved = 0;
    int max_spread = data.velocity.x;

    for (int i = 1; i <= max_spread; i++) {
        int nx = x + dir * i;
        int prev_x = x + dir * (i - 1);

        if (move_down(map, prev_x, y)) {
            moved++;
            break;
        }
        if (!is_in_grid(map, (sfVector2i){nx, y}))
            break;
        if (can_displace(&GRID(map, prev_x, y).data,
            &GRID(map, nx, y).data)) {
            swap_voxel(&GRID(map, nx, y).data, &GRID(map, prev_x, y).data);
            GRID(map, nx, y).data.inertia.x = dir;
            moved++;
        } else {
            if (GRID(map, prev_x, y).data.inertia.x != dir)
                GRID(map, prev_x, y).data.inertia.x = 0;
            break;
        }
    }
    return moved;
}

static void choose_side(map_t *map, int x, int y)
{
    data_t data = GRID(map, x, y).data;
    int side;

    if (data.inertia.x == 0)
        side = random_number(0, 1) ? 1 : -1;
    else
        side = data.inertia.x;

    if (!move_horizontal(map, x, y, side))
        move_horizontal(map, x, y, -side);
}

void move_liquid(map_t *map, int x, int y)
{
    if (apply_air_velocity(map, x, y))
        return;
    if (!can_move(map, x, y))
        return;
    if (move_down(map, x, y))
        return;
    choose_side(map, x, y);
}
