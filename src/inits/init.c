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
    c->textures.button = malloc(sizeof(sfTexture *) * (3 + NB_MATERIALS));
    c->textures.button[0] = new_texture("assets/buttons/play.png", NULL);
    c->textures.button[1] = new_texture("assets/buttons/exit.png", NULL);
    c->textures.button[2] = new_texture("assets/buttons/sand.png", NULL);
    c->textures.button[3] = new_texture("assets/buttons/water.png", NULL);
    c->textures.button[4] = new_texture("assets/buttons/stone.png", NULL);
    c->textures.button[5] = new_texture("assets/buttons/black_hole.png", NULL);
    c->textures.button[6] = new_texture("assets/buttons/acid.png", NULL);
    c->textures.button[7] = new_texture("assets/buttons/clone.png", NULL);
    c->textures.button[8] = new_texture("assets/buttons/steam.png", NULL);
    c->textures.button[9] = new_texture("assets/buttons/lava.png", NULL);
    c->textures.button[10] = new_texture("assets/buttons/ice.png", NULL);
    c->textures.button[11] = new_texture("assets/buttons/caustic_gas.png", NULL);
    c->textures.button[12] = new_texture("assets/buttons/wood.png", NULL);
    c->textures.button[13] = new_texture("assets/buttons/fire.png", NULL);
    c->textures.button[14] = new_texture("assets/buttons/smoke.png", NULL);
    c->textures.button[15] = NULL;

}

void init_mouse(core_t *c)
{
    c->mouse.pos = get_mouse_pos_view(c);
    c->ui.mouse_released = true;
}

void init_material_buttons(core_t *c)
{
    c->ui.button[2] = button_create(c->textures.button[2],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.10});
    c->ui.button[3] = button_create(c->textures.button[3],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.15});
    c->ui.button[4] = button_create(c->textures.button[4],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.20});
    c->ui.button[5] = button_create(c->textures.button[5],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.25});
    c->ui.button[6] = button_create(c->textures.button[6],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.30});
    c->ui.button[7] = button_create(c->textures.button[7],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.35});
    c->ui.button[8] = button_create(c->textures.button[8],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.40});
    c->ui.button[9] = button_create(c->textures.button[9],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.45});
    c->ui.button[10] = button_create(c->textures.button[10],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.50});
    c->ui.button[11] = button_create(c->textures.button[11],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.55});
    c->ui.button[12] = button_create(c->textures.button[12],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.60});
    c->ui.button[13] = button_create(c->textures.button[13],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.65});
    c->ui.button[14] = button_create(c->textures.button[14],
    (sfVector2f){32, 32}, (sfVector2f){c->render.w_size.x * 0.95, c->render.w_size.y * 0.70});


    for (int i = 2; i < NB_MATERIALS + 1; i++) {
        button_link_scene(c->ui.button[i], 1);
        button_set_onclick(c->ui.button[i], &on_click_set_brush_id);
    }
    c->ui.button[15] = NULL;
}

void init_buttons(core_t *c)
{
    c->ui.button = malloc(sizeof(button_t *) * (3 + NB_MATERIALS));
    c->ui.button[0] = button_create(c->textures.button[0],
    (sfVector2f){350, 150}, (sfVector2f){c->render.w_size.x / 2.0, c->render.w_size.y * 0.4});
    c->ui.button[1] = button_create(c->textures.button[1],
    (sfVector2f){350, 150}, (sfVector2f){c->render.w_size.x / 2.0, c->render.w_size.y * 0.6});

    button_link_scene(c->ui.button[0], 0);
    button_link_scene(c->ui.button[1], 0);
    button_set_onclick(c->ui.button[0], &on_click_play);
    button_set_onclick(c->ui.button[1], &on_click_exit);

    init_material_buttons(c);
}

void init_background(core_t *c)
{
    c->ui.background = sfRectangleShape_create();

    sfRectangleShape_setSize(c->ui.background, (sfVector2f){c->render.w_size.x,
    c->render.w_size.y});
    sfRectangleShape_setOrigin(c->ui.background, get_rect_center(c->ui.background));
    sfRectangleShape_setFillColor(c->ui.background, darken_color(sfWhite, 0.2));
    sfRectangleShape_setPosition(c->ui.background, sfView_getCenter(c->ui.view));
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
    sfText_setPosition(c->ui.voxel_info, (sfVector2f){c->render.w_size.x * 0.92,
    c->render.w_size.y / 25.0});
    sfText_setOrigin(c->ui.voxel_info, get_text_center(c->ui.voxel_info));
}

void init_ui(core_t *c)
{
    init_fps_text(c);
    init_ui_view(c);
    init_background(c);
    init_buttons(c);
    init_voxel_info(c);
}

void init_keys(core_t *c)
{
    unsigned int toggleable_keys_count = 2;
    c->events.keys.toggleable = malloc(sizeof(switch_key_t) * (toggleable_keys_count + 1));
    c->events.keys.toggleable[toggleable_keys_count + 1].index = -1;

    init_toggleable_key(&c->events.keys.toggleable[0], sfKeyF11, &toggle_fullscreen);
    init_toggleable_key(&c->events.keys.toggleable[1], sfKeySpace, &toggle_pause);
    init_toggleable_key(&c->events.keys.toggleable[2], sfKeyT, &toggle_temperature_mode);
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
    sfRectangleShape_setSize(c->render.r_shape, (sfVector2f){c->render.w_size.x * 0.9, c->render.w_size.y});
    sfRectangleShape_setOutlineColor(c->render.r_shape, darken_color(sfWhite, 0.5));
    sfRectangleShape_setOutlineThickness(c->render.r_shape, 0);
    sfRectangleShape_setOrigin(c->render.r_shape, (sfVector2f){0, get_rect_center(c->render.r_shape).y});
    sfRectangleShape_setPosition(c->render.r_shape, (sfVector2f){0, sfView_getCenter(c->render.view).y});
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
    c->render.temperature_mode = false;
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
