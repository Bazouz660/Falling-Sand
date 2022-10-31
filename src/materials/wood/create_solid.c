/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create_solid.c
*/

#include "prototypes.h"

data_t create_wood(void)
{
    data_t data;

    data.has_updated = false;
    data.id = wood;
    data.density = 1.5;
    data.state = static_solid;
    data.color = (sfColor){133, 94, 66, 255};
    data.temperature = 20;
    data.flammability = 0.4;
    data.conductivity = 0.15;
    data.inertia = (sfVector2i){0, 0};
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = darken_color(data.color, random_number(90, 100) / 100.0);
    data.velocity = (sfVector2i){0, 0};
    return data;
}