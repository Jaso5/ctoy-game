#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include <cglm/vec3.h>

void resize_buf(char *buf, uint size, int delta)
{
    realloc(buf, size + delta);
}

char* read_file(const char *name)
{
    char *source = NULL;
    FILE *fp = fopen(name, "r");
    if (fp != NULL)
    {
        /* Go to the end of the file. */
        if (fseek(fp, 0L, SEEK_END) == 0)
        {
            /* Get the size of the file. */
            long bufsize = ftell(fp);
            if (bufsize == -1)
            { /* Error */
            }

            /* Allocate our buffer to that size. */
            source = malloc(sizeof(char) * (bufsize + 1));

            /* Go back to the start of the file. */
            if (fseek(fp, 0L, SEEK_SET) != 0)
            { /* Error */
            }

            /* Read the entire file into memory. */
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if (ferror(fp) != 0)
            {
                printf("Error reading file");
            }
            else
            {
                source[newLen++] = '\0'; /* Just to be safe. */
            }
        }
        fclose(fp);
    }

    return source;
}


void set_vec3(vec3* vec, float x, float y, float z) {
    (*vec)[0] = x;
    (*vec)[1] = y;
    (*vec)[2] = z;
}
