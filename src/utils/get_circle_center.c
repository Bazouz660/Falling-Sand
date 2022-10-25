/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** get_circle_center.c
*/

#include "includes.h"

sfVector2f get_circle_center(sfCircleShape *circle)
{
    sfFloatRect bound = sfCircleShape_getGlobalBounds(circle);
    sfVector2f center;

    center.x = bound.width / 2.0;
    center.y = bound.height / 2.0;
    return center;
}
