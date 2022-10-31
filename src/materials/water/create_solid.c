/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create_solid.c
*/

#include "prototypes.h"

data_t create_ice(void)
{
    data_t data;

    data.has_updated = false;
    data.id = ice;
    data.density = 0.917;
    data.state = static_solid;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = -50;
    data.flammability = 0;
    data.conductivity = 2.1;
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = darken_color(sfWhite, 0.9);
    data.color = darken_color(data.color, random_number(950, 1000) / 1000.0);
    data.velocity = (sfVector2i){0, 0};
    return data;
}