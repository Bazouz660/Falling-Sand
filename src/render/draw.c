/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** draw.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

void draw_grid(core_t *c)
{
    //for (int x = 0; x < c->map.dim.x; x++)
    //    for (int y = 0; y < c->map.dim.y; y++) {
    //        sfRenderWindow_drawRectangleShape(c->render.window,
    //        c->map.gridc[x][y]->shape, NULL);
    //    }

    sfVertexBuffer_update(c->map.v_buffer, c->map.buffer, c->map.nb_case, 0);

    sfRenderTexture_drawVertexBuffer(c->render.r_texture,
    c->map.v_buffer, NULL);
    //sfVertexArray_clear(array);
    sfRenderWindow_drawRectangleShape(c->render.window, c->render.r_shape, NULL);
}

void draw_brush(core_t *c)
{
    sfRenderWindow_drawCircleShape(c->render.window, c->brush.shape, NULL);
}

void draw_2d(core_t *c)
{
    //sfRenderWindow_setView(c->render.window, c->render.view);
    draw_grid(c);
    draw_brush(c);
}

void draw_background(core_t *c)
{
    sfRenderWindow_drawRectangleShape(c->render.window, c->ui.b1, NULL);
}

void draw_ui(core_t *c)
{
    //sfRenderWindow_setView(c->render.window, c->ui.view);
    sfRenderWindow_drawText(c->render.window, c->ui.fps_hint, NULL);
    sfRenderWindow_drawText(c->render.window, c->ui.voxel_info, NULL);
}

void draw_all(core_t *c)
{
    draw_2d(c);
    draw_ui(c);
}

void draw_buttons(core_t *c)
{
    for (int i = 0; c->ui.button[i] != NULL; i++) {
        if (c->ui.button[i]->scene == c->render.scene)
            sfRenderWindow_drawRectangleShape(c->render.window,
            c->ui.button[i]->shape, NULL);
    }
}

void draw_main_menu(core_t *c)
{
    draw_background(c);
    draw_buttons(c);
}
