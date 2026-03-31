/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "prototypes.h"

data_t create_gunpowder(void)
{
    data_t data;

    data.has_updated = false;
    data.id = gunpowder;
    data.density = 17.0;
    data.state = movable_solid;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 20;
    data.flammability = 1.0;
    data.pressure = 0;
    data.conductivity = 0.15;
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = smooth_color((sfColor){50, 50, 50, 255},
        (sfColor){80, 70, 40, 255}, random_number(0, 1000) / 1000.0);
    data.color = darken_color(data.color, random_number(85, 100) / 100.0);
    data.velocity = (sfVector2i){1, gravity};
    return data;
}
