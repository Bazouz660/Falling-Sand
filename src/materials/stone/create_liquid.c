/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create_liquid.c
*/

#include "prototypes.h"

data_t create_lava(void)
{
    data_t data;

    data.has_updated = false;
    data.id = lava;
    data.density = 31.1;
    data.state = liquid;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 3000;
    data.conductivity = 5.2;
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = smooth_color(sfRed, sfYellow, 0.8);
    data.color = darken_color(data.color, random_number(900, 1000) / 1000.0);
    data.velocity = (sfVector2i){3, gravity};
    return data;
}