/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "prototypes.h"

data_t create_sand(void)
{
    data_t data;

    data.has_updated = false;
    data.id = sand;
    data.density = 18.5;
    data.color = sfYellow;
    data.temperature = 20;
    data.conductivity = 0.2;
    data.state = movable_solid;
    data.inertia = (sfVector2i){0, 0};
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = darken_color(data.color, random_number(70, 100) / 100.0);
    data.velocity = (sfVector2i){1, gravity};
    return data;
}