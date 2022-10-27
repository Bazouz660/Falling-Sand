/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create_gas.c
*/

#include "prototypes.h"

data_t create_caustic_gas(void)
{
    data_t data;

    data.has_updated = false;
    data.id = caustic_gas;
    data.density = 0.4;
    data.state = gas;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 80;
    data.conductivity = 0.35;
    data.life_time = 20.0;
    data.life_counter = 0;
    data.color = smooth_color(sfWhite, sfGreen, 0.6);
    data.color.a = 100;
    data.color = darken_color(data.color, random_number(950, 1000) / 1000.0);
    data.velocity = (sfVector2i){5, gravity / 2};
    return data;
}