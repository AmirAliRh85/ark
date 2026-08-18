#include "../ark.h"


struct ark_RingBuffer
{
    int head;
    int tail;
    int size;
    int capacity;
    int objSize;
    void* _mem;
};

ark_RingBuffer* ark_RingBuffer_create(int sizeof_obj , int capacity)
{
    if (capacity <= 1 || sizeof_obj <= 0)
        return NULL;

    ark_RingBuffer* rb = malloc(sizeof(ark_RingBuffer));
    
    if (rb == NULL)
        return NULL;

    rb->capacity = capacity;
    rb->objSize = sizeof_obj;
    rb->_mem = malloc(capacity * sizeof_obj);
    if (rb->_mem == NULL)
    {
        free(rb);
        return NULL;
    }
    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;

    return rb;
}

void ark_RingBuffer_push(ark_RingBuffer* rb , void* src)
{
    if (rb == NULL)
        return;
    
    if (rb->size == rb->capacity)
        return;

    memcpy((char*)rb->_mem + rb->tail * rb->objSize , src , rb->objSize);
    rb->tail++;
    rb->size++;

    if (rb->tail >= rb->capacity)
        rb->tail = 0;
}

void ark_RingBuffer_pop(ark_RingBuffer* rb)
{
    if (rb == NULL)
        return;

    if (rb->size == 0)
        return;

    rb->head++;
    rb->size--;

    if (rb->head >= rb->capacity)
        rb->head = 0;   
}

void ark_RingBuffer_destroy(ark_RingBuffer* rb)
{
    if (rb == NULL)
        return;

    free(rb->_mem);
    free(rb);
}

void* ark_RingBuffer_front(ark_RingBuffer* rb)
{
    return (char*)(rb->_mem) + rb->head * rb->objSize;
}

int ark_RingBuffer_capacity(ark_RingBuffer* rb)
{
    return rb->capacity;
}

int ark_RingBuffer_size(ark_RingBuffer* rb)
{
    return rb->size;
}

int ark_RingBuffer_isFull(ark_RingBuffer* rb)
{
    return rb->capacity == rb->size;
}

int ark_RingBuffer_isEmpty(ark_RingBuffer* rb)
{
    return rb->size == 0;
}

void _ark_RingBuffer_debug(ark_RingBuffer* rb)
{
    if (rb == NULL)
        printf("rb is NULL\n");

    if (rb->_mem == NULL)
        printf("rb->_mem is NULL\n");

    int capacity = rb->capacity;
    for (int i = 0 ; i < capacity ; i++)
    {
        if (i == rb->head)
            printf("%-3i> [address %p] [val %i] HEAD\n" , i , (char*)rb->_mem + i * rb->objSize , ((int*)(rb->_mem))[i]);
        else if (i == rb->tail)
            printf("%-3i> [address %p] [val %i] TAIL\n" , i , (char*)rb->_mem + i * rb->objSize , ((int*)(rb->_mem))[i]);
        else
            printf("%-3i> [address %p] [val %i]\n" , i , (char*)rb->_mem + i * rb->objSize , ((int*)(rb->_mem))[i]);
    }
}