/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** defines.h
*/

#ifndef SAND_DEFINES
    #define SAND_DEFINES

    #define True 1
    #define False 0

    #define true True
    #define false False

    #define SCREEN_HEIGHT 1080
    #define SCREEN_WIDTH 1920

    #define PI 3.14159265359
    #define DR 0.0174533

    #define bool unsigned short

    #define gravity 9

    #define GRID(map, gx, gy) ((map)->grid[(gy) * (map)->dim.x + (gx)])
    #define PMAP(map, gx, gy) ((map)->pmap[(gy) * (map)->air_dim.x + (gx)])
    #define VX(map, gx, gy) ((map)->vx[(gy) * (map)->air_dim.x + (gx)])
    #define VY(map, gx, gy) ((map)->vy[(gy) * (map)->air_dim.x + (gx)])

    #define TransparentRed (sfColor){255, 0, 0, 100}

    #define new_texture(path, intrect) sfTexture_createFromFile(path, intrect)
    #define key_pressed(key) sfKeyboard_isKeyPressed(key)

    #define MIN_TEMPERATURE -273.15
    #define MAX_TEMPERATURE 5000

    #define AIR_CELL 4
    #define AIR_LOSS 0.999f
    #define VELOCITY_FACTOR 0.4f
    #define VELOCITY_LOSS 0.999f
    #define PRESSURE_ITERATIONS 4
    #define MAX_CFL 0.9f
    #define EXPLOSION_PRESSURE 120.0f
    #define HEAT_PRESSURE_FACTOR 0.00005f

#endif /*SAND_DEFINES*/

