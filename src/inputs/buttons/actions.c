/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** functions.c
*/

#include "structs.h"
#include "prototypes.h"

void on_click_play(core_t *c, button_t *button)
{
    c->render.scene = 1;
    sfRenderWindow_setMouseCursorVisible(c->render.window, false);
}

void on_click_exit(core_t *c, button_t *button)
{
    close_game(c);
}
