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
    int index = 0;
    float min_temp = MIN_TEMPERATURE; // Absolute zero
    float mid_temp = MIN_TEMPERATURE + (MAX_TEMPERATURE - MIN_TEMPERATURE) / 2; // Mid temperature
    float max_temp = MAX_TEMPERATURE; // Maximum temperature

    for (int x = 0; x < c->map.dim.x; x++) {
        for (int y = 0; y < c->map.dim.y; y++) {
            if (c->map.grid[x][y].data.id != empty) {
                float temp = c->map.grid[x][y].data.temperature;

                int r, g, b;
                if (temp <= mid_temp) {
                    // Temperatures from min_temp to mid_temp: Blue to Red
                    float temp_normalized = (temp - min_temp) / (mid_temp - min_temp);
                    if (temp_normalized < 0) temp_normalized = 0;
                    if (temp_normalized > 1) temp_normalized = 1;
                    float hue = (1 - temp_normalized) * 240.0f; // Blue (240°) to Red (0°)
                    HSVtoRGB(hue, 1.0f, 1.0f, &r, &g, &b);
                } else {
                    // Temperatures from mid_temp to max_temp: Red to White
                    float temp_normalized = (temp - mid_temp) / (max_temp - mid_temp);
                    if (temp_normalized < 0) temp_normalized = 0;
                    if (temp_normalized > 1) temp_normalized = 1;
                    float saturation = 1.0f - temp_normalized; // From 1 to 0
                    HSVtoRGB(0.0f, saturation, 1.0f, &r, &g, &b); // Hue is Red (0°)
                }

                // Set the pixel color
                c->map.buffer[index].color.r = r;
                c->map.buffer[index].color.g = g;
                c->map.buffer[index].color.b = b;
                c->map.buffer[index].color.a = 255; // Full opacity
            }
            index++;
        }
    }
}

void draw_grid(core_t *c)
{
    if (c->render.temperature_mode)
        draw_temperature_mode(c);

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
