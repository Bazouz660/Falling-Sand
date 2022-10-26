/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void resize_brush(core_t *c)
{
    if (c->events.input.type == sfEvtMouseWheelMoved) {
        if (c->events.input.mouseWheel.delta == 1 && c->brush.radius < 30) {
            c->brush.radius += 1;
        }
        if (c->events.input.mouseWheel.delta == -1 && c->brush.radius > 1) {
            c->brush.radius -= 1;
        }
    }
}

data_t create_data(int id)
{
    data_t data;

    if (id == 0) {
        data.has_updated = false;
        data.id = empty;
        data.density = 0;
        data.color = sfBlack;
        data.state = -1;
        data.inertia = (sfVector2i){0, 0};
        data.life_time = INFINITY;
        data.life_counter = 0;
        data.velocity = (sfVector2i){1, gravity};

    }
    if (id == 1) {
        data.has_updated = false;
        data.id = sand;
        data.density = 18.5;
        data.color = sfYellow;
        data.state = movable_solid;
        data.inertia = (sfVector2i){0, 0};
        data.life_time = INFINITY;
        data.life_counter = 0;
        data.color = darken_color(data.color, random_number(70, 100) / 100.0);
        data.velocity = (sfVector2i){1, gravity};
    }
    if (id == 2) {
        data.has_updated = false;
        data.id = water;
        data.density = 9.97;
        data.color = sfCyan;
        data.state = liquid;
        data.inertia = (sfVector2i){0, 0};
        data.life_time = INFINITY;
        data.life_counter = 0;
        data.color = darken_color(data.color, random_number(90, 100) / 100.0);
        data.velocity = (sfVector2i){10, gravity};
    }
    if (id == 3) {
        data.has_updated = false;
        data.id = stone;
        data.density = 24.5;
        data.state = static_solid;
        data.color = darken_color(sfWhite, 0.8);
        data.inertia = (sfVector2i){0, 0};
        data.life_time = INFINITY;
        data.life_counter = 0;
        data.color = darken_color(data.color, random_number(80, 100) / 100.0);
        data.velocity = (sfVector2i){0, 0};
    }
    if (id == 4) {
        data.has_updated = false;
        data.id = black_hole;
        data.state = static_solid;
        data.density = 1000000;
        data.color = darken_color(sfRed, 0.3);
        data.inertia = (sfVector2i){0, 0};
        data.life_time = INFINITY;
        data.life_counter = 0;
        data.color = darken_color(data.color, random_number(80, 100) / 100.0);
        data.velocity = (sfVector2i){0, 0};
    }
    if (id == 5) {
        data.has_updated = false;
        data.id = acid;
        data.density = 1.05;
        data.state = liquid;
        data.color = sfGreen;
        data.inertia = (sfVector2i){0, 0};
        data.life_time = INFINITY;
        data.life_counter = 0;
        data.color = darken_color(data.color, random_number(95, 100) / 100.0);
        data.velocity = (sfVector2i){8, gravity};
    }
    if (id == 6) {
        data.has_updated = false;
        data.id = clone;
        data.density = 300.0;
        data.state = static_solid;
        data.color = sfYellow;
        data.inertia = (sfVector2i){0, 0};
        data.life_time = INFINITY;
        data.life_counter = 0;
        data.velocity = (sfVector2i){0, 0};
    }
    if (id == 7) {
        data.has_updated = false;
        data.id = steam;
        data.density = 0.6;
        data.state = gas;
        data.inertia = (sfVector2i){0, 0};
        data.life_time = 10.0;
        data.life_counter = 0;
        data.color = smooth_color(sfCyan, sfWhite, 0.6);
        data.velocity = (sfVector2i){5, gravity};
    }
    return data;
}

bool inside_circle(sfVector2i center, sfVector2i tile, float radius)
{
    float dx = center.x - tile.x;
    float dy = center.y - tile.y;
    float distance = sqrt(dx*dx + dy*dy);

    return distance <= radius;
}

void place_in_range(core_t *c, sfVector2i center, int radius, int id)
{
    data_t data = create_data(id);

    radius = radius / 2;
    if (c->map.grid[center.x][center.y].data.id == 0 || id == 0)
        c->map.grid[center.x][center.y].data = data;

    //for (int i = -(radius / 2); i < (radius / 2); i++) {
    //    for (int j = -(radius / 2); j < (radius / 2); j++) {
    //        if (is_in_grid(&c->map, (sfVector2i){center.x, center.y + j}) && )
    //            if (c->map.grid[center.x][center.y + j].data.id == 0 || id == 0)
    //                c->map.grid[center.x][center.y + j].data = create_data(id);
    //        if (is_in_grid(&c->map, (sfVector2i){center.x + i, center.y}))
    //            if (c->map.grid[center.x + i][center.y].data.id == 0 || id == 0)
    //                c->map.grid[center.x + i][center.y].data = create_data(id);
    //    }
    //}
    for (int y = -radius - 1; y <= radius; y++) {
        for (int x = -radius - 1; x <= radius; x++) {
            if (inside_circle(center, (sfVector2i){center.x + x, center.y + y}, radius)) {
              if (is_in_grid(&c->map, (sfVector2i){center.x + x, center.y + y}))
                  if (c->map.grid[center.x + x][center.y + y].data.id == 0 || id == 0) {
                    if (id == 0)
                        destroy_voxel(&c->map.grid[center.x + x][center.y + y].data);
                    else
                        c->map.grid[center.x + x][center.y + y].data = create_data(id);
                  }
            }
        }
    }


}

void place_voxel(core_t *c)
{
    sfVector2i m_pos = get_mouse_grid(c);

    if (m_pos.x >= 0 && m_pos.y >= 0) {
        //c->map.last_cell = c->map.current_cell;
        //if (c->map.grid[c->map.last_cell.x][c->map.last_cell.y].data.id == 0)
        //    c->map.grid[c->map.last_cell.x][c->map.last_cell.y].data.color = sfBlack;
        //c->map.grid[m_pos.x][m_pos.y].data.color = sfGreen;
        //c->map.current_cell = (sfVector2u){m_pos.x,
        //m_pos.y};
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            place_in_range(c, m_pos, c->brush.radius, c->brush.id);
        }
        if (sfMouse_isButtonPressed(sfMouseRight)) {
            place_in_range(c, m_pos, c->brush.radius, 0);
        }
    }
}

void select_voxel(core_t *c)
{
    if (key_pressed(sfKeyNum1))
        c->brush.id = 1;
    if (key_pressed(sfKeyNum2))
        c->brush.id = 2;
    if (key_pressed(sfKeyNum3))
        c->brush.id = 3;
    if (key_pressed(sfKeyNum4))
        c->brush.id = 4;
    if (key_pressed(sfKeyNum5))
        c->brush.id = 5;
    if (key_pressed(sfKeyNum6))
        c->brush.id = 6;
    if (key_pressed(sfKeyNum7))
        c->brush.id = 7;
}

void update_brush(core_t *c)
{
    sfVector2i m_pos = get_mouse_pos_view(c);

    select_voxel(c);
    place_voxel(c);
    sfCircleShape_setRadius(c->brush.shape, c->brush.radius);
    sfCircleShape_setOrigin(c->brush.shape, get_circle_center(c->brush.shape));
    sfCircleShape_setPosition(c->brush.shape, v2i_to_v2f(m_pos));
}
