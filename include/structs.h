/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** structs.h
*/

#include "defines.h"
#include "includes.h"

#ifndef SAND_STRUCTS
    #define SAND_STRUCTS

    typedef struct core_s core_t;
    typedef struct button_s button_t;

    typedef struct list_s {
        void *data;
        struct list_s *next;
        struct list_s *prev;
    } list_t;

    typedef struct matrix_s {
        int rows;
        int cols;
        float **data;
    } matrix_t;

    typedef enum materials_e {
        empty,
        sand,
        water,
        stone,
        black_hole,
        acid,
        clone,
        steam,
        lava,
        ice,
        NB_MATERIALS,
    } materials_e;

    typedef enum states_e {
        movable_solid,
        static_solid,
        liquid,
        gas,
    } states_e;

    typedef struct data_s {
        int id;
        float life_time;
        float life_counter;
        float density;
        float conductivity;
        float temperature;
        float mass;
        bool has_updated;
        short state;
        sfVector2i velocity;
        sfVector2i inertia;
        sfVector2u speed;
        sfColor color;
    } data_t;

    typedef struct voxel_s {
        data_t data;
        data_t stored_data;
        sfVector2u pos;
    } voxel_t;

    typedef struct map_s {
        sfVector2i dim;
        sfVector2f c_size;
        sfVector2u last_cell;
        sfVector2u current_cell;
        int nb_case;
        voxel_t **grid;
        sfVertex *buffer;
        sfVertexBuffer *v_buffer;
    } map_t;

    typedef struct ofrect_s {
        sfVector2f a;
        sfVector2f b;
        sfVector2f c;
        sfVector2f d;
    } ofrect;

    typedef struct switch_key_s {
        int index;
        bool prev_state;
        bool can_press;
        bool state;
        sfKeyCode keycode;
        void (*do_action)(core_t *, struct switch_key_s *);
        void (*update)(core_t *, struct switch_key_s *);
    } switch_key_t;

    typedef struct button_s {
        int index;
        bool visible;
        unsigned short scene;
        unsigned short state;
        sfRectangleShape *shape;
        sfTexture *texture;
        sfText *text;
        void (*on_click)(core_t *, button_t *);
        void (*update)(core_t *, button_t *);
    } button_t;

    typedef struct render_s {
        sfRenderWindow *window;
        sfRenderTexture *r_texture;
        sfRectangleShape *r_shape;
        sfVector2u r_size;
        sfVector2u w_size;
        sfView *view;
        bool fullscreen;
        unsigned short scene;
    } render_t;

    typedef struct vrect_s {
        sfTexture *texture;
        sfVector2f origin;
        sfVector2f pos;
        sfVector2f size;
        sfColor color;
        sfVertex vertex[4];
    } vrect_t;

    typedef struct clock_s {
        sfClock *clock;
        sfTime time;
        sfTime prev_time;
        float frame_delta;
        float elapsed_time;
        float seconds;
    } clock_st;

    typedef struct sounds_s {
    } sounds_t;

    typedef struct textures_s {
        sfTexture **button;
        sfTexture *r_texture;
    } textures_t;

    typedef struct find_files_s {
        DIR *d;
        int file;
        struct dirent *dir;
        char *content;
        int file_nb;
        char **found_files;
        int index;
    } find_files_t;

    typedef struct mouse_s {
        sfVector2i pos;
        sfVector2i lastpos;
        sfVector2i diff;
    } mouse_t;

    typedef struct ui_s {
        sfView *view;
        sfFont *font;
        sfText *fps_hint;
        sfText *voxel_info;
        button_t **button;
        bool mouse_released;
        unsigned short selected_level;
        sfRectangleShape *b1;
    } ui_t;

    typedef enum {
        fullscreen,
    } toggleable_keys;

    typedef struct keys_s {
        switch_key_t *toggleable;
    } keys_t;

    typedef struct events_s {
        sfEvent input;
        keys_t keys;
        bool paused;
    } events_t;

    typedef struct brush_s {
        sfCircleShape *shape;
        unsigned int radius;
        int id;
    } brush_t;

    struct core_s {
        render_t render;
        clock_st clock;
        events_t events;
        textures_t textures;
        mouse_t mouse;
        sounds_t sounds;
        brush_t brush;
        map_t map;
        ui_t ui;
    };
#endif /*SAND_STRUCTS*/
