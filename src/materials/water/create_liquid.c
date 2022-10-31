/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create_liquid.c
*/

#include "prototypes.h"

data_t create_water(void)
{
    data_t data;

    data.has_updated = false;
    data.id = water;
    data.density = 9.97;
    data.color = smooth_color(sfBlue, sfCyan, 0.3);
    data.color.a = 150;
    data.temperature = 20;
    data.flammability = 0;
    data.conductivity = 0.59;
    data.state = liquid;
    data.inertia = (sfVector2i){0, 0};
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = darken_color(data.color, random_number(90, 100) / 100.0);
    data.velocity = (sfVector2i){10, gravity};
    return data;
}