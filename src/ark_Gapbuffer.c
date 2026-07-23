#include "../ark.h"

// remaining gap in the gapbuffer should not be lower than this

struct ark_Gapbuffer
{
    int capacity;
    int objSize;
    void* memory;

    int startGapIdx;
    int endGapIdx;
};


ark_Gapbuffer* ark_Gapbuffer_create(int capacity , int sizeof_obj)
{
    ark_Gapbuffer* gb = malloc(sizeof(ark_Gapbuffer));
    
    if (gb == NULL || capacity < 2 || sizeof_obj < 1)
        return NULL;

    gb->capacity = capacity;
    gb->objSize = sizeof_obj;
    gb->memory = malloc(gb->objSize * gb->capacity);

    gb->startGapIdx = 0;
    gb->endGapIdx = gb->capacity - 1;

    return gb;
}

void ark_Gapbuffer_insert(ark_Gapbuffer* gb , void* val)
{
    if (gb == NULL || gb->startGapIdx == gb->endGapIdx)
        return;

    memcpy(gb->memory + gb->startGapIdx * gb->objSize , val , gb->objSize);
    gb->startGapIdx += 1;
}

void ark_Gapbuffer_remove(ark_Gapbuffer* gb)
{
    if (gb == NULL || gb->startGapIdx == 0)
        return;

    gb->startGapIdx -= 1;
}

void ark_Gapbuffer_moveLeft(ark_Gapbuffer* gb)
{
    if (gb == NULL || gb->startGapIdx == 0)
        return;

    memcpy(gb->memory + gb->objSize * gb->endGapIdx , gb->memory + gb->objSize * (gb->startGapIdx - 1) , gb->objSize);
    
    gb->startGapIdx -= 1;
    gb->endGapIdx -= 1;
}

void ark_Gapbuffer_moveRight(ark_Gapbuffer* gb)
{
    if (gb == NULL || gb->endGapIdx == gb->capacity - 1)
        return;

    memcpy(gb->memory + gb->objSize * gb->startGapIdx , gb->memory + gb->objSize * (gb->endGapIdx + 1) , gb->objSize);
    
    gb->startGapIdx += 1;
    gb->endGapIdx += 1;
}

void ark_Gapbuffer_destroy(ark_Gapbuffer* gb)
{
    if (gb == NULL)
        return;
    
    free(gb->memory);
    free(gb);
}


void* ark_Gapbuffer_at(ark_Gapbuffer* gb , int idx) { return (char*)gb->memory + idx * gb->objSize ; }
int ark_Gapbuffer_getGapStart(ark_Gapbuffer* gb) { return gb->startGapIdx ; }
int ark_Gapbuffer_getGapEnd(ark_Gapbuffer* gb) { return gb->endGapIdx ; }
bool ark_Gapbuffer_isFull(ark_Gapbuffer* gb) { return gb->startGapIdx == gb->endGapIdx ? true : false ; }

void ark_Gapbuffer_info(ark_Gapbuffer* gb)
{
    printf("capacity: %i , objSize: %i , memAddress: %0x\n" , gb->capacity , gb->objSize , gb->memory);
    printf("startGap: %i , endGap: %i\n" , gb->startGapIdx , gb->endGapIdx);
}