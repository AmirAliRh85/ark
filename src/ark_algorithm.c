#include "../ark.h"

#define DEFAULT_DYNAMIC_ARRAY_CAPACITY  10


ark_DynamicArray* ark_DynamicArray_create(int sizeof_obj)
{
    if (sizeof_obj <= 0)
        return NULL;

    ark_DynamicArray* da = (ark_DynamicArray*)malloc(sizeof(ark_DynamicArray));
    if (!da)
        return NULL;

    da->capacity = DEFAULT_DYNAMIC_ARRAY_CAPACITY;
    da->currentIdx = 0;
    da->elementSize = sizeof_obj;    
    da->objectAddress = (void*)malloc(sizeof_obj * da->capacity);

    return da;
}

void ark_DynamicArray_push(ark_DynamicArray* da , const void* src)
{
    if (da->currentIdx >= da->capacity)
        ark_DynamicArray_resize(da);

    memcpy((char*)da->objectAddress + da->currentIdx * da->elementSize , src , da->elementSize);

    da->currentIdx += 1;
}

void ark_DynamicArray_pop(ark_DynamicArray* da)
{
    if (da->currentIdx > 0)
        da->currentIdx -= 1;
}

void ark_DynamicArray_remove(ark_DynamicArray* da , int index)
{
    if (index == da->currentIdx - 1)
        ark_DynamicArray_pop(da);

    if (index >= da->currentIdx || index < 0)
        return;

    void* dst = ark_DynamicArray_at(da , index);
    void* src = ark_DynamicArray_at(da , index + 1);

    memcpy(dst , src , (da->currentIdx - (index + 1)) * da->elementSize);
    da->currentIdx -= 1;
}

void ark_DynamicArray_resize(ark_DynamicArray* da)
{
    int new_capacity = da->capacity * 2;

    void* new_size = realloc(da->objectAddress , new_capacity * da->elementSize);
    if (!new_size)
        return;
        
    da->capacity = new_capacity;
    da->objectAddress = new_size;
}

void ark_DynamicArray_destroy(ark_DynamicArray* da)
{
    if (!da->objectAddress)
        free(da->objectAddress);
    if (!da)
        free(da);
}


void* ark_DynamicArray_at(ark_DynamicArray* da , int index)
{
    if (index >= 0 && index < da->currentIdx)
        return ((char*)da->objectAddress + (index * da->elementSize));
    else
        return NULL;
}

int ark_DynamicArray_length(ark_DynamicArray* da)
{
    return da->currentIdx;
}

int ark_DynamicArray_capacity(ark_DynamicArray* da)
{
    return da->capacity;
}

int ark_DynamicArray_find(ark_DynamicArray* da , const void* val)
{
    int len = ark_DynamicArray_length(da);
    for (unsigned int i = 0 ; i < len ; i++)
    {
        void* curr_val = ark_DynamicArray_at(da , i);
        if (memcmp(val , curr_val , da->elementSize) == 0)
            return i;
    }

    return -1;
}



ark_Pair* ark_Pair_create(int sizeof_first_item , int sizeof_second_item)
{
    if (sizeof_first_item <= 0 || sizeof_second_item <= 0)
        return NULL;

    ark_Pair* p = (ark_Pair*)malloc(sizeof(ark_Pair));

    if (!p)        
        return NULL;

    p->firstItemSize = sizeof_first_item;
    p->secondItemSize = sizeof_second_item;
    p->elementSize = p->firstItemSize + p->secondItemSize;
    p->dArray = ark_DynamicArray_create(p->elementSize);

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

    if (p->dArray->currentIdx >= p->dArray->capacity)
        ark_DynamicArray_resize(p->dArray);

    void* dest = (char*)p->dArray->objectAddress + p->dArray->elementSize * p->dArray->currentIdx;
    if (!dest) return;
    
    memcpy(dest, first_item, p->firstItemSize);
    memcpy((char*)dest + p->firstItemSize, second_item, p->secondItemSize);
    
    p->dArray->currentIdx += 1;
}

void ark_Pair_pop(ark_Pair* p)
{
    if (p && p->dArray)
        ark_DynamicArray_pop(p->dArray);
}

void ark_Pair_destroy(ark_Pair* p)
{
    ark_DynamicArray_destroy(p->dArray);
    free(p);
}

void* ark_Pair_at(ark_Pair* p , int index , ark_PairFlag flag)
{
    if (index < 0 || index >= p->dArray->currentIdx)
        return NULL;

    void* object_addres = ark_DynamicArray_at(p->dArray , index);

    if (flag == FIRST)
        return object_addres;

    return (char*)object_addres + p->firstItemSize;
}

int ark_Pair_length(ark_Pair* p)
{
    return p->dArray->currentIdx;
}
int ark_Pair_capacity(ark_Pair* p)
{
    return p->dArray->capacity;
}