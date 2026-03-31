/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

static bool should_detonate(map_t *map, int x, int y)
{
    int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

    if (GRID(map, x, y).data.temperature > 300)
        return true;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (is_in_grid(map, (sfVector2i){nx, ny})) {
            int nid = GRID(map, nx, ny).data.id;
            if (nid == fire || nid == lava)
                return true;
        }
    }
    int ax = x / AIR_CELL;
    int ay = y / AIR_CELL;
    if (ax >= 0 && ax < map->air_dim.x && ay >= 0 && ay < map->air_dim.y)
        if (PMAP(map, ax, ay) > EXPLOSION_PRESSURE * 0.5f)
            return true;
    return false;
}

void explode(map_t *map, int cx, int cy, int radius)
{
    int ax = cx / AIR_CELL;
    int ay = cy / AIR_CELL;

    if (ax < 0 || ax >= map->air_dim.x
        || ay < 0 || ay >= map->air_dim.y)
        return;
    PMAP(map, ax, ay) += EXPLOSION_PRESSURE;
}

void update_gunpowder(clock_st clock, map_t *map, int x, int y)
{
    if (should_detonate(map, x, y)) {
        float temp = GRID(map, x, y).data.temperature;

        GRID(map, x, y).data = create_fire();
        GRID(map, x, y).data.temperature = 1500;
        if (temp > 1500)
            GRID(map, x, y).data.temperature = temp;
        explode(map, x, y, 0);
        return;
    }
    move_movable_solid(map, x, y);
}
