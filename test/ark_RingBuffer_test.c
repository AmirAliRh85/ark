#include "../ark.h"
#include <stdio.h>
#include <stdlib.h>

#define print(_mem , type)                      \
    do                                          \
    {                                           \
        printf("%i\n" , *(type*)_mem);          \
    } while (0)

int main()
{
    ark_RingBuffer* rb = ark_RingBuffer_create(sizeof(int) , 8);

    int a = 5;
    ark_RingBuffer_push(rb , &a);
    a = 6;
    ark_RingBuffer_push(rb , &a);
    a = 7;
    ark_RingBuffer_push(rb , &a);
    a = 8;
    ark_RingBuffer_push(rb , &a);
    a = 9;
    ark_RingBuffer_push(rb , &a);

    ark_RingBuffer_pop(rb);
    ark_RingBuffer_pop(rb);
    
    a = 9;
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_push(rb , &a);
    ark_RingBuffer_pop(rb);

    _ark_RingBuffer_debug(rb);

    ARK_ASSERT(ark_RingBuffer_capacity(rb) == 8);
    ARK_ASSERT(ark_RingBuffer_size(rb) == 7);
    ARK_ASSERT(ark_RingBuffer_isEmpty(rb) == false);
    ARK_ASSERT(ark_RingBuffer_isFull(rb) == false);

    ark_RingBuffer_destroy(rb);
}