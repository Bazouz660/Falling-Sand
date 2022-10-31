/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "prototypes.h"

data_t create_smoke(void)
{
    data_t data;

    data.has_updated = false;
    data.id = smoke;
    data.density = 1.87;
    data.state = gas;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 300;
    data.flammability = 0;
    data.conductivity = 0.016;
    data.life_time = 2.0;
    data.life_counter = 0;
    data.color = darken_color(sfWhite, 0.3);
    data.color.a = 200;
    data.color = darken_color(data.color, random_number(900, 1000) / 1000.0);
    data.velocity = (sfVector2i){3, gravity / 3};
    return data;
}