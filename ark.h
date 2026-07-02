#ifndef ARK_H
#define ARK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**                 -- Algorithms --
 *  - DynamicArray
 *      1. create
 *      2.
 * 
 *  - Pair
 * 
 * 
 *  - Stack
 * 
 * 
 *  - Hashmap
 * 
 * 
 *  - LinkedList
 * 
 */
//                  -- DynamicArray --
typedef struct ark_DynamicArray
{
    int capacity;
    int currentIdx;
    int elementSize;
    void* objectAddress;

} ark_DynamicArray;


ark_DynamicArray* ark_DynamicArray_create(int sizeof_obj);
void ark_DynamicArray_pop(ark_DynamicArray* da);
void ark_DynamicArray_remove(ark_DynamicArray* da , int index);
void ark_DynamicArray_push(ark_DynamicArray* da , const void* src);
void ark_DynamicArray_resize(ark_DynamicArray* da);
void ark_DynamicArray_destroy(ark_DynamicArray* da);

void* ark_DynamicArray_at(ark_DynamicArray* da , int index);
int ark_DynamicArray_length(ark_DynamicArray* da);
int ark_DynamicArray_capacity(ark_DynamicArray* da);
int ark_DynamicArray_find(ark_DynamicArray* da , const void* val);


//                  -- Pair --


typedef enum
{
    FIRST       = 0         ,
    SECOND
} ark_PairFlag;

typedef struct ark_Pair
{
    int firstItemSize;
    int secondItemSize;
    int elementSize;
    ark_DynamicArray* dArray;

} ark_Pair;


ark_Pair* ark_Pair_create(int sizeof_first_item , int sizeof_second_item);
void ark_Pair_push(ark_Pair* p , void* first_item , void* second_item);
void ark_Pair_pop(ark_Pair* p);
void ark_Pair_destroy(ark_Pair* p);

void* ark_Pair_at(ark_Pair* p , int index , ark_PairFlag flag);
int ark_Pair_length(ark_Pair* p);
int ark_Pair_capacity(ark_Pair* p);


//                  -- LinkedList --





//                  -- Stack --


ark_Pair* ark_Stack_create(int sizeof_first_item , int sizeof_second_item);
void ark_Stack_push(ark_Pair* p , void* first_item , void* second_item);
void ark_Stack_pop(ark_Pair* p);
void ark_Stack_destroy(ark_Pair* p);

void* ark_Pair_top(ark_Pair* p , int index , ark_PairFlag flag);
int ark_Stack_size(ark_Pair* p);

//                  -- Hashmap --



//                  -- Log --

typedef struct ark_ResourceTracker ark_ResourceTracker;


typedef enum
{
    TRACE       = 0 ,
    INFO        = 1 ,
    ERROR       = 2 ,
    WARNING     = 3 ,
    FATAL       = 4
} ark_LogLevel;


// it will only save the logs when the level is between min and max level
typedef struct ark_Log
{
    const char* title;
    ark_LogLevel minLevel;
    ark_LogLevel maxLevel;
    char* log;
    // int currLogIdx;
} ark_Log;

ark_Log* ark_Log_create(const char* title , ark_LogLevel min_level , ark_LogLevel max_level , int log_size);

void ark_Log_add(ark_Log* log , ark_LogLevel level , const char* text);
void ark_Log_flush(ark_Log* log , FILE* dst);

void ark_Log_destroy(ark_Log* log);

//                  -- Debugging --

struct ark_ResourceTracker
{
    ark_DynamicArray* addressAllocated;
    int memAllocated;
};

extern ark_ResourceTracker ResourceTracker;

void ark_ResouceTracker_create();
void* ark_malloc(size_t _size , const char* _name);
void ark_free(void* _memory);
void ark_memDebug();
void ark_ResouceTracker_destroy();


#endif