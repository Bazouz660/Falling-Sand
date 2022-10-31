/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** state_change.c
*/

#include "prototypes.h"

bool condensate(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature < threshold
        && map->grid[x][y].data.temperature > 0) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool vaporize(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature >= threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool solidify(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature < threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool melt(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature > threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool sublimate(map_t *map, int x, int y, float threshold, int id)
{
    data_t tmp = map->grid[x][y].data;

    if (map->grid[x][y].data.temperature > threshold) {
        map->grid[x][y].data = create_data(id);
        map->grid[x][y].data.temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool set_fire(data_t *data)
{
    data_t tmp = *data;

    if (random_number(-100, data->flammability * 3) / 100.0 > 0) {
        *data = create_data(fire);
        data->temperature = tmp.temperature;
        return true;
    }
    return false;
}

bool produce_fire(map_t *map, int x, int y, data_t *data)
{
    data_t tmp = *data;
    bool produced_fire = false;

    //if (map->grid[x][y].data.id == empty)
    //    return false;

    if (is_in_grid(map, (sfVector2i){x, y + 1}))
        if (random_number(-100, map->grid[x][y + 1].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x][y + 1].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }

    if (is_in_grid(map, (sfVector2i){x, y - 1}))
        if (random_number(-100, map->grid[x][y - 1].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x][y - 1].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }

    if (is_in_grid(map, (sfVector2i){x + 1, y}))
        if (random_number(-100, map->grid[x + 1][y].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x + 1][y].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }

    if (is_in_grid(map, (sfVector2i){x - 1, y}))
        if (random_number(-100, map->grid[x - 1][y].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x - 1][y].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }

    /*if (is_in_grid(map, (sfVector2i){x - 1, y + 1}))
        if (random_number(-100, map->grid[x - 1][y + 1].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x - 1][y + 1].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }

    if (is_in_grid(map, (sfVector2i){x + 1, y + 1}))
        if (random_number(-100, map->grid[x + 1][y + 1].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x + 1][y + 1].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }

    if (is_in_grid(map, (sfVector2i){x - 1, y - 1}))
        if (random_number(-100, map->grid[x - 1][y - 1].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x - 1][y - 1].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }

    if (is_in_grid(map, (sfVector2i){x + 1, y - 1}))
        if (random_number(-100, map->grid[x + 1][y - 1].data.flammability * 40) > 0)
            if (set_fire(&map->grid[x + 1][y - 1].data)) {
                if (random_number(-100, 20) / 100.0 > 0)
                    map->grid[x][y].data = create_data(fire);
                return true;
            }*/

    return produced_fire;
}

bool burn(data_t *data, float threshold)
{
    data_t tmp = *data;

    if (data->temperature > threshold && random_number(-100, data->flammability * 100) > 0) {
        *data = create_data(fire);
        data->temperature = tmp.temperature;
        return true;
    }
    return false;
}