/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

static bool move_down(map_t *map, int x, int y, data_t data)
{
    bool moved = false;

    for (int i = 1; i < data.velocity.y + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x, y + i})) {
            if (map->grid[x][y].data.density > map->grid[x][y + i].data.density) {
                swap_voxel(&map->grid[x][y + i].data, &map->grid[x][y].data);
                moved =  true;
            } else if (map->grid[x][y].data.id != map->grid[x][y + i].data.id) {
                break;
            }
        } else
            break;
    }
    return moved;
}

static bool move_up(map_t *map, int x, int y, data_t data)
{
    bool moved = false;

    for (int i = 1; i < data.velocity.y + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x, y - i})) {
            if (map->grid[x][y].data.density > map->grid[x][y - i].data.density) {
                swap_voxel(&map->grid[x][y - i].data, &map->grid[x][y].data);
                moved = true;
            } else if (map->grid[x][y].data.id != map->grid[x][y - i].data.id) {
                break;
            }
        } else
            break;
    }
    return moved;
}

static bool move_down_right(map_t *map, int x, int y, data_t data)
{
    bool moved = false;

    for (int i = 1; i < data.velocity.x + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x + i, y + i})) {
            if (map->grid[x][y].data.density > map->grid[x + i][y + i].data.density) {
                swap_voxel(&map->grid[x + i][y + i].data, &map->grid[x][y].data);
                moved = true;
            } else if (map->grid[x][y].data.id != map->grid[x + 1][y + i].data.id) {
                break;
            }
        } else
            break;
    }
    return moved;
}

static bool move_down_left(map_t *map, int x, int y, data_t data)
{
    bool moved = false;

    for (int i = 1; i < data.velocity.x + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x - i, y + i})) {
            if (map->grid[x][y].data.density > map->grid[x - i][y + i].data.density) {
                swap_voxel(&map->grid[x - i][y + i].data, &map->grid[x][y].data);
                moved = true;
            } else if (map->grid[x][y].data.id != map->grid[x - i][y + i].data.id) {
                break;
            }
        } else
            break;
    }
    return moved;
}

static bool move_right(map_t *map, int x, int y, data_t data)
{
    bool moved = false;

    for (int i = 1; i < data.velocity.x + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x + i, y})) {
            if (map->grid[x][y].data.density > map->grid[x + i][y].data.density) {
                swap_voxel(&map->grid[x + i][y].data, &map->grid[x][y].data);
                moved = true;
            } else if (map->grid[x][y].data.id != map->grid[x + i][y].data.id) {
                break;
            }
        } else
            break;
    }
    return moved;
}

static bool move_left(map_t *map, int x, int y, data_t data)
{
    bool moved = false;

    for (int i = 1; i < data.velocity.x + 1; i++) {
        if (is_in_grid(map, (sfVector2i){x - i, y})) {
            if (map->grid[x][y].data.density > map->grid[x - i][y].data.density) {
                swap_voxel(&map->grid[x - i][y].data, &map->grid[x][y].data);
                moved = true;
            } else if (map->grid[x][y].data.id != map->grid[x - i][y].data.id) {
                break;
            }
        } else
            break;
    }
    return moved;
}

static bool move_diagonal_down(map_t *map, int x, int y, data_t data)
{
    bool side = random_number(0, 1);

    if (side) {
        if (!move_down_right(map, x, y, data))
            return move_down_left(map, x, y, data);
    } else
        if (!move_down_left(map, x, y, data))
            return move_down_right(map, x, y, data);
}

static bool move_side(map_t *map, int x, int y, data_t data)
{
    bool side = random_number(0, 1);

    if (side) {
        if (!move_right(map, x, y, data))
            return move_left(map, x, y, data);
    } else
        if (!move_left(map, x, y, data))
            return move_right(map, x, y, data);
}

void update_water(map_t *map, int x, int y, data_t data)
{
    if (!move_down(map, x, y, data))
        if (!move_diagonal_down(map, x, y, data))
            move_side(map, x, y, data);

}