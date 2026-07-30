#include "../ark.h"
#include <stdbool.h>


#define ARK_VECTOR_DEFAULT_CAPACITY  16


struct ark_Vector
{
    int capacity;
    int currIdx;
    int objSize;
    void* _mem;
};

ark_Vector* ark_Vector_create(int sizeof_obj)
{
    if (sizeof_obj <= 0)
        return NULL;

    ark_Vector* vec = (ark_Vector*)malloc(sizeof(ark_Vector));
    if (!vec)
        return NULL;

    vec->capacity = ARK_VECTOR_DEFAULT_CAPACITY;
    vec->currIdx = 0;
    vec->objSize = sizeof_obj;    
    vec->_mem = (void*)malloc(sizeof_obj * vec->capacity);

    if (vec->_mem == NULL)
    {
        free(vec);
        return NULL;
    }

    return vec;
}

void ark_Vector_push(ark_Vector* vec , const void* src)
{
    if (vec == NULL || src == NULL) 
        return;

    if (vec->currIdx >= vec->capacity)
        ark_Vector_resize(vec);

    memcpy((char*)vec->_mem + vec->currIdx * vec->objSize , src , vec->objSize);

    vec->currIdx += 1;
}

// index should not be higher than size(length) of the vector
void ark_Vector_insert(ark_Vector* vec , const void* src , int index)
{
    if (vec == NULL || index < 0)
        return;

    if (index > vec->currIdx)
        return;

    if (index == vec->capacity)
    {
        ark_Vector_push(vec , src);
        return;
    }
    
    if (vec->currIdx == vec->capacity)
        ark_Vector_resize(vec);

    memcpy((char*)vec->_mem + (index + 1) * vec->objSize , vec->_mem + index * vec->objSize , vec->objSize);
    memcpy((char*)vec->_mem + index * vec->objSize , src , vec->objSize);

    vec->currIdx += 1;
}

void ark_Vector_pop(ark_Vector* vec)
{
    if (vec == NULL) 
        return;

    if (vec->currIdx > 0)
        vec->currIdx -= 1;
}

void ark_Vector_remove(ark_Vector* vec , int index)
{
    if (vec == NULL) 
        return;

    if (index == vec->currIdx - 1)
        ark_Vector_pop(vec);

    if (index >= vec->currIdx || index < 0)
        return;

    void* dst = ark_Vector_at(vec , index);
    void* src = ark_Vector_at(vec , index + 1);

    memcpy(dst , src , (vec->currIdx - (index + 1)) * vec->objSize);
    vec->currIdx -= 1;
}

void ark_Vector_shrink(ark_Vector* vec)
{
    if (vec->currIdx == vec->capacity || vec->currIdx == 0 || vec == NULL)
        return;
    
    void* new_memory = realloc(vec->_mem , sizeof(vec->objSize) * vec->currIdx);
    
    if (new_memory)
    {
        vec->capacity = vec->currIdx;
        vec->_mem = new_memory;
    }
}   

void ark_Vector_resize(ark_Vector* vec)
{
    if (vec == NULL) 
        return;

    int new_capacity = vec->capacity * 2;

    void* new_size = realloc(vec->_mem , new_capacity * vec->objSize);
    if (!new_size)
        return;
        
    vec->capacity = new_capacity;
    vec->_mem = new_size;
}

void ark_Vector_reserve(ark_Vector* vec , int new_capacity)
{
    if (vec == NULL || new_capacity <= vec->capacity)
        return;

    void* new_mem = realloc(vec->_mem , new_capacity * vec->objSize);
    if (new_mem == NULL)
        return;

    vec->capacity = new_capacity;
    vec->_mem = new_mem;
}

void ark_Vector_destroy(ark_Vector* vec)
{
    if (vec == NULL) 
        return;

    if (!vec->_mem)
        free(vec->_mem);
    if (!vec)
        free(vec);
}


void* ark_Vector_at(ark_Vector* vec , int index)
{
    if (vec == NULL) 
        return NULL;

    if (index >= 0 && index < vec->currIdx)
        return ((char*)vec->_mem + (index * vec->objSize));
    else
        return NULL;
}

int ark_Vector_length(ark_Vector* vec)
{
    if (vec == NULL)
        return -1;

    return vec->currIdx;
}

int ark_Vector_size(ark_Vector* vec)
{
    return ark_Vector_length(vec);
}

int ark_Vector_capacity(ark_Vector* vec)
{
    if (vec == NULL)
        return -1;

    return vec->capacity;
}

int ark_Vector_find(ark_Vector* vec , const void* val)
{
    if (vec == NULL)
        return -1;

    int len = ark_Vector_length(vec);
    for (unsigned int i = 0 ; i < len ; i++)
    {
        void* curr_val = ark_Vector_at(vec , i);
        if (memcmp(val , curr_val , vec->objSize) == 0)
            return i;
    }

    return -1;
}

/* ===================================== Pair ===================================== */

struct ark_Pair
{
    int firstItemSize;
    int secondItemSize;
    int objSize;
    ark_Vector* dArray;
};

ark_Pair* ark_Pair_create(int sizeof_first_item , int sizeof_second_item)
{
    if (sizeof_first_item <= 0 || sizeof_second_item <= 0)
        return NULL;

    ark_Pair* p = (ark_Pair*)malloc(sizeof(ark_Pair));

    if (!p)        
        return NULL;

    p->firstItemSize = sizeof_first_item;
    p->secondItemSize = sizeof_second_item;
    p->objSize = p->firstItemSize + p->secondItemSize;
    p->dArray = ark_Vector_create(p->objSize);

    if (p->dArray == NULL)
    {
        free(p);
        return NULL;
    }

    return p;
}

void ark_Pair_push(ark_Pair* p , void* first_item , void* second_item)
{
    if (!p || !first_item || !second_item)
        return;

    if (p->dArray->currIdx >= p->dArray->capacity)
        ark_Vector_resize(p->dArray);

    void* dest = (char*)p->dArray->_mem + p->dArray->objSize * p->dArray->currIdx;
    if (!dest) return;
    
    memcpy(dest, first_item, p->firstItemSize);
    memcpy((char*)dest + p->firstItemSize, second_item, p->secondItemSize);
    
    p->dArray->currIdx += 1;
}

void ark_Pair_pop(ark_Pair* p)
{
    if (p && p->dArray)
        ark_Vector_pop(p->dArray);
}

void ark_Pair_shrink(ark_Pair* p)
{
    if (p && p->dArray)
        ark_Vector_shrink(p->dArray);
}

void ark_Pair_destroy(ark_Pair* p)
{
    ark_Vector_destroy(p->dArray);
    free(p);
}

void* ark_Pair_at(ark_Pair* p , int index , ark_PairFlag flag)
{
    if (index < 0 || index >= p->dArray->currIdx)
        return NULL;

    void* object_addres = ark_Vector_at(p->dArray , index);

    if (flag == ARK_FIRST)
        return object_addres;

    return (char*)object_addres + p->firstItemSize;
}

int ark_Pair_length(ark_Pair* p)
{
    return p->dArray->currIdx;
}

int ark_Pair_size(ark_Pair* p)
{
    return p->dArray->currIdx;
}

int ark_Pair_capacity(ark_Pair* p)
{
    return p->dArray->capacity;
}