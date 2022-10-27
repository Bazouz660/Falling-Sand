/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_water(map_t *map, int x, int y)
{
    if (vaporize(map, x, y, 100, steam))
        return;
    if (solidify(map, x, y, 0, ice))
        return;
    move_liquid(map, x, y);
}