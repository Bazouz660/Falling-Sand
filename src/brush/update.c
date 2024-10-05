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
        case wood:
            data = create_wood();
            break;
        case fire:
            data = create_fire();
            break;
        case smoke:
            data = create_smoke();
            break;
        default:
            data = create_empty();
            break;
    }
    return data;
}

bool inside_circle(sfVector2i center, sfVector2i tile, float radius)
{
    float dx = center.x - tile.x;
    float dy = center.y - tile.y;
    float distance = sqrt(dx * dx + dy * dy);

    return distance <= radius;
}

void apply_brush_action(core_t *c, sfVector2i pos, int id, brush_mode mode)
{
    data_t *voxel = &c->map.grid[pos.x][pos.y].data;

    switch (mode) {
        case place:
            if (voxel->id == empty) {
                *voxel = create_data(id);
            }
            break;
        case destroy:
            if (voxel->id != empty) {
                destroy_voxel(voxel);
            }
            break;
        case replace:
            destroy_voxel(voxel);
            *voxel = create_data(id);
            break;
        case cool:
            if (voxel->id != empty) {
                voxel->temperature -= 10.0f; // Decrease temperature by 10 units
                // Clamp temperature to minimum value if necessary
                if (voxel->temperature < MIN_TEMPERATURE)
                    voxel->temperature = MIN_TEMPERATURE;
            }
            break;
        case heat:
            if (voxel->id != empty) {
                voxel->temperature += 10.0f; // Increase temperature by 10 units
                // Clamp temperature to maximum value if necessary
                if (voxel->temperature > MAX_TEMPERATURE)
                    voxel->temperature = MAX_TEMPERATURE;
            }
            break;
        default:
            break;
    }
}

void action_in_range(core_t *c, sfVector2i center, int radius, int id, brush_mode mode)
{
    radius = radius / 2;

    for (int y = -radius - 1; y <= radius; y++) {
        for (int x = -radius - 1; x <= radius; x++) {
            sfVector2i pos = {center.x + x, center.y + y};
            if (inside_circle(center, pos, radius)) {
                if (is_in_grid(&c->map, pos)) {
                    apply_brush_action(c, pos, id, mode);
                }
            }
        }
    }
}

void place_voxel(core_t *c)
{
    sfVector2i m_pos = get_mouse_grid(c);

    if (sfKeyboard_isKeyPressed(sfKeyLControl)) {
        c->brush.mode = cool;
    } else if (sfKeyboard_isKeyPressed(sfKeyLShift)) {
        c->brush.mode = heat;
    } else if (sfKeyboard_isKeyPressed(sfKeyLAlt)) {
        c->brush.mode = replace;
    } else {
        c->brush.mode = place;
    }

    if (m_pos.x >= 0 && m_pos.y >= 0) {
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            action_in_range(c, m_pos, c->brush.radius, c->brush.id, c->brush.mode);
        }
        if (sfMouse_isButtonPressed(sfMouseRight)) {
            // Right-click to remove voxels
            action_in_range(c, m_pos, c->brush.radius, 0, destroy);
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

    resize_brush(c);
    place_voxel(c);

    sfCircleShape_setRadius(c->brush.shape, c->brush.radius);
    sfCircleShape_setOrigin(c->brush.shape, get_circle_center(c->brush.shape));
    sfCircleShape_setPosition(c->brush.shape, v2i_to_v2f(m_pos));
}
