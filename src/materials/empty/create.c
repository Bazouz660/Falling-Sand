/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** create.c
*/

#include "structs.h"

data_t create_empty(void)
{
    data_t data;

    data.has_updated = false;
    data.id = empty;
    data.density = 0;
    data.color = sfBlack;
    data.temperature = 20;
    data.flammability = 0;
    data.conductivity = 0.026;
    data.state = -1;
    data.inertia = (sfVector2i){0, 0};
    data.life_time = INFINITY;
    data.life_counter = 0;
    data.velocity = (sfVector2i){1, gravity};
    return data;
}