/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create_solid.c
*/

#include "prototypes.h"

data_t create_stone(void)
{
    data_t data;

    data.has_updated = false;
    data.id = stone;
    data.density = 24.5;
    data.state = static_solid;
    data.color = darken_color(sfWhite, 0.8);
    data.temperature = 20;
    data.conductivity = 3.2;
    data.inertia = (sfVector2i){0, 0};
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.color = darken_color(data.color, random_number(80, 100) / 100.0);
    data.velocity = (sfVector2i){0, 0};
    return data;
}