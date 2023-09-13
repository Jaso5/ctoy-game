#pragma once
#include <ctoy.h>

float mouse_dx() {
    static float last_mouse_x;
    float mouse_x = ctoy_mouse_x();

    float delta = mouse_x - last_mouse_x;
    last_mouse_x = mouse_x;
    // printf("%f, ", delta);
    return delta;
}

float mouse_dy() {
    static float last_mouse_y;
    float mouse_y = ctoy_mouse_y();

    float delta = mouse_y - last_mouse_y;
    last_mouse_y = mouse_y;
    // printf("%f\n", delta);
    return delta;
}