/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

short burn_things(map_t *map, int x, int y, data_t data)
{
    short burned_things = false;
    float tmp;

    if (is_in_grid(map, (sfVector2i){x, y + 1})) {
        if (map->grid[x][y + 1].data.id == water || map->grid[x][y + 1].data.id == steam) {
            tmp = map->grid[x][y + 1].data.temperature;
            if (random_number(-100, 80) / 100.0 > 0)
                map->grid[x][y].data = create_smoke();
            else
                map->grid[x][y].data = create_empty();
            map->grid[x][y].data.temperature = tmp;
            return -1;
        }
        burned_things != produce_fire(map, x, y + 1, &map->grid[x][y].data);
    }


    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (map->grid[x][y - 1].data.id == water || map->grid[x][y - 1].data.id == steam) {
            tmp = map->grid[x][y - 1].data.temperature;
            if (random_number(-100, 80) / 100.0 > 0)
                map->grid[x][y].data = create_smoke();
            else
                map->grid[x][y].data = create_empty();
            map->grid[x][y].data.temperature = tmp;
            return -1;
        }
        burned_things != produce_fire(map, x, y - 1, &map->grid[x][y].data);

    /*if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (map->grid[x + 1][y].data.id == water || map->grid[x + 1][y].data.id == steam) {
            tmp = map->grid[x + 1][y].data.temperature;
            if (random_number(-100, 80) / 100.0 > 0)
                map->grid[x][y].data = create_smoke();
            else
                map->grid[x][y].data = create_empty();
            map->grid[x][y].data.temperature = tmp;
            return -1;
        }
        burned_things != produce_fire(map, x + 1, y, &map->grid[x][y].data);
    return burned_things;*/

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (map->grid[x - 1][y].data.id == water || map->grid[x - 1][y].data.id == steam) {
            tmp = map->grid[x - 1][y].data.temperature;
            if (random_number(-100, 80) / 100.0 > 0)
                map->grid[x][y].data = create_smoke();
            else
                map->grid[x][y].data = create_empty();
            map->grid[x][y].data.temperature = tmp;
            return -1;
        }
        burned_things != produce_fire(map, x - 1, y, &map->grid[x][y].data);

    if (is_in_grid(map, (sfVector2i){x - 1, y + 1}))
        burned_things != produce_fire(map, x - 1, y + 1, &map->grid[x][y].data);

    if (is_in_grid(map, (sfVector2i){x + 1, y + 1}))
        burned_things != produce_fire(map, x + 1, y + 1, &map->grid[x][y].data);

    if (is_in_grid(map, (sfVector2i){x - 1, y - 1}))
        burned_things != produce_fire(map, x - 1, y - 1, &map->grid[x][y].data);

    if (is_in_grid(map, (sfVector2i){x + 1, y - 1}))
        burned_things != produce_fire(map, x + 1, y - 1, &map->grid[x][y].data);
    return burned_things;
}

void update_fire(clock_st clock, map_t *map, int x, int y)
{
    data_t data = map->grid[x][y].data;

    if (!update_voxel_life_time(clock, &map->grid[x][y].data)) {
        if (random_number(-100, 40) / 100.0 > 0) {
            map->grid[x][y].data = create_smoke();
            map->grid[x][y].data.temperature = data.temperature;
        }
        return;
    }

    if (burn_things(map, x, y, data) != 0)
        return;

    if (random_number(-100, 80) / 100.0 > 0) {
        move_gas(map, x, y);
        return;
    }
    if (random_number(-100, 20) / 100.0 > 0)
        move_liquid(map, x, y);
}