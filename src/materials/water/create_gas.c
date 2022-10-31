/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create_gas.c
*/

#include "prototypes.h"

data_t create_steam(void)
{
    data_t data;

    data.has_updated = false;
    data.id = steam;
    data.density = 0.6;
    data.state = gas;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 120;
    data.flammability = 0;
    data.conductivity = 0.184;
    data.life_time = 10.0;
    data.life_counter = 0;
    data.color = smooth_color(sfWhite, sfCyan, 0.6);
    data.color.a = 100;
    data.color = darken_color(data.color, random_number(950, 1000) / 1000.0);
    data.velocity = (sfVector2i){5, gravity / 2};
    return data;
}