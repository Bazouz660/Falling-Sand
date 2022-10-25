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

    #define TransparentRed (sfColor){255, 0, 0, 100}

    #define new_texture(path, intrect) sfTexture_createFromFile(path, intrect)
    #define key_pressed(key) sfKeyboard_isKeyPressed(key)

#endif /*SAND_DEFINES*/

