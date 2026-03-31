/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** pressure.c - Coarse-grid air simulation
**
** Wave equation: advection carries pressure along velocity,
** gradient converts pressure differences into velocity.
** Hot gases act as pressure sources (thermal expansion).
** Open boundaries: outside the simulation is ambient pressure.
*/

#include "prototypes.h"
#include <string.h>

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

static bool is_inside(int aw, int ah, int x, int y)
{
    return x >= 0 && x < aw && y >= 0 && y < ah;
}

static bool is_open(bool *blocked, int aw, int ah, int x, int y)
{
    if (!is_inside(aw, ah, x, y))
        return false;
    return !blocked[y * aw + x];
}

static float sample_pressure(map_t *map, bool *blocked, int x, int y)
{
    if (!is_inside(map->air_dim.x, map->air_dim.y, x, y))
        return 0.0f;
    if (blocked[y * map->air_dim.x + x])
        return 0.0f;
    return PMAP(map, x, y);
}

static void advect_pressure(map_t *map, bool *blocked)
{
    int aw = map->air_dim.x;
    int ah = map->air_dim.y;
    int n = aw * ah;
    float *new_p = malloc(sizeof(float) * n);

    memset(new_p, 0, sizeof(float) * n);

    for (int y = 0; y < ah; y++) {
        for (int x = 0; x < aw; x++) {
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

            int ix = (int)src_x;
            int iy = (int)src_y;
            float fx = src_x - ix;
            float fy = src_y - iy;

            int ix1 = ix + 1;
            int iy1 = iy + 1;

            float p00 = sample_pressure(map, blocked, ix, iy);
            float p10 = sample_pressure(map, blocked, ix1, iy);
            float p01 = sample_pressure(map, blocked, ix, iy1);
            float p11 = sample_pressure(map, blocked, ix1, iy1);

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

    for (int y = 0; y < ah; y++) {
        for (int x = 0; x < aw; x++) {
            if (blocked[y * aw + x])
                continue;

            float p = PMAP(map, x, y);

            float pl = is_inside(aw, ah, x - 1, y)
                ? (is_open(blocked, aw, ah, x - 1, y) ? PMAP(map, x - 1, y) : p)
                : 0.0f;
            float pr = is_inside(aw, ah, x + 1, y)
                ? (is_open(blocked, aw, ah, x + 1, y) ? PMAP(map, x + 1, y) : p)
                : 0.0f;
            float pu = is_inside(aw, ah, x, y - 1)
                ? (is_open(blocked, aw, ah, x, y - 1) ? PMAP(map, x, y - 1) : p)
                : 0.0f;
            float pd = is_inside(aw, ah, x, y + 1)
                ? (is_open(blocked, aw, ah, x, y + 1) ? PMAP(map, x, y + 1) : p)
                : 0.0f;

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
            float damp = AIR_LOSS;

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
