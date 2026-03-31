/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** draw.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"
#include <stdint.h>
#include <math.h>

// Helper function to convert HSV to RGB
void HSVtoRGB(float h, float s, float v, int *r, int *g, int *b)
{
    float c = v * s; // Chroma
    float x = c * (1 - fabs(fmodf(h / 60.0f, 2) - 1));
    float m = v - c;
    float r1, g1, b1;

    if (h >= 0 && h < 60) {
        r1 = c, g1 = x, b1 = 0;
    } else if (h >= 60 && h < 120) {
        r1 = x, g1 = c, b1 = 0;
    } else if (h >= 120 && h < 180) {
        r1 = 0, g1 = c, b1 = x;
    } else if (h >= 180 && h < 240) {
        r1 = 0, g1 = x, b1 = c;
    } else if (h >= 240 && h < 300) {
        r1 = x, g1 = 0, b1 = c;
    } else {
        r1 = c, g1 = 0, b1 = x;
    }

    *r = (int)((r1 + m) * 255);
    *g = (int)((g1 + m) * 255);
    *b = (int)((b1 + m) * 255);
}

// Main function to draw the temperature mode
void draw_temperature_mode(core_t *c)
{
    float min_temp = MIN_TEMPERATURE;
    float mid_temp = MIN_TEMPERATURE + (MAX_TEMPERATURE - MIN_TEMPERATURE) / 2;
    float max_temp = MAX_TEMPERATURE;

    for (int y = 0; y < c->map.dim.y; y++) {
        for (int x = 0; x < c->map.dim.x; x++) {
            int index = y * c->map.dim.x + x;

            if (GRID(&c->map, x, y).data.id != empty) {
                float temp = GRID(&c->map, x, y).data.temperature;

                int r, g, b;
                if (temp <= mid_temp) {
                    float temp_normalized = (temp - min_temp) / (mid_temp - min_temp);
                    if (temp_normalized < 0) temp_normalized = 0;
                    if (temp_normalized > 1) temp_normalized = 1;
                    float hue = (1 - temp_normalized) * 240.0f;
                    HSVtoRGB(hue, 1.0f, 1.0f, &r, &g, &b);
                } else {
                    float temp_normalized = (temp - mid_temp) / (max_temp - mid_temp);
                    if (temp_normalized < 0) temp_normalized = 0;
                    if (temp_normalized > 1) temp_normalized = 1;
                    float saturation = 1.0f - temp_normalized;
                    HSVtoRGB(0.0f, saturation, 1.0f, &r, &g, &b);
                }

                c->map.buffer[index].color.r = r;
                c->map.buffer[index].color.g = g;
                c->map.buffer[index].color.b = b;
                c->map.buffer[index].color.a = 255;
            }
        }
    }
}

static float sample_pressure_bilinear(map_t *map, int px, int py)
{
    float fx = ((float)px / AIR_CELL) - 0.5f;
    float fy = ((float)py / AIR_CELL) - 0.5f;
    int ax = (int)fx;
    int ay = (int)fy;
    float tx = fx - ax;
    float ty = fy - ay;

    if (ax < 0) { ax = 0; tx = 0; }
    if (ay < 0) { ay = 0; ty = 0; }
    if (ax >= map->air_dim.x - 1) { ax = map->air_dim.x - 2; tx = 1.0f; }
    if (ay >= map->air_dim.y - 1) { ay = map->air_dim.y - 2; ty = 1.0f; }

    float p00 = PMAP(map, ax, ay);
    float p10 = PMAP(map, ax + 1, ay);
    float p01 = PMAP(map, ax, ay + 1);
    float p11 = PMAP(map, ax + 1, ay + 1);

    float top = p00 * (1.0f - tx) + p10 * tx;
    float bot = p01 * (1.0f - tx) + p11 * tx;
    return top * (1.0f - ty) + bot * ty;
}

void draw_pressure_mode(core_t *c)
{
    for (int y = 0; y < c->map.dim.y; y++) {
        for (int x = 0; x < c->map.dim.x; x++) {
            int index = y * c->map.dim.x + x;
            float p = sample_pressure_bilinear(&c->map, x, y);

            float sign = p >= 0 ? 1.0f : -1.0f;
            float ap = p >= 0 ? p : -p;
            float norm = ap / (ap + 60.0f);
            if (norm > 1.0f) norm = 1.0f;
            norm *= sign;

            int r, g, b;
            if (norm >= 0) {
                r = 128 + (int)(norm * 127);
                g = 128 - (int)(norm * 128);
                b = 128 - (int)(norm * 128);
            } else {
                float an = -norm;
                r = 128 - (int)(an * 128);
                g = 128 - (int)(an * 128);
                b = 128 + (int)(an * 127);
            }
            c->map.buffer[index].color.r = r;
            c->map.buffer[index].color.g = g;
            c->map.buffer[index].color.b = b;
            c->map.buffer[index].color.a = 255;
        }
    }
}

void draw_grid(core_t *c)
{
    if (c->render.temperature_mode)
        draw_temperature_mode(c);
    if (c->render.pressure_mode)
        draw_pressure_mode(c);

    sfVertexBuffer_update(c->map.v_buffer, c->map.buffer, c->map.nb_case, 0);

    sfRenderTexture_drawVertexBuffer(c->render.r_texture, c->map.v_buffer, NULL);

    sfRenderWindow_drawRectangleShape(c->render.window, c->render.r_shape, NULL);
}

void draw_brush(core_t *c)
{
    sfRenderWindow_drawCircleShape(c->render.window, c->brush.shape, NULL);
}

void draw_background(core_t *c)
{
    sfRenderWindow_drawRectangleShape(c->render.window, c->ui.background, NULL);
}

void draw_2d(core_t *c)
{
    //sfRenderWindow_setView(c->render.window, c->render.view);
    draw_background(c);
    draw_grid(c);
    draw_brush(c);
}

void draw_buttons(core_t *c)
{
    for (int i = 0; c->ui.button[i] != NULL; i++) {
        if (c->ui.button[i]->scene == c->render.scene)
            sfRenderWindow_drawRectangleShape(c->render.window,
            c->ui.button[i]->shape, NULL);
    }
}

void draw_ui(core_t *c)
{
    //sfRenderWindow_setView(c->render.window, c->ui.view);
    sfRenderWindow_drawText(c->render.window, c->ui.fps_hint, NULL);
    sfRenderWindow_drawText(c->render.window, c->ui.voxel_info, NULL);
    draw_buttons(c);
}

void draw_all(core_t *c)
{
    draw_2d(c);
    draw_ui(c);
}

void draw_main_menu(core_t *c)
{
    draw_background(c);
    draw_buttons(c);
}
