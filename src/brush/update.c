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

    switch (id) {
        case empty:
            data = create_empty();
            break;
        case sand:
            data = create_sand();
            break;
        case water:
            data = create_water();
            break;
        case stone:
            data = create_stone();
            break;
        case lava:
            data = create_lava();
            break;
        case ice:
            data = create_ice();
            break;
        case steam:
            data = create_steam();
            break;
        case acid:
            data = create_acid();
            break;
        case black_hole:
            data = create_black_hole();
            break;
        case clone:
            data = create_clone();
            break;
        case caustic_gas:
            data = create_caustic_gas();
            break;
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

void update_brush(core_t *c)
{
    sfVector2i m_pos = get_mouse_pos_view(c);
    sfVector2u w_size = c->render.w_size;
    sfVector2f ratio = {(float)w_size.x / (float)c->map.dim.x,
    (float)w_size.y / (float)c->map.dim.y};

    if (!sfRenderWindow_hasFocus(c->render.window))
        return;
    place_voxel(c);
    sfCircleShape_setRadius(c->brush.shape, c->brush.radius);
    sfCircleShape_setOrigin(c->brush.shape, get_circle_center(c->brush.shape));
    sfCircleShape_setPosition(c->brush.shape, v2i_to_v2f(m_pos));
}
