/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** free_render.c
*/

#include "prototypes.h"

void free_render(core_t *c)
{
    sfText_destroy(c->render.fps_hint);
    sfView_destroy(c->render.view);
}
