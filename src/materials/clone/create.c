/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "prototypes.h"

data_t create_clone(void)
{
    data_t data;

    data.has_updated = false;
    data.id = clone;
    data.density = 300.0;
    data.state = static_solid;
    data.color = sfYellow;
    data.inertia = (sfVector2i){0, 0};
    data.temperature = 20;
    data.conductivity = 5;
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.velocity = (sfVector2i){0, 0};
    return data;
}