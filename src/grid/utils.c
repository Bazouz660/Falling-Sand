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

    if (pos.x < dim.x && pos.x >= 0 && pos.y < dim.y - 1 && pos.y >= 0)
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
    *dest = *src;
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
        transfered_heat = (temp1 - temp2) * get_min(a->conductivity / 10.0, b->conductivity / 10.0);
        b->temperature += transfered_heat;
        a->temperature -= transfered_heat;
        b->temperature > 10000 ? b->temperature = 10000 : 0;
        a->temperature < -253 ? a->temperature = -253 : 0;
    } else if (temp1 < temp2) {
        transfered_heat = (temp2 - temp1) * get_min(a->conductivity / 10.0, b->conductivity / 10.0);
        a->temperature += transfered_heat;
        b->temperature -= transfered_heat;
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
    ambient_heat(&map->grid[x][y].data, x, y);
    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (map->grid[x][y + 1].data.temperature != map->grid[x][y].data.temperature) {
            transfer_heat(&map->grid[x][y + 1].data, &map->grid[x][y].data);
        }

    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (map->grid[x][y - 1].data.temperature != map->grid[x][y].data.temperature) {
            transfer_heat(&map->grid[x][y - 1].data, &map->grid[x][y].data);
        }

    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (map->grid[x + 1][y].data.temperature != map->grid[x][y].data.temperature) {
            transfer_heat(&map->grid[x + 1][y].data, &map->grid[x][y].data);
        }

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (map->grid[x - 1][y].data.temperature != map->grid[x][y].data.temperature) {
            transfer_heat(&map->grid[x - 1][y].data, &map->grid[x][y].data);
        }
}
