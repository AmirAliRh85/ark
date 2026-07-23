#include "../ark.h"
#include <stdbool.h>


#define ARK_DEFAULT_DYNAMIC_ARRAY_CAPACITY  16

struct ark_DynamicArray
{
    int capacity;
    int currIdx;
    int elementSize;
    void* objAddress;
};

ark_DynamicArray* ark_DynamicArray_create(int sizeof_obj)
{
    if (sizeof_obj <= 0)
        return NULL;

    ark_DynamicArray* da = (ark_DynamicArray*)malloc(sizeof(ark_DynamicArray));
    if (!da)
        return NULL;

    da->capacity = ARK_DEFAULT_DYNAMIC_ARRAY_CAPACITY;
    da->currIdx = 0;
    da->elementSize = sizeof_obj;    
    da->objAddress = (void*)malloc(sizeof_obj * da->capacity);

    return da;
}

void ark_DynamicArray_push(ark_DynamicArray* da , const void* src)
{
    if (da == NULL) 
        return;

    if (da->currIdx >= da->capacity)
        ark_DynamicArray_resize(da);

    memcpy((char*)da->objAddress + da->currIdx * da->elementSize , src , da->elementSize);

    da->currIdx += 1;
}

void ark_DynamicArray_pop(ark_DynamicArray* da)
{
    if (da == NULL) 
        return;

    if (da->currIdx > 0)
        da->currIdx -= 1;
}

void ark_DynamicArray_remove(ark_DynamicArray* da , int index)
{
    if (da == NULL) 
        return;

    if (index == da->currIdx - 1)
        ark_DynamicArray_pop(da);

    if (index >= da->currIdx || index < 0)
        return;

    void* dst = ark_DynamicArray_at(da , index);
    void* src = ark_DynamicArray_at(da , index + 1);

    memcpy(dst , src , (da->currIdx - (index + 1)) * da->elementSize);
    da->currIdx -= 1;
}

void ark_DynamicArray_shrink(ark_DynamicArray* da)
{
    if (da->currIdx == da->capacity || da->currIdx == 0 || da == NULL)
        return;
    
    void* new_memory = realloc(da->objAddress , sizeof(da->elementSize) * da->currIdx);
    
    if (new_memory)
    {
        da->capacity = da->currIdx;
        da->objAddress = new_memory;
    }
}   

void ark_DynamicArray_resize(ark_DynamicArray* da)
{
    if (da == NULL) 
        return;

    int new_capacity = da->capacity * 2;

    void* new_size = realloc(da->objAddress , new_capacity * da->elementSize);
    if (!new_size)
        return;
        
    da->capacity = new_capacity;
    da->objAddress = new_size;
}

void ark_DynamicArray_reserve(ark_DynamicArray* da , int new_capacity)
{
    if (da == NULL || new_capacity <= da->capacity)
        return;

    void* new_mem = realloc(da->objAddress , new_capacity * da->elementSize);
    if (new_mem == NULL)
        return;

    da->capacity = new_capacity;
    da->objAddress = new_mem;
}

void ark_DynamicArray_destroy(ark_DynamicArray* da)
{
    if (da == NULL) 
        return;

    if (!da->objAddress)
        free(da->objAddress);
    if (!da)
        free(da);
}


void* ark_DynamicArray_at(ark_DynamicArray* da , int index)
{
    if (da == NULL) 
        return NULL;

    if (index >= 0 && index < da->currIdx)
        return ((char*)da->objAddress + (index * da->elementSize));
    else
        return NULL;
}

int ark_DynamicArray_length(ark_DynamicArray* da)
{
    if (da == NULL)
        return -1;

    return da->currIdx;
}

int ark_DynamicArray_size(ark_DynamicArray* da)
{
    if (da == NULL)
        return -1;

    return ark_DynamicArray_length(da);
}

int ark_DynamicArray_capacity(ark_DynamicArray* da)
{
    if (da == NULL)
        return -1;

    return da->capacity;
}

int ark_DynamicArray_find(ark_DynamicArray* da , const void* val)
{
    if (da == NULL)
        return -1;

    int len = ark_DynamicArray_length(da);
    for (unsigned int i = 0 ; i < len ; i++)
    {
        void* curr_val = ark_DynamicArray_at(da , i);
        if (memcmp(val , curr_val , da->elementSize) == 0)
            return i;
    }

    return -1;
}

/* ===================================== Pair ===================================== */

struct ark_Pair
{
    int firstItemSize;
    int secondItemSize;
    int elementSize;
    ark_DynamicArray* dArray;
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

    if (p->dArray->currIdx >= p->dArray->capacity)
        ark_DynamicArray_resize(p->dArray);

    void* dest = (char*)p->dArray->objAddress + p->dArray->elementSize * p->dArray->currIdx;
    if (!dest) return;
    
    memcpy(dest, first_item, p->firstItemSize);
    memcpy((char*)dest + p->firstItemSize, second_item, p->secondItemSize);
    
    p->dArray->currIdx += 1;
}

void ark_Pair_pop(ark_Pair* p)
{
    if (p && p->dArray)
        ark_DynamicArray_pop(p->dArray);
}

void ark_Pair_shrink(ark_Pair* p)
{
    if (p && p->dArray)
        ark_DynamicArray_shrink(p->dArray);
}

void ark_Pair_destroy(ark_Pair* p)
{
    ark_DynamicArray_destroy(p->dArray);
    free(p);
}

void* ark_Pair_at(ark_Pair* p , int index , ark_PairFlag flag)
{
    if (index < 0 || index >= p->dArray->currIdx)
        return NULL;

    void* object_addres = ark_DynamicArray_at(p->dArray , index);

    if (flag == ARK_FIRST)
        return object_addres;

    return (char*)object_addres + p->firstItemSize;
}

int ark_Pair_length(ark_Pair* p)
{
    return p->dArray->currIdx;
}
int ark_Pair_capacity(ark_Pair* p)
{
    return p->dArray->capacity;
}


/* ===================================== Stack ===================================== */

#define ARK_STACK_MAX_SIZE      4096

ark_Stack* ark_Stack_create()
{
    ark_Stack* stack = malloc(sizeof(ark_Stack));
    
    stack->maxSize = ARK_STACK_MAX_SIZE;
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

void ark_Stack_push(ark_Stack* stack , void* value)
{
    ark_SNode* top = malloc(sizeof(ark_SNode));
    top->prev = NULL;
    top->value = value;
    
    stack->size += 1;

    if (stack->top == NULL)
    {
        stack->top = top;
        return;
    }

    top->prev = stack->top;
    stack->top = top;
}

void ark_Stack_pop(ark_Stack* stack)
{
    if (stack->size == 0 || stack == NULL)
        return;

    ark_SNode* top = stack->top;

    stack->top = top->prev;
    stack->size -= 1;

    free(top);
}

void ark_Stack_destroy(ark_Stack* stack)
{
    while (stack->size >= 1)
    {
        ark_Stack_pop(stack);
    }

    free(stack);
}

void* ark_Stack_top(ark_Stack* stack)
{
    return stack->top->value;
}

int ark_Stack_size(ark_Stack* stack)
{
    return stack->size;
}

bool ark_Stack_isEmpty(ark_Stack* stack)
{
    if (stack->size <= 0)
        return true;

    return false;
}