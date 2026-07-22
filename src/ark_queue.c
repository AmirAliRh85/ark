#include "../ark.h"

struct ark_Queue
{
    ark_SNode* front;
    ark_SNode* back;
    int size;
};


ark_Queue* ark_Queue_create()
{
    ark_Queue* q = malloc(sizeof(ark_Queue));
    if (q == NULL)
        return NULL;
    
    q->back = NULL;
    q->front = NULL;
    q->size = 0;

    return q;
}

void ark_Queue_push(ark_Queue* q , void* val)
{
    if (q == NULL || val == NULL)
        return;

    ark_SNode* node = malloc(sizeof(ark_SNode));

    if (node == NULL)
        return;

    node->value = val;
    node->prev = NULL;
    
    if (q->size == 0)
    {
        q->front = node;
        q->back = node;
    }
    else
    {
        q->back->prev = node;
        q->back = node;
    }


    q->size += 1;
}

void ark_Queue_pop(ark_Queue* q)
{
    if (q == NULL || q->size == 0)
        return;

    ark_SNode* node = q->front;
    q->front = q->front->prev;
    free(node);
    q->size -= 1;
}

void ark_Queue_destory(ark_Queue* q)
{
    if (q == NULL)
        return;

    while (q->size != 0)
        ark_Queue_pop(q);

    free(q);
}

void* ark_Queue_front(ark_Queue* q)
{
    return q->front->value;
}

bool ark_Queue_isEmpty(ark_Queue* q)
{
    if (q->size == 0)
        return true;

    return false;
}

int ark_Queue_size(ark_Queue* q)
{
    return q->size;
}