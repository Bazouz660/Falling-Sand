/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "prototypes.h"

data_t create_black_hole(void)
{
    data_t data;

    data.has_updated = false;
    data.id = black_hole;
    data.state = static_solid;
    data.density = 1000000;
    data.color = darken_color(sfRed, 0.3);
    data.temperature = 20;
    data.conductivity = 0;
    data.inertia = (sfVector2i){0, 0};
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = darken_color(data.color, random_number(80, 100) / 100.0);
    data.velocity = (sfVector2i){0, 0};
    return data;
}