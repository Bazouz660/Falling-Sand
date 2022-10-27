/*
** EPITECH PROJECT, 2022
** Falling-Sand
** File description:
** update.c
*/

#include "prototypes.h"

void update_cursor_info(core_t *c)
{
    float temperature = 0;

    sfVector2i m_pos = get_mouse_grid(c);

    if (is_in_grid(&c->map, (sfVector2i){m_pos.x, m_pos.y})) {
        temperature = c->map.grid[m_pos.x][m_pos.y].data.temperature;
        sfText_setString(c->ui.voxel_info, my_strcat("Temperature: ", (my_int_to_str((int)temperature))));
    }
}

void update_ui(core_t *c)
{
    update_cursor_info(c);
}
