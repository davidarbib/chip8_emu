#include <stdlib.h>

#define STACK_WORD_SZ 16

typedef struct s_stack
{
    size_t size;
    void *area;
    void *top;
} t_stack;

void *pop(t_stack stack);
void push(t_stack stack, size_t size, unsigned char data[size]);
void *top(t_stack stack);
