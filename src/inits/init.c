/*
** EPITECH PROJECT, 2022
** fiziks
** File description:
** init.c
*/

#include "inputs.h"
#include "structs.h"
#include "prototypes.h"


void init_fps_text(core_t *c)
{
    c->ui.font = sfFont_createFromFile("misc/font.ttf");
    c->ui.fps_hint = sfText_create();
    sfText_setFont(c->ui.fps_hint, c->ui.font);
    sfText_setColor(c->ui.fps_hint, sfWhite);
    sfText_setPosition(c->ui.fps_hint, (sfVector2f){c->render.w_size.x / 30.0,
    c->render.w_size.y / 25.0});
    sfText_setString(c->ui.fps_hint, NULL);
    sfText_setOutlineColor(c->ui.fps_hint, sfBlack);
    sfText_setOutlineThickness(c->ui.fps_hint, 1);
    sfText_setCharacterSize(c->ui.fps_hint, c->render.w_size.x / 40);
}

void init_view(core_t *c)
{
    sfVector2u w_size = sfRenderWindow_getSize(c->render.window);
    c->render.view = sfView_create();
    sfView_setSize(c->render.view, (sfVector2f){w_size.x,
    w_size.y});
    sfView_setCenter(c->render.view, sfView_getCenter(sfRenderWindow_getView(c->render.window)));
}

void init_textures(core_t *c)
{
    c->textures.button = malloc(sizeof(sfTexture *) * 3);
    c->textures.button[0] = new_texture("assets/buttons/play.png", NULL);
    c->textures.button[1] = new_texture("assets/buttons/exit.png", NULL);
    c->textures.button[2] = NULL;
}

void init_mouse(core_t *c)
{
    c->mouse.pos = get_mouse_pos_view(c);
    c->ui.mouse_released = true;
}

void init_buttons(core_t *c)
{
    c->ui.button = malloc(sizeof(button_t *) * 3);
    c->ui.button[0] = button_create(c->textures.button[0],
    (sfVector2f){200, 150}, (sfVector2f){960, 400});
    c->ui.button[1] = button_create(c->textures.button[1],
    (sfVector2f){200, 150}, (sfVector2f){960, 600});
    c->ui.button[2] = NULL;

    button_link_scene(c->ui.button[0], 0);
    button_link_scene(c->ui.button[1], 0);
    button_set_onclick(c->ui.button[0], &on_click_play);
    button_set_onclick(c->ui.button[1], &on_click_exit);
}

void init_background(core_t *c)
{
    c->ui.b1 = sfRectangleShape_create();

    sfRectangleShape_setSize(c->ui.b1, (sfVector2f){c->render.r_size.x,
    c->render.r_size.y});
    sfRectangleShape_setOrigin(c->ui.b1, get_rect_center(c->ui.b1));
    sfRectangleShape_setFillColor(c->ui.b1, sfBlack);
}

void init_ui_view(core_t *c)
{
    c->ui.view = sfView_copy(c->render.view);
}

void init_voxel_info(core_t *c)
{
    c->ui.voxel_info = sfText_copy(c->ui.fps_hint);

    sfText_setCharacterSize(c->ui.voxel_info, 20);
    sfText_setString(c->ui.voxel_info, "Empty");
    sfText_setPosition(c->ui.voxel_info, (sfVector2f){c->render.w_size.x * 0.95,
    c->render.w_size.y / 25.0});
    sfText_setOrigin(c->ui.voxel_info, get_text_center(c->ui.voxel_info));
}

void init_ui(core_t *c)
{
    init_fps_text(c);
    init_background(c);
    init_buttons(c);
    init_ui_view(c);
    init_voxel_info(c);
}

void init_keys(core_t *c)
{
    c->events.keys.toggleable = malloc(sizeof(switch_key_t) * (3));
    init_toggleable_key(&c->events.keys.toggleable[0], sfKeyF11,
    &toggle_fullscreen);
    init_toggleable_key(&c->events.keys.toggleable[1], sfKeySpace, &toggle_pause);
    c->events.keys.toggleable[2].index = -1;
}

void init_map(core_t *c)
{
    sfVector2i dim = {640, 360};
    sfVector2f pos = {0, 0};
    sfVector2f c_size = {5, 5};
    int index = 0;

    c->map.dim = dim;
    c->map.c_size = c_size;
    c->map.nb_case = dim.x * dim.y;
    c->map.current_cell = (sfVector2u){0, 0};
    c->map.last_cell = c->map.current_cell;
    c->map.v_buffer = sfVertexBuffer_create(c->map.nb_case, sfPoints, sfVertexBufferStream);
    c->map.grid = malloc(sizeof(voxel_t *) * (dim.x + 1));
    c->map.buffer = malloc(sizeof(sfVertex) * (c->map.nb_case + 1));
    for (int x = 0; x < c->map.dim.x; x++) {
        c->map.grid[x] = malloc(sizeof(voxel_t) * (dim.y + 1));
        for (int y = 0; y < c->map.dim.y; y++) {
            pos.y = y;
            c->map.grid[x][y].data = create_data(empty);
            destroy_voxel(&c->map.grid[x][y].stored_data);
            c->map.buffer[index].position = pos;
            c->map.buffer[index].color = c->map.grid[x][y].data.color;
            index++;
        }
        pos.x++;
    }
}

void init_render_texture(core_t *c)
{
    c->render.r_texture = sfRenderTexture_create(c->map.dim.x, c->map.dim.y,
    false);
    c->textures.r_texture = (sfTexture *)sfRenderTexture_getTexture(c->render.r_texture);
    c->render.r_shape = sfRectangleShape_create();
    sfRectangleShape_setSize(c->render.r_shape, v2u_to_v2f(c->render.w_size));
    sfRectangleShape_setOutlineColor(c->render.r_shape, sfWhite);
    sfRectangleShape_setOutlineThickness(c->render.r_shape, 0);
    sfRectangleShape_setOrigin(c->render.r_shape, get_rect_center(c->render.r_shape));
    sfRectangleShape_setPosition(c->render.r_shape, sfView_getCenter(c->render.view));
    sfRectangleShape_setTexture(c->render.r_shape, c->textures.r_texture, false);
    sfRectangleShape_setScale(c->render.r_shape, (sfVector2f){1, -1});
}

void init_brush(core_t *c)
{
    c->brush.radius = 1;
    c->brush.id = 1;
    c->brush.shape = sfCircleShape_create();
    sfCircleShape_setFillColor(c->brush.shape, sfTransparent);
    sfCircleShape_setOutlineThickness(c->brush.shape, 1);
    sfCircleShape_setOutlineColor(c->brush.shape, sfWhite);
    sfCircleShape_setRadius(c->brush.shape, c->brush.radius);
}

void init_game(core_t *c)
{
    c->render.r_size = (sfVector2u){380, 200};
    c->render.window = create_window("Backrooms", false);
    c->render.w_size = sfRenderWindow_getSize(c->render.window);
    sfRenderWindow_setPosition(c->render.window, (sfVector2i){0, 0});
    c->render.fullscreen = false;
    c->clock.clock = sfClock_create();
    c->mouse.lastpos = get_mouse_pos_view(c);
    c->mouse.diff = (sfVector2i){0, 0};
    c->render.scene = 0;
    c->clock.prev_time.microseconds = 0;
    c->clock.frame_delta = 0;
    c->events.paused = false;
    srand(time(NULL));
    init_textures(c);
    init_view(c);
    init_mouse(c);
    init_brush(c);
    init_keys(c);
    init_ui(c);
    init_map(c);
    init_render_texture(c);
}
