/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "prototypes.h"

data_t create_acid(void)
{
    data_t data;

    data.has_updated = false;
    data.id = acid;
    data.density = 1.05;
    data.state = liquid;
    data.color = sfGreen;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 20;
    data.conductivity = 0.2;
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = darken_color(data.color, random_number(95, 100) / 100.0);
    data.velocity = (sfVector2i){8, gravity};
    return data;
}