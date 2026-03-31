/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"
#include <math.h>

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
        if (PMAP(map, ax, ay) > EXPLOSION_PRESSURE
            && random_number(0, 100) < 15)
            return true;
    return false;
}

void explode(map_t *map, int cx, int cy, int radius)
{
    int ax = cx / AIR_CELL;
    int ay = cy / AIR_CELL;
    int ar = radius / AIR_CELL;

    if (ax < 0 || ax >= map->air_dim.x
        || ay < 0 || ay >= map->air_dim.y)
        return;
    if (ar < 1)
        ar = 1;

    for (int y = ay - ar; y <= ay + ar; y++) {
        for (int x = ax - ar; x <= ax + ar; x++) {
            if (x < 0 || x >= map->air_dim.x || y < 0 || y >= map->air_dim.y)
                continue;
            float dx = (float)(x - ax);
            float dy = (float)(y - ay);
            float dist = sqrtf(dx * dx + dy * dy);
            if (dist > (float)ar)
                continue;

            float t = 1.0f - (dist / (float)ar);
            float burst = EXPLOSION_PRESSURE * t * t;

            PMAP(map, x, y) += burst;
        }
    }
}

void update_gunpowder(clock_st clock, map_t *map, int x, int y)
{
    if (should_detonate(map, x, y)) {
        float temp = GRID(map, x, y).data.temperature;

        GRID(map, x, y).data = create_fire();
        GRID(map, x, y).data.temperature = 700;
        if (temp > 700)
            GRID(map, x, y).data.temperature = temp;
        explode(map, x, y, AIR_CELL * 2);
        return;
    }
    move_movable_solid(map, x, y);
}
