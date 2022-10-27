/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** inputs.h
*/

#include "structs.h"

// In game buttons

void on_click_play(core_t *c, button_t *button);
void on_click_exit(core_t *c, button_t *button);
void on_click_set_brush_id(core_t *c, button_t *button);

// User inputs
void toggle_fullscreen(core_t *c, switch_key_t *key);
void toggle_pause(core_t *c, switch_key_t *key);