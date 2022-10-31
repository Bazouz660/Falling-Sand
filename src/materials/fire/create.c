/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "prototypes.h"

data_t create_fire(void)
{
    data_t data;

    data.has_updated = false;
    data.id = fire;
    data.density = 0.3;
    data.state = gas;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 1200;
    data.flammability = 0;
    data.conductivity = 1.0;
    data.life_time = 5.0;
    data.life_counter = 0;
    data.color = smooth_color(sfRed, sfYellow, random_number(200, 1000) / 1000.0);
    data.color.a = 200;
    data.color = darken_color(data.color, random_number(750, 1000) / 1000.0);
    data.velocity = (sfVector2i){2, gravity / 3};
    return data;
}