#ifndef STACK_H
# define STACK_H

#include <stdlib.h>

#define MAX_STACK_ELEM 4096

typedef struct s_stack
{
    size_t size;
    size_t cap;
    size_t elem_size;
    unsigned char *data;
    unsigned char *top;
} t_stack;

int stack_init(t_stack *stack, size_t elem_size);
unsigned char *pop(t_stack *stack);
int push(t_stack *stack, unsigned char *data);
unsigned char const *top(t_stack *stack);

#endif
