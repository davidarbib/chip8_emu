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

int stack_init(t_stack *stack, size_t elem_size, size_t cap, size_t max_cap)
{
    stack->size = 0;
    stack->cap = cap;
    if (cap == 0)
    {
        stack->cap = 1;
    }
    stack->max_cap = max_cap;
    if (max_cap == 0)
    {
        stack->max_cap = MAX_STACK_CAP;
    }
    if (stack->cap > stack->max_cap)
    {
        return -1;
    }
    stack->elem_size = elem_size;
    if ((stack->data = malloc(stack->elem_size * cap)))
    {
        return -1;
    }
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
    if (stack->size == 0)
    {
        return NULL;
    }
    void *ret = calloc(stack->elem_size, 1);
    if (!ret)
    {
        return NULL;
    }
    memcpy(ret, stack->top, stack->elem_size);
    stack->size--;
    if (stack->size != 0)
    {
        stack->top -= stack->elem_size;
    }
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
    if (stack->size == stack->max_cap)
    {
        //TODO set errno ?
        return -1;
    }
    if (stack->size == stack->cap)
    {
        if (!(stack->data = realloc(stack->data,
                                    stack->cap * stack->elem_size * 2)))
        {
            return -1;
        }
        stack->cap *= 2;
    }
    stack->top = stack->data + stack->size * stack->elem_size;
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
    if (stack->size == 0)
    {
        return NULL;
    }

    return stack->top;
}

/**
 * free resources of a stack 
 * @param stack the target stack 
*/
void destroy_stack(t_stack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->top = NULL;
    stack->size = 0;
}

/*
//------------------tests-----------------------//
int main()
{
    t_stack st1;
    int a = 42; 
    int b = 7;
    int c = 3;
    int d = -6;
    int e = 77;
    int f = -9;
    int g = -48;

    if (!stack_init(&st1, sizeof(int), 1, 0))
    {
        return EXIT_FAILURE;
    }
    push(&st1, (unsigned char *)&a);
    push(&st1, (unsigned char *)&b);
    push(&st1, (unsigned char *)&c); 
    for (int i = 0; i < 9; i++)
    {
        unsigned char *memchunk = pop(&st1);
        if (!memchunk) break;
        printf("%d\n", *(int*)memchunk);
        free(memchunk);
    }
    push(&st1, (unsigned char *)&d);
    push(&st1, (unsigned char *)&e);
    push(&st1, (unsigned char *)&f); 
    push(&st1, (unsigned char *)&g); 
    printf("%d\n", *(int*)top(&st1));
    
    for (int i = 0; i < 12; i++)
    {
        unsigned char *memchunk = pop(&st1);
        if (!memchunk) break;
        printf("%d\n", *(int*)memchunk);
        free(memchunk);
    }
    destroy_stack(&st1);
    return EXIT_SUCCESS;
}
*/
