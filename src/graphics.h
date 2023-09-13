#pragma once
#include "util.h"
#include <GLES2/gl2.h>

GLuint gu_shader_from_string(GLenum type, const char *src)
{
    GLuint shader;
    GLint compiled;

    shader = glCreateShader(type);
    if (shader == 0)
        return 0;
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {

        GLint ilen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &ilen);

        if (ilen > 0)
        {
            char *infolog = malloc(sizeof(char) * (ilen + 1));
            glGetShaderInfoLog(shader, ilen, NULL, infolog);
            printf("Error compiling shader:\n%s\n", infolog);
            free(infolog);
            printf("--SHADER START--\n%s\n---SHADER END---\n", src);
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint compile_shader(GLenum type, char* name)
{
    char *buf = read_file(name);
    return gu_shader_from_string(type, buf);
}

GLuint compile_program(char* vtx_path, char* frg_path, void (*fn)(uint*)) {
    uint vtx = compile_shader(GL_VERTEX_SHADER, vtx_path);
    uint frg = compile_shader(GL_FRAGMENT_SHADER, frg_path);
    uint prg = glCreateProgram();
    glAttachShader(prg, vtx);
    glAttachShader(prg, frg);

    (*fn)(&prg);

    glLinkProgram(prg);

    int success;
    glGetProgramiv(prg, GL_LINK_STATUS, &success);
    if(!success) {
        char* buf = malloc(1024);
        glGetProgramInfoLog(prg, 1024, NULL, buf);
        printf("===SHADER LINK ERROR===\n%s=======================\n");
        glDeleteProgram(prg);
        glDeleteShader(vtx);
        glDeleteShader(frg);
        return 0;
    }

    glDeleteShader(vtx);
    glDeleteShader(frg);

    return prg;
}