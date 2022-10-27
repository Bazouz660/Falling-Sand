/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

static void update_voxel(core_t *c, map_t *map, int x, int y)
{
    if (map->grid[x][y].data.id == 0 || map->grid[x][y].data.has_updated == true)
        return;
    if (map->grid[x][y].data.id == 1)
        update_sand(map, x, y);
    if (map->grid[x][y].data.id == 2)
        update_water(map, x, y);
    if (map->grid[x][y].data.id == 3)
        update_stone(map, x, y);
    if (map->grid[x][y].data.id == 4)
        update_black_hole(map, x, y);
    if (map->grid[x][y].data.id == 5)
        update_acid(map, x, y);
    if (map->grid[x][y].data.id == 6)
        update_clone(map, x, y);
    if (map->grid[x][y].data.id == 7)
        update_steam(c->clock, map, x, y);
    if (map->grid[x][y].data.id == 8)
        update_lava(c->clock, map, x, y);
    if (map->grid[x][y].data.id == 9)
        update_ice(map, x, y);
    update_heat(map, x, y);
}

void update_grid(core_t *c)
{
    int index = 0;
    static int frame_counter = 0;
    bool ran = (frame_counter % 2 == 0 ? 0: 1);
    bool ran2 = 1;

    if (!c->events.paused) {

        if (ran2) {
            for (int y = 0; y < c->map.dim.y; y++) {
                if (ran) {
                    for (int x = c->map.dim.x - 1; x >= 0 ; x--)
                        update_voxel(c, &c->map, x, y);
                } else {
                    for (int x = 0; x < c->map.dim.x; x++)
                        update_voxel(c, &c->map, x, y);
                }
            }
        } else {
            for (int y = c->map.dim.y - 1; y >= 0; y--) {
                if (ran) {
                    for (int x = c->map.dim.x - 1; x >= 0 ; x--)
                        update_voxel(c, &c->map, x, y);
                } else {
                    for (int x = 0; x < c->map.dim.x; x++)
                        update_voxel(c, &c->map, x, y);
                }
            }
        }
    }
    for (int x = 0; x < c->map.dim.x; x++) {
        for (int y = 0; y < c->map.dim.y; y++) {
            c->map.grid[x][y].data.has_updated = false;
            if (c->map.grid[x][y].data.id == 0)
                c->map.grid[x][y].data.color = sfBlack;
            c->map.buffer[index].color = c->map.grid[x][y].data.color;
            c->map.buffer[index].position.x = x;
            c->map.buffer[index].position.y = y;
            index++;
        }
    }
    frame_counter++;
}
