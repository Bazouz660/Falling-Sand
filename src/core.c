/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** core.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"
#include "defines.h"

void close_game(core_t *c)
{
    sfRenderWindow_close(c->render.window);
    free_all(c);
}

void analyse_events(core_t *c)
{
    int mouse_released = 0;

    while (sfRenderWindow_pollEvent(c->render.window, &c->events.input)) {
        update_toggleable_keys(c);
        resize_brush(c);
        if (c->events.input.type == sfEvtMouseButtonReleased)
            mouse_released += 1;
        if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
            c->render.scene = 0;
            sfRenderWindow_setMouseCursorVisible(c->render.window, true);
        }
        if (c->events.input.type == sfEvtClosed)
            close_game(c);
    }
    if (mouse_released > 0)
        c->ui.mouse_released = true;
    else
        c->ui.mouse_released = false;
}

void update_mouse(core_t *c)
{
    c->mouse.lastpos = c->mouse.pos;
    c->mouse.pos = get_mouse_pos_view(c);
    c->mouse.diff.x = c->mouse.pos.x - c->mouse.lastpos.x;
    c->mouse.diff.y = c->mouse.pos.y - c->mouse.lastpos.y;
}

void render_game(core_t *c)
{
    update_brush(c);
    update_grid(c);
    draw_all(c);
}

void update_buttons(core_t *c)
{
    for (int i = 0; c->ui.button[i] != NULL; i++) {
        if (c->ui.button[i]->scene == c->render.scene)
            c->ui.button[i]->update(c, c->ui.button[i]);
    }
}

void render_menu(core_t *c)
{
    draw_main_menu(c);
    update_buttons(c);
}

int game_loop(void)
{
    core_t *c = malloc(sizeof(core_t));

    init_game(c);
    //sfRenderWindow_setVerticalSyncEnabled(c->render.window, True);
    //sfRenderWindow_setFramerateLimit(c->render.window, 30);
    while (sfRenderWindow_isOpen(c->render.window)) {
        update_clock(c);
        update_fps(c);
        update_screen(c);
        update_mouse(c);
        if (c->render.scene == 0)
            render_menu(c);
        if (c->render.scene == 1)
            render_game(c);
        analyse_events(c);
    }
    sfRenderWindow_destroy(c->render.window);
    return 0;
}

int main(int ac, char **av)
{
    return game_loop();
}
