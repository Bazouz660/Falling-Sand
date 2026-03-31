/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

static void update_voxel(core_t *c, map_t *map, int x, int y)
{
    int id = GRID(map, x, y).data.id;
    if (id == empty || GRID(map, x, y).data.has_updated == true)
        return;
    switch (id) {
        case sand:        update_sand(map, x, y); break;
        case water:       update_water(map, x, y); break;
        case stone:       update_stone(map, x, y); break;
        case black_hole:  update_black_hole(map, x, y); break;
        case acid:        update_acid(map, x, y); break;
        case clone:       update_clone(map, x, y); break;
        case steam:       update_steam(c->clock, map, x, y); break;
        case lava:        update_lava(c->clock, map, x, y); break;
        case ice:         update_ice(map, x, y); break;
        case caustic_gas: update_caustic_gas(c->clock, map, x, y); break;
        case wood:        update_wood(map, x, y); break;
        case fire:        update_fire(c->clock, map, x, y); break;
        case smoke:       update_smoke(c->clock, map, x, y); break;
        default: break;
    }
    update_heat(map, x, y);
}

void update_grid(core_t *c)
{
    int index = 0;
    static int frame_counter = 0;
    bool ran = (frame_counter % 2 == 0 ? 0: 1);

    if (!c->events.paused) {
        for (int y = 0; y < c->map.dim.y; y++) {
            if (ran) {
                for (int x = c->map.dim.x - 1; x >= 0 ; x--)
                    update_voxel(c, &c->map, x, y);
            } else {
                for (int x = 0; x < c->map.dim.x; x++)
                    update_voxel(c, &c->map, x, y);
            }
        }
    }
    for (int y = 0; y < c->map.dim.y; y++) {
        for (int x = 0; x < c->map.dim.x; x++) {
            GRID(&c->map, x, y).data.has_updated = false;
            if (GRID(&c->map, x, y).data.id == 0)
                GRID(&c->map, x, y).data.color = sfBlack;
            c->map.buffer[index].color = GRID(&c->map, x, y).data.color;
            index++;
        }
    }
    frame_counter++;
}
