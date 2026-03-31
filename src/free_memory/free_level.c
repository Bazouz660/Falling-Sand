/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** free_level.c
*/

#include "prototypes.h"

void free_level(core_t *c)
{
    free(c->map.grid);
    free(c->map.pmap);
    free(c->map.vx);
    free(c->map.vy);
    sfVertexBuffer_destroy(c->map.v_buffer);
}
