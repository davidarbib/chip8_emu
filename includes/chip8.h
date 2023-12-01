#ifndef CHIP8_H
# define CHIP8_H

#include <stdint.h>
#include "stack.h"

# define SCREEN_WIDTH 64
# define SCREEN_HEIGHT 32

# define RAM_SIZE 4096

typedef struct s_screen 
{
    uint64_t pixels[SCREEN_HEIGHT];
} t_screen;

typedef struct s_reg 
{
    uint8_t value;
} t_reg;

typedef struct s_timer
{
    uint8_t count;
} t_timer;

typedef struct s_ram
{
    unsigned char data[RAM_SIZE];
} t_ram;

typedef struct s_chip8
{
   t_screen screen; 
   uint16_t PC;
   uint16_t I;
   t_reg V[16];
   t_ram ram;
   t_stack stack;
   t_timer delay_tim;
   t_timer sound_tim;
} t_chip8;

#endif
