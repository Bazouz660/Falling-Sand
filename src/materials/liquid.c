/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** liquid.c
*/

#include "prototypes.h"

static bool can_move(map_t *map, int x, int y)
{
    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (map->grid[x][y].data.density > map->grid[x][y + 1].data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x + 1, y + 1}))
        if (map->grid[x][y].data.density > map->grid[x + 1][y + 1].data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x - 1, y + 1}))
        if (map->grid[x][y].data.density > map->grid[x - 1][y + 1].data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (map->grid[x][y].data.density > map->grid[x + 1][y].data.density);
            return true;
    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (map->grid[x][y].data.density > map->grid[x - 1][y].data.density);
            return true;
    return false;
}

static bool move_down(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
    unsigned int moved = 0;

    for (int i = 1; i < data.velocity.y + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x, y + i})) {
            if (map->grid[x][y + i - 1].data.density > map->grid[x][y + i].data.density) {
                swap_voxel(&map->grid[x][y + i].data, &map->grid[x][y + i - 1].data);
                map->grid[x][y + i].data.inertia.y = 1;
                moved++;
            } else {
                map->grid[x][y + i - 1].data.inertia.y = 0;
                break;
            }
        } else {
            map->grid[x][y + i - 1].data.inertia.y = 0;
            break;
        }
    }
    return moved;
}

static bool move_up(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
    bool moved = false;

    for (int i = 1; i < data.velocity.y + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x, y - i})) {
            if (map->grid[x][y - i + 1].data.density > map->grid[x][y - i].data.density) {
                swap_voxel(&map->grid[x][y - i].data, &map->grid[x][y - i + 1].data);
                moved = true;
            } else {
                break;
            }
        } else
            break;
    }
    return moved;
}

static bool move_down_right(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
    unsigned short moved = 0;

    for (int i = 1; i < data.velocity.x + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x + i, y + i})) {
            if (map->grid[x + i - 1][y + i - 1].data.density > map->grid[x + i][y + i].data.density) {
                swap_voxel(&map->grid[x + i][y + i].data, &map->grid[x + i - 1][y + i - 1].data);
                map->grid[x + i][y + i].data.inertia.y = 1;
                moved++;
            } else {
                map->grid[x + i - 1][y + i - 1].data.inertia.y = 0;
                break;
            }
        } else {
            map->grid[x + i - 1][y + i - 1].data.inertia.y = 0;
            break;
        }
    }
    return moved;
}

static short move_down_left(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
    unsigned short moved = 0;

    for (int i = 1; i < data.velocity.x + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x - i, y + i})) {
            if (map->grid[x - i + 1][y + i - 1].data.density > map->grid[x - i][y + i].data.density) {
                swap_voxel(&map->grid[x - i][y + i].data, &map->grid[x - i + 1][y + i - 1].data);
                map->grid[x - i][y + i].data.inertia.y = 1;
                moved++;
            } else {
                map->grid[x - i + 1][y + i - 1].data.inertia.y = 0;
                break;
            }
        } else {
            map->grid[x - i + 1][y + i - 1].data.inertia.y = 0;
            break;
        }
    }
    return moved;
}

static bool move_diagonal_down(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
    bool side = random_number(0, 1);

    if (side) {
        if (!move_down_right(map, x, y))
            return move_down_left(map, x, y);
    } else
        if (!move_down_left(map, x, y))
            return move_down_right(map, x, y);
}

static bool move_right(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
    unsigned int moved = 0;
    sfVector2i avail_moves = {data.velocity.x, data.velocity.y};
    sfVector2i i = {1, 1};

    while (i.x < avail_moves.x && i.y < avail_moves.y) {
        moved = 0;
        if (move_down(map, x + i.x - 1, y + i.y - 1))
            break;
        if (is_in_grid(map, (sfVector2i){x + i.x, y + i.y - 1})) {
            if (map->grid[x + i.x - 1][y].data.density > map->grid[x + i.x][y].data.density) {
                swap_voxel(&map->grid[x + i.x][y].data, &map->grid[x + i.x - 1][y].data);
                map->grid[x + i.x][y].data.inertia.x = 1;
                i.x ++;
            } else if (!move_down(map, x + i.x - 1, y + i.y - 1)) {
                if (map->grid[x + i.x - 1][y].data.inertia.x != map->grid[x + i.x][y].data.inertia.x)
                    map->grid[x + i.x - 1][y].data.inertia.x = 0;
                break;
            }
        } else {
            map->grid[x + i.x - 1][y].data.inertia.x = 0;
            break;
        }
    }
    return get_max(i.x, i.y);
}

static bool move_left(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
    unsigned int moved = 0;
    sfVector2i avail_moves = {data.velocity.x, data.velocity.y};
    sfVector2i i = {1, 1};

    while (i.x < avail_moves.x && i.y < avail_moves.y) {
        moved = 0;
        if (move_down(map, x - i.x + 1, y + i.y - 1))
            break;
        if (is_in_grid(map, (sfVector2i){x - i.x, y + i.y - 1})) {
            if (map->grid[x - i.x + 1][y].data.density > map->grid[x - i.x][y].data.density) {
                swap_voxel(&map->grid[x - i.x][y].data, &map->grid[x - i.x + 1][y].data);
                map->grid[x - i.x][y].data.inertia.x = -1;
                i.x++;
            } else if (!move_down(map, x - i.x + 1, y + i.y - 1)) {
                if (map->grid[x - i.x][y].data.inertia.x != map->grid[x - i.x + 1][y].data.inertia.x)
                    map->grid[x - i.x + 1][y].data.inertia.x = 0;
                break;
            }
        } else {
            map->grid[x - i.x + 1][y].data.inertia.x = 0;
            break;
        }
    }
    return get_max(i.x, i.y);
}

static bool choose_side(map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;
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

void move_liquid(map_t *map, int x, int y, data_t *data)
{
    if (!can_move(map, x, y)) {
        return;
    }
    choose_side(map, x, y);
}
