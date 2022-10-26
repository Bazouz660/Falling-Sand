/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** prototypes.h
*/

#include "includes.h"
#include "structs.h"
#include "defines.h"

#ifndef SAND_PROTOTYPES
    #define SAND_PROTOTYPES

    // Utils
    sfRenderWindow *create_window(char const *title, bool fullscreen);
    sfSprite *new_sprite(char *texture_name, float x, float y);
    sfSound *new_sound(sfSound *new_sound, const char *buffer_location);
    void init_animated_sprite(sfSprite *sprite, int columns, int rows);
    sfSprite *setSprite_pos(sfSprite *sprite, float posX, float posY);
    sfVector2f get_sprite_center(sfSprite *sprite);
    float random_float(float scale);
    int random_number(int min_num, int max_num);
    sfVertex add_vertex_circular(float radius,
    float i, sfVector2f center);
    int positive(int nb);
    sfVector2f get_rect_center(sfRectangleShape *rect);
    sfFloatRect init_frect(float left, float top, float width, float height);
    int rand_range(int lower, int upper);
    sfVector2f init_vector2f(float x, float y);
    sfIntRect init_irect(int left, int top, int width, int height);
    char *my_int_to_str(int nb);
    double get_angle(sfVector2f origin, sfVector2f direction);
    double rad_to_deg(double angle);
    double deg_to_rad(double angle);
    void modulate_sound(sfSound *sound);
    int get_inv_angle(double angle);
    sfColor random_color(void);
    float get_min(float a, float b);
    float get_max(float a, float b);
    ofrect rect_get_oriented_bounds(sfRectangleShape *obj);
    void rotate_point(sfVector2f center, float angle, sfVector2f *p);
    double absolute(double x);
    int get_arr_len(void const **arr);
    int my_strlen(char const *str);
    char *my_strdup(char const *src);
    sfColor smooth_color(sfColor c1, sfColor c2, double prog);
    sfColor darken_color(sfColor c1, double prog);
    char *my_strcpy(char *dest, char const *src);
    char *my_strcat(char *dest, char const *src);
    int my_strcmp(char const *s1, char const *s2);
    char **strwar(const char *str, const char *separators);
    char *rm_str_char(char **str, char *to_remove);
    char *str_keep_char(char **str, char *to_keep);
    int my_getnbr(char const *str);
    sfVector2i get_mouse_pos_view(core_t *c);
    sfBool get_mouse_intersect_view(core_t *c, sfFloatRect to_check);
    sfVector2f get_text_center(sfText *text);
    double clamp(double min, double max, double n);
    int get_inv_angle(double angle);
    void close_game(core_t *c);
    double norm_deg(double *value, const double start, const double end);
    int my_list_size(list_t const *begin);
    float lerp(float a, float b, float t);
    sfVector2f lerp2f(sfVector2f a, sfVector2f b, float t);
    sfVector2f get_circle_center(sfCircleShape *circle);

    // Inits
    void init_game(core_t *c);

    // Fps
    float get_fps(sfClock *clock, sfTime *prev_time);
    float time_as_sec(sfTime time);

    // Screen Update
    void update_clock(core_t *c);
    void update_fps(core_t *c);
    void update_screen(core_t *c);

    // Vectors
    sfVector2f vect_add(sfVector2f v1, sfVector2f v2);
    sfVector2f vect_sub(sfVector2f v1, sfVector2f v2);
    float vect_mag(sfVector2f v);
    sfVector2f vect_mult(sfVector2f v, float n);
    sfVector2f vect_unit(sfVector2f v);
    sfVector2f vect_norm(sfVector2f v);
    float vect_dot(sfVector2f v1, sfVector2f v2);
    float vect_cross(sfVector2f v1, sfVector2f v2);
    float dist_from(sfVector2f p1, sfVector2f p2);
    sfVector2f closest_point_seg(sfVector2f a, sfVector2f b, sfVector2f p);
    sfVector2f v2u_to_v2f(sfVector2u vector);
    sfVector2u v2f_to_v2u(sfVector2f vector);
    sfVector2i v2f_to_v2i(sfVector2f vector);
    sfVector2f v2i_to_v2f(sfVector2i vector);

    // Matrix
    matrix_t new_matrix(int rows, int cols);
    matrix_t new_rot_matrix(float angle);
    sfVector2f multiply_vec(matrix_t *mx, sfVector2f vec);
    void free_matrix(matrix_t *matrix);

    // Render
    void draw_all(core_t *c);

    // vrect
    vrect_t *vrect_create(void);
    void vrect_draw(sfRenderWindow *render_window, sfRenderTexture *render_texture, vrect_t *vrect);
    void vrect_settexture(vrect_t *vrect, sfTexture *texture);
    void vrect_setposition(vrect_t *vrect, sfVector2f position);
    void vrect_setsize(vrect_t *vrect, sfVector2f size);
    void vrect_setcolor(vrect_t *vrect, sfColor color, unsigned int side,
    bool all_sides);

    // Buttons
    button_t *button_create(sfTexture *texture, sfVector2f size, sfVector2f pos);
    void button_set_onclick(button_t *button, void(*func)(core_t *, button_t *));
    void button_link_scene(button_t *button, unsigned short scene);
    void button_destroy(button_t *button);

    // UI
    void draw_main_menu(core_t *c);
    void draw_select_menu(core_t *c);

    // Rendering

    // Memory cleanup
    void free_all(core_t *c);
    void free_level(core_t *c);
    void free_render(core_t *c);
    void free_textures(core_t *c);
    void free_ui(core_t *c);

    // Input
    void init_toggleable_key(switch_key_t *key, sfKeyCode keycode,
    void(*action)(core_t *, switch_key_t *));
    void update_toggleable_keys(core_t *c);

    // Grid
    bool is_in_grid(map_t *map, sfVector2i pos);
    void swap_voxel(data_t *a, data_t *b);
    sfVector2i get_mouse_grid(core_t *c);
    void update_grid(core_t *c);
    void destroy_voxel(data_t *a);
    void copy_voxel(data_t *dest, data_t *src);
    bool update_voxel_life_time(clock_st clock, data_t *data);

    // Materials
    void update_sand(map_t *map, int x, int y);
    void update_water(map_t *map, int x, int y, data_t *data);
    void update_black_hole(map_t *map, int x, int y);
    void update_stone(map_t *map, int x, int y);
    void update_acid(map_t *map, int x, int y, data_t *data);
    void update_clone(map_t *map, int x, int y);
    void update_steam(clock_st clock, map_t *map, int x, int y);

    // States
    void move_gas(map_t *map, int x, int y, data_t data);
    void move_liquid(map_t *map, int x, int y, data_t *data);
    void move_movable_solid(map_t *map, int x, int y);

    // Brush
    void update_brush(core_t *c);
    void resize_brush(core_t *c);
    void place_voxel(core_t *c);

#endif /*SAND_PROTOTYPES*/
