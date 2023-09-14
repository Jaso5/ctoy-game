/* Rustlib start! */

#pragma once

/* Generated with cbindgen:0.26.0 */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct TestStruct {
  uint32_t a;
  uint8_t b;
} TestStruct;

uint32_t double_u32(uint32_t x);

struct TestStruct get_struct(void);

/* Rustlib end! */
