/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** pressure.c - Coarse-grid air simulation
**
** Wave equation: advection carries pressure along velocity,
** gradient converts pressure differences into velocity.
** Hot gases act as pressure sources (thermal expansion).
** Sponge layer at edges absorbs outgoing waves.
*/

#include "prototypes.h"
#include <string.h>

#define SPONGE_WIDTH 5

static void scan_grid(map_t *map, bool *blocked, float *heat_src)
{
    int aw = map->air_dim.x;
    int ah = map->air_dim.y;

    for (int ay = 0; ay < ah; ay++) {
        for (int ax = 0; ax < aw; ax++) {
            int bx = ax * AIR_CELL;
            int by = ay * AIR_CELL;
            int solid = 0;
            float heat = 0;

            for (int dy = 0; dy < AIR_CELL; dy++)
                for (int dx = 0; dx < AIR_CELL; dx++) {
                    int px = bx + dx;
                    int py = by + dy;
                    if (px < map->dim.x && py < map->dim.y) {
                        data_t *d = &GRID(map, px, py).data;
                        if (d->state == static_solid)
                            solid++;
                        if (d->id != empty && d->state == gas
                            && d->temperature > 100)
                            heat += (d->temperature - 100);
                    }
                }
            blocked[ay * aw + ax] = solid > (AIR_CELL * AIR_CELL) / 2;
            heat_src[ay * aw + ax] = heat;
        }
    }
}

static bool is_open(bool *blocked, int aw, int ah, int x, int y)
{
    if (x < 0 || x >= aw || y < 0 || y >= ah)
        return false;
    return !blocked[y * aw + x];
}

static float get_sponge_factor(int x, int y, int aw, int ah)
{
    int dx = x;
    if (aw - 1 - x < dx) dx = aw - 1 - x;
    int dy = y;
    if (ah - 1 - y < dy) dy = ah - 1 - y;
    int dist = dx < dy ? dx : dy;

    if (dist >= SPONGE_WIDTH)
        return 1.0f;
    return (float)dist / (float)SPONGE_WIDTH;
}

static void advect_pressure(map_t *map, bool *blocked)
{
    int aw = map->air_dim.x;
    int ah = map->air_dim.y;
    int n = aw * ah;
    float *new_p = malloc(sizeof(float) * n);

    memset(new_p, 0, sizeof(float) * n);

    for (int y = 1; y < ah - 1; y++) {
        for (int x = 1; x < aw - 1; x++) {
            if (blocked[y * aw + x])
                continue;

            float cvx = VX(map, x, y);
            float cvy = VY(map, x, y);

            if (cvx > MAX_CFL) cvx = MAX_CFL;
            if (cvx < -MAX_CFL) cvx = -MAX_CFL;
            if (cvy > MAX_CFL) cvy = MAX_CFL;
            if (cvy < -MAX_CFL) cvy = -MAX_CFL;

            float src_x = (float)x - cvx;
            float src_y = (float)y - cvy;

            if (src_x < 0.5f) src_x = 0.5f;
            if (src_y < 0.5f) src_y = 0.5f;
            if (src_x > aw - 1.5f) src_x = aw - 1.5f;
            if (src_y > ah - 1.5f) src_y = ah - 1.5f;

            int ix = (int)src_x;
            int iy = (int)src_y;
            float fx = src_x - ix;
            float fy = src_y - iy;

            int ix1 = ix + 1 < aw ? ix + 1 : ix;
            int iy1 = iy + 1 < ah ? iy + 1 : iy;

            float p00 = is_open(blocked, aw, ah, ix, iy)
                ? PMAP(map, ix, iy) : 0;
            float p10 = is_open(blocked, aw, ah, ix1, iy)
                ? PMAP(map, ix1, iy) : 0;
            float p01 = is_open(blocked, aw, ah, ix, iy1)
                ? PMAP(map, ix, iy1) : 0;
            float p11 = is_open(blocked, aw, ah, ix1, iy1)
                ? PMAP(map, ix1, iy1) : 0;

            float top = p00 * (1.0f - fx) + p10 * fx;
            float bot = p01 * (1.0f - fx) + p11 * fx;
            new_p[y * aw + x] = top * (1.0f - fy) + bot * fy;
        }
    }
    memcpy(map->pmap, new_p, sizeof(float) * n);
    free(new_p);
}

static void apply_gradient(map_t *map, bool *blocked)
{
    int aw = map->air_dim.x;
    int ah = map->air_dim.y;

    for (int y = 1; y < ah - 1; y++) {
        for (int x = 1; x < aw - 1; x++) {
            if (blocked[y * aw + x])
                continue;

            float p = PMAP(map, x, y);

            float pl = is_open(blocked, aw, ah, x - 1, y)
                ? PMAP(map, x - 1, y) : p;
            float pr = is_open(blocked, aw, ah, x + 1, y)
                ? PMAP(map, x + 1, y) : p;
            float pu = is_open(blocked, aw, ah, x, y - 1)
                ? PMAP(map, x, y - 1) : p;
            float pd = is_open(blocked, aw, ah, x, y + 1)
                ? PMAP(map, x, y + 1) : p;

            VX(map, x, y) += (pl - pr) * VELOCITY_FACTOR;
            VY(map, x, y) += (pu - pd) * VELOCITY_FACTOR;
        }
    }
}

void update_pressure(map_t *map)
{
    int aw = map->air_dim.x;
    int ah = map->air_dim.y;
    int n = aw * ah;
    bool *blocked = malloc(sizeof(bool) * n);
    float *heat_src = malloc(sizeof(float) * n);

    scan_grid(map, blocked, heat_src);

    for (int iter = 0; iter < PRESSURE_ITERATIONS; iter++) {
        advect_pressure(map, blocked);
        apply_gradient(map, blocked);
    }

    for (int y = 0; y < ah; y++) {
        for (int x = 0; x < aw; x++) {
            float sponge = get_sponge_factor(x, y, aw, ah);
            float damp = AIR_LOSS * sponge;

            PMAP(map, x, y) *= damp;
            VX(map, x, y) *= damp;
            VY(map, x, y) *= damp;
            if (!blocked[y * aw + x])
                PMAP(map, x, y) += heat_src[y * aw + x] * HEAT_PRESSURE_FACTOR;
        }
    }
    free(heat_src);
    free(blocked);
}
