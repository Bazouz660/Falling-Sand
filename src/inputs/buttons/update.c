/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_buttons(core_t *c)
{
    for (int i = 0; c->ui.button[i] != NULL; i++) {
        if (c->ui.button[i]->scene == c->render.scene)
            c->ui.button[i]->update(c, c->ui.button[i]);
    }
}
