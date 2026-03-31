/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** utils.c
*/

#include "prototypes.h"

sfVector2i get_mouse_grid(core_t *c)
{
    sfVector2i m_pos = c->mouse.pos;
    sfVector2u w_size = {c->render.w_size.x * 0.9, c->render.w_size.y};
    sfVector2f ratio = {(float)w_size.x / (float)c->map.dim.x,
    (float)w_size.y / (float)c->map.dim.y};
    sfVector2f m_pos_view = {m_pos.x / ratio.x, m_pos.y / ratio.y};
    sfVector2i res = {-1, -1};

    if (c->mouse.pos.x < w_size.x && c->mouse.pos.y < w_size.y
        && c->mouse.pos.x >= 0 && c->mouse.pos.y >= 0) {
        res = (sfVector2i){(int)m_pos_view.x, (int)m_pos_view.y};
        res.y >= c->map.dim.y ? (res.y = c->map.dim.y - 1) : 0;
        res.x >= c->map.dim.x ? (res.x = c->map.dim.x - 1) : 0;
        return res;
    }
    return res;
}

bool is_in_grid(map_t *map, sfVector2i pos)
{
    sfVector2i dim = map->dim;

    if (pos.x < dim.x && pos.x >= 0 && pos.y < dim.y && pos.y >= 0)
        return true;
    return false;
}

void swap_voxel(data_t *a, data_t *b)
{
    data_t tmp = *a;

    *a = *b;
    *b = tmp;
    a->has_updated = true;
}

void copy_voxel(data_t *dest, data_t *src)
{
    *dest = create_data(src->id);
    dest->has_updated = true;
}

void destroy_voxel(data_t *a)
{
    if (a->id == 0)
        return;
    *a = create_data(empty);
}

bool update_voxel_life_time(clock_st clock, data_t *data)
{
    data->life_counter += clock.frame_delta;
    if (data->life_counter >= data->life_time && random_number(-100, 10) > 0) {
        destroy_voxel(data);
        return false;
    }
    return true;
}

float get_conductivity(int id)
{
    if (id < 0 || id > 8)
        return 0;
    return create_data(id).conductivity;
}

void transfer_heat(data_t *a, data_t *b)
{
    float transfered_heat = 0;

    if (a->id == empty || b->id == empty || a->has_updated == true)
        return;

    float temp1 = a->temperature / 4.0;
    float temp2 = b->temperature / 4.0;


    if (temp1 > temp2) {
        transfered_heat = (temp1 - temp2);
        b->temperature += transfered_heat * (a->conductivity / 10.0);
        a->temperature -= transfered_heat * (b->conductivity / 10.0);
        b->temperature > 10000 ? b->temperature = 10000 : 0;
        a->temperature < -253 ? a->temperature = -253 : 0;
    } else if (temp1 < temp2) {
        transfered_heat = (temp2 - temp1);
        a->temperature += transfered_heat * (b->conductivity / 10.0);
        b->temperature -= transfered_heat * (a->conductivity / 10.0);
        a->temperature > 10000 ? a->temperature = 10000 : 0;
        b->temperature < -253 ? b->temperature = -253 : 0;
    }
}

void ambient_heat(data_t *a, int x, int y)
{
    float transfered_heat = 0;

    float temp1 = a->temperature / 4.0;
    float temp2 = 20;

    if (temp1 > temp2) {
        transfered_heat = (temp1 - temp2) * (a->conductivity / 10000.0);
        a->temperature -= transfered_heat;
        a->temperature < -253 ? a->temperature = -253 : 0;
    } else if (temp1 < temp2) {
        transfered_heat = (temp2 - temp1) * (a->conductivity / 10000.0);
        a->temperature += transfered_heat;
        a->temperature > 10000 ? a->temperature = 10000 : 0;
    }
}

void update_heat(map_t *map, int x, int y)
{
    ambient_heat(&GRID(map, x, y).data, x, y);
    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (GRID(map, x, y + 1).data.temperature != GRID(map, x, y).data.temperature) {
            transfer_heat(&GRID(map, x, y + 1).data, &GRID(map, x, y).data);
        }

    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (GRID(map, x, y - 1).data.temperature != GRID(map, x, y).data.temperature) {
            transfer_heat(&GRID(map, x, y - 1).data, &GRID(map, x, y).data);
        }

    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (GRID(map, x + 1, y).data.temperature != GRID(map, x, y).data.temperature) {
            transfer_heat(&GRID(map, x + 1, y).data, &GRID(map, x, y).data);
        }

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (GRID(map, x - 1, y).data.temperature != GRID(map, x, y).data.temperature) {
            transfer_heat(&GRID(map, x - 1, y).data, &GRID(map, x, y).data);
        }
}

void apply_pressure_effects(map_t *map, int x, int y)
{
    data_t *d = &GRID(map, x, y).data;
    int ax = x / AIR_CELL;
    int ay = y / AIR_CELL;

    if (d->id == empty)
        return;
    if (ax < 0 || ax >= map->air_dim.x
        || ay < 0 || ay >= map->air_dim.y)
        return;

    float p = PMAP(map, ax, ay);
    float ap = p > 0 ? p : -p;

    if (ap > 10.0f)
        d->temperature += ap * 0.02f;
    if (ap > 80.0f && d->state != static_solid
        && random_number(0, 1000) < (int)(ap * 0.3f)) {
        destroy_voxel(d);
    }
    if (ap > 200.0f && d->state == static_solid
        && d->id != black_hole
        && random_number(0, 1000) < (int)(ap * 0.05f)) {
        destroy_voxel(d);
    }
}

bool apply_air_velocity(map_t *map, int x, int y)
{
    int ax = x / AIR_CELL;
    int ay = y / AIR_CELL;

    if (ax < 0 || ax >= map->air_dim.x
        || ay < 0 || ay >= map->air_dim.y)
        return false;

    float vel_x = VX(map, ax, ay);
    float vel_y = VY(map, ax, ay);
    bool moved = false;
    int cx = x;
    int cy = y;

    if (vel_x > -0.5f && vel_x < 0.5f
        && vel_y > -0.5f && vel_y < 0.5f)
        return false;

    int dy = vel_y > 0 ? 1 : (vel_y < 0 ? -1 : 0);
    int abs_y = (int)(vel_y > 0 ? vel_y : -vel_y);
    if (abs_y > 8) abs_y = 8;

    for (int i = 0; i < abs_y; i++) {
        int ny = cy + dy;
        if (!is_in_grid(map, (sfVector2i){cx, ny}))
            break;
        data_t *dst = &GRID(map, cx, ny).data;
        if (dst->id == empty || (dst->state != static_solid
            && GRID(map, cx, cy).data.density > dst->density)) {
            swap_voxel(&GRID(map, cx, cy).data, dst);
            cy = ny;
            moved = true;
        } else
            break;
    }

    int dx = vel_x > 0 ? 1 : (vel_x < 0 ? -1 : 0);
    int abs_x = (int)(vel_x > 0 ? vel_x : -vel_x);
    if (abs_x > 8) abs_x = 8;

    for (int i = 0; i < abs_x; i++) {
        int nx = cx + dx;
        if (!is_in_grid(map, (sfVector2i){nx, cy}))
            break;
        data_t *dst = &GRID(map, nx, cy).data;
        if (dst->id == empty || (dst->state != static_solid
            && GRID(map, cx, cy).data.density > dst->density)) {
            swap_voxel(&GRID(map, cx, cy).data, dst);
            cx = nx;
            moved = true;
        } else
            break;
    }
    return moved;
}
