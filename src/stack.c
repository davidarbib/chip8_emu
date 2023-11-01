#include <stdlib.h>
#include "stack.h"

void *pop(t_stack stack)
{
    if (stack.size == 0) return NULL;
    void *ret = calloc(STACK_WORD_SZ, 1);
    if (!ret) return NULL;
    return ret;
}

//void push(t_stack stack, size_t size, unsigned char data[size])
//{
//}

//void *top(t_stack stack)
//{
//    return NULL;
//}
