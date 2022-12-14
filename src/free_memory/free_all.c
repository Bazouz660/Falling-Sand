/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** free_all.c
*/

#include "structs.h"
#include "prototypes.h"

void free_all(core_t *c)
{
    sfClock_destroy(c->clock.clock);
    free_level(c);
    free_render(c);
    free_textures(c);
    free_ui(c);
}
