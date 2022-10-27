/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_sand(map_t *map, int x, int y)
{
    
    move_movable_solid(map, x, y);
}
