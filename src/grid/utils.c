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
    sfVector2u w_size = c->render.w_size;
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

    if (pos.x < dim.x - 1 && pos.x >= 0 && pos.y < dim.y && pos.y >= 0)
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
    a->color = sfBlack;
    a->density = 0;
    a->has_updated = false;
    a->id = 0;
    a->state = -1;
    a->life_time = 0;
    a->life_counter = 0;
    a->inertia = (sfVector2i){0, 0};
    a->speed = (sfVector2u){0, 0};
    a->velocity = (sfVector2i){0, 0};
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
