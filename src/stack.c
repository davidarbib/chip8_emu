#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/**
 * init a stack
 * @param stack the stack to init
 * @param elem_size the size of stack element
*/

int stack_init(t_stack *stack, size_t elem_size)
{
    stack->size = 0;
    stack->cap = 1;
    stack->elem_size = elem_size;
    if ((stack->data = malloc(stack->elem_size))) return -1;
    stack->top = stack->data;

    return 0;
}

/**
 * copy last stack element to a new returned memory chunk
 * this element is then lost by the stack
 * @param stack the stack to pop
 * @return a fresh memory chunk with popped data 
*/

unsigned char *pop(t_stack *stack)
{
    if (stack->size == 0) return NULL;
    void *ret = calloc(stack->elem_size, 1);
    if (!ret) return NULL;
    memcpy(ret, stack->top, stack->elem_size);
    stack->size--;
    stack->top -= stack->elem_size;

    return ret;
}

/**
 * push a new element to stack
 * can fail :
 * - in case of stack overflow
 * - if realloc fail
 * @param stack the target stack
 * @param data the new element data
*/

int push(t_stack *stack, unsigned char *data)
{
    if (stack->size == MAX_STACK_ELEM)
    {
        //TODO set errno ?
        return -1;
    }
    if (stack->size == stack->cap)
    {
        if (!realloc(stack->data, stack->cap * 2)) return -1;
        stack->cap *= 2;
    }
    if (stack->size != 0)
    {
        stack->top += stack->elem_size;
    }
    stack->size++;
    memcpy(stack->top, data, stack->elem_size);
    return 0;
}

/**
 * return a constant pointer to last stack element
 * @param stack the target stack
*/
unsigned char const *top(t_stack *stack)
{
    return stack->top;
}

//------------------tests-----------------------//
int main()
{
    t_stack st1;
    if (!stack_init(&st1, sizeof(int))) return EXIT_FAILURE;
    int a = 42; 
    int b = 7;
    int c = 3;
    push(&st1, (unsigned char *)&a);
    push(&st1, (unsigned char *)&b);
    push(&st1, (unsigned char *)&c); 
    for (int i = 0; i < 2; i++)
    {
        printf("%d", *(int*)pop(&st1));
    }
    return EXIT_SUCCESS;
}
