/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update_solid.c
*/

#include "prototypes.h"

void update_ice(map_t *map, int x, int y)
{
    if (vaporize(map, x, y, 100, steam))
        return;
    if (melt(map, x, y, 0, water))
        return;
    0;
}