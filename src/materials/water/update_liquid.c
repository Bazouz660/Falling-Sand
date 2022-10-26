/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_water(map_t *map, int x, int y, data_t *data)
{
    move_liquid(map, x, y, data);
}