#pragma once
#include <cglm/cglm.h>
#include <ctoy.h>
#include "mouse.h"


// Assumes y = up, z = forward

static vec3 up = {0.0f, 1.0f, 0.0f};

typedef struct Camera {
    mat4 proj_mat;
    mat4 view_mat;

    float fov;

    vec3 pos;

    // Dinnae reorder these 3 m8
    vec3 view;
    // float roll;
    // float pitch; // up/down
    // float yaw; // left/right
} Camera;

void calc_proj(Camera* cam) {
    float aspect = (float)ctoy_window_width() / (float)ctoy_window_height();
    // printf("Aspect: %f\n", aspect);
    glm_perspective(cam->fov, aspect, 0.01f, 100.0f, cam->proj_mat);
    // glm_mat4_print(cam->proj_mat, stderr);
}

void calc_view(Camera* cam) {
    mat4 transform;
    mat4 euler;
    // vec4 look = {0.0f, 0.0f, 1.0f, 0.0f};

    glm_mat4_identity(transform);
    glm_translate(transform, cam->pos);

    glm_euler(cam->view, euler);

    glm_mat4_mul(euler, transform, cam->view_mat);

    // glm_look(cam->pos, &look, &up, cam->view_mat);
}

void cam_bind_uniform(Camera* cam, uint shader) {
    // uint view_loc, proj_loc;
    uint view_loc = glGetUniformLocation(shader, "camView");
    uint proj_loc = glGetUniformLocation(shader, "camProj");

    glUniformMatrix4fv(view_loc, 1, false, (GLfloat*)cam->view_mat);
    glUniformMatrix4fv(proj_loc, 1, false, (GLfloat*)cam->proj_mat);
}

Camera* new_camera(float fov) {
    Camera* cam = malloc(sizeof(Camera));
    cam->fov = fov;
    glm_make_rad(&cam->fov);



    set_vec3(&cam->pos, 0.0f, 0.0f, 0.0f);
    set_vec3(&cam->view, 0.0f, 0.0f, 0.0f);


    calc_proj(cam);
    calc_view(cam);

    return cam;
}

void handle_resize(Camera* cam) {
    //calc_proj(cam);
}

void update_cam(Camera* cam) {
    // Looking

    vec3 move = {sin(cam->view[1]), 0.0, cos(cam->view[1])};
    vec3 m_axis = {0.0f, 0.0f, 0.0f};

    const float SPEED = 0.2;

    if (ctoy_key_pressed(CTOY_KEY_W)) {
        m_axis[2] += SPEED;
    }
    if (ctoy_key_pressed(CTOY_KEY_S)) {
        m_axis[2] -= SPEED;
    }
    if (ctoy_key_pressed(CTOY_KEY_A)) {
        m_axis[0] += SPEED;
    }
    if (ctoy_key_pressed(CTOY_KEY_D)) {
        m_axis[0] -= SPEED;
    }
    if (ctoy_key_pressed(CTOY_KEY_LEFT_SHIFT)) {
        m_axis[1] += SPEED;
    }
    if (ctoy_key_pressed(CTOY_KEY_SPACE)) {
        m_axis[1] -= SPEED;
    }

    vec3 axis = {0.0, -1.0, 0.0};
    glm_vec3_rotate(&m_axis, cam->view[1], &axis);

    float speed = 0.1f;
    glm_vec3_scale(&m_axis, speed, &m_axis);

    glm_vec3_add(cam->pos, m_axis, cam->pos);

    // LOOKING
    float accel = 0.15f;

    cam->view[1] += mouse_dx() * accel;
    cam->view[0] += mouse_dy() * accel;

    calc_view(cam);
    calc_proj(cam);
}