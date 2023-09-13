#pragma once
#include <ctoy.h> // ctoy API (including frequently used ANSI C libs)
#include <GLES2/gl2.h>
#include "graphics.h"
#include "types.h"
#include "camera.h"
#include <cglm/mat4.h>

void test_shader(uint *prg)
{
    glBindAttribLocation(*prg, 0, "vPos");
    glBindAttribLocation(*prg, 1, "vCol");
}

float vertices[] = {
     -1.0f, -1.0f, -5.0f, 1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, -5.0f, 0.0f, 1.0f, 0.0f,
     -1.0f,  1.0f, -5.0f, 0.0f, 0.0f, 1.0f,
      1.0f,  1.0f, -5.0f, 0.5f, 0.0f, 0.5f
};
uint VBO;
uint test_prg;

Camera* cam;

void ctoy_begin() // called at the beginning of the program
{
    printf("PROGRAM START\n");
    printf(
        "Window size: %i, %i\nFB size: %i, %i\n",
        ctoy_window_width(),
        ctoy_window_height(),
        ctoy_frame_buffer_width(),
        ctoy_frame_buffer_height()
    );

    ctoy_mouse_disable();

    test_prg = compile_program(
        "data/test.vtx.glsl",
        "data/test.frg.glsl",
        &test_shader);

    cam = new_camera(45.0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
}

void ctoy_main_loop() // called at every update of the main loop
{
    update_cam(cam);

    glViewport(0, 0, ctoy_frame_buffer_width(), ctoy_frame_buffer_height());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(test_prg);
    cam_bind_uniform(cam, test_prg);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    ctoy_swap_buffer(NULL);
}

void ctoy_end() // called at the end of the program
{
    glDeleteProgram(test_prg);
    printf("PROGRAM END\n");
}