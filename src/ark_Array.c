#include "../ark.h"



struct ark_Array
{
    int capacity;
    int objSize;
    void* _mem;
};


ark_Array* ark_Array_create(int sizeof_obj , int capacity)
{
    if (capacity <= 0 || sizeof_obj <= 0)
        return NULL;

    ark_Array* arr = malloc(sizeof(ark_Array));
    if (arr == NULL)
        return NULL;
    
    arr->capacity = capacity;
    arr->objSize = sizeof_obj;
    arr->_mem = malloc(capacity * sizeof_obj);

    if (arr->_mem == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

void ark_Array_insert(ark_Array* arr , int index , const void* src)
{
    if (arr == NULL || src == NULL)
        return;

    if (index < 0 || index >= arr->capacity)
        return;
    
    memcpy((char*)arr->_mem + index * arr->objSize , src , arr->objSize);
}

void ark_Array_resize(ark_Array* arr , int new_capacity)
{
    if (arr == NULL || new_capacity < 0)
        return;

    void* new_mem = realloc(arr->_mem , new_capacity * arr->objSize);
    if (new_mem == NULL)
        return;

    arr->capacity = new_capacity;
    arr->_mem = new_mem;
}

void ark_Array_destroy(ark_Array* arr)
{
    if (arr == NULL)
        return;

    free(arr->_mem);
    free(arr);
}


void* ark_Array_at(ark_Array* arr , int index)
{
    if (arr == NULL || index < 0)
        return NULL;

    if (index >= arr->capacity)
        return NULL;

    return (char*)arr->_mem + index * arr->objSize;
}

int ark_Array_capacity(ark_Array* arr)
{
    if (arr == NULL)
        return -1;

    return arr->capacity;
}

int ark_Array_find(ark_Array* arr , const void* src)
{
    if (arr == NULL || src == NULL)
        return -1;

    int cap = arr->capacity;
    for (int i = 0 ; i < cap ; i++)
    {
        if (memcmp(ark_Array_at(arr , i) , src , arr->objSize))
            return i;
    }

    return -1;
}