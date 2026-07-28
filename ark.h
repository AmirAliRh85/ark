#ifndef ARK_H
#define ARK_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


#define ARK_MAJOR_VERSION   0
#define ARK_MINOR_VERSION   0
#define ARK_PATCH_VERSION   0

//                  -- Array --

typedef struct ark_Array ark_Array;

ark_Array* ark_Array_create(int sizeof_ob , int capacityj);
void ark_Array_insert(ark_Array* arr , int index , const void* src);
void ark_Array_resize(ark_Array* arr , int new_capacity);
void ark_Array_destroy(ark_Array* arr);

void* ark_Array_at(ark_Array* arr , int index);
int ark_Array_capacity(ark_Array* arr);
int ark_Array_find(ark_Array* arr , const void* val);

//                  -- DynamicArray --

typedef struct ark_Vector ark_Vector;

ark_Vector* ark_Vector_create(int sizeof_obj);
void ark_Vector_pop(ark_Vector* vec);
void ark_Vector_remove(ark_Vector* vec , int index);
void ark_Vector_push(ark_Vector* vec , const void* src);
void ark_Vector_insert(ark_Vector* vec , const void* src , int index);
void ark_Vector_shrink(ark_Vector* vec);
void ark_Vector_reserve(ark_Vector* vec , int new_capacity);
void ark_Vector_resize(ark_Vector* vec);
void ark_Vector_destroy(ark_Vector* vec);

void* ark_Vector_at(ark_Vector* vec , int index);
int ark_Vector_length(ark_Vector* vec);
int ark_Vector_size(ark_Vector* vec);
int ark_Vector_capacity(ark_Vector* vec);
int ark_Vector_find(ark_Vector* vec , const void* val);


//                  -- Pair --


typedef enum
{
    ARK_FIRST       = 1     ,
    ARK_SECOND      = 2
} ark_PairFlag;

typedef struct ark_Pair ark_Pair;

ark_Pair* ark_Pair_create(int sizeof_first_item , int sizeof_second_item);
void ark_Pair_push(ark_Pair* p , void* first_item , void* second_item);
void ark_Pair_pop(ark_Pair* p);
void ark_Pair_shrink(ark_Pair* p);
void ark_Pair_destroy(ark_Pair* p);

void* ark_Pair_at(ark_Pair* p , int index , ark_PairFlag flag);
int ark_Pair_length(ark_Pair* p);
int ark_Pair_size(ark_Pair* p);
int ark_Pair_capacity(ark_Pair* p);

//                  -- LinkedList and Nodes --

typedef struct ark_SNode ark_SNode;
typedef struct ark_DNode ark_DNode;


struct ark_SNode
{
    ark_SNode* prev;
    void* value;
};


struct ark_DNode
{
    ark_DNode* prev;
    ark_DNode* next;
    void* value;
};


//                  -- Stack --

typedef struct ark_Stack
{
    ark_SNode* top;
    int size;
    int maxSize;
} ark_Stack;


ark_Stack* ark_Stack_create();
void ark_Stack_push(ark_Stack* stack , void* value);
void ark_Stack_pop(ark_Stack* stack);
void ark_Stack_destroy(ark_Stack* stack);

void* ark_Stack_top(ark_Stack* stack);
int ark_Stack_size(ark_Stack* stack);
bool ark_Stack_isEmpty(ark_Stack* stack);

//                  -- Queue

typedef struct ark_Queue ark_Queue;

ark_Queue* ark_Queue_create();
void ark_Queue_push(ark_Queue* q , void* val);
void ark_Queue_pop(ark_Queue* q);
void ark_Queue_destory(ark_Queue* q);

void* ark_Queue_front(ark_Queue* q);
bool ark_Queue_isEmpty(ark_Queue* q);
int ark_Queue_size(ark_Queue* q);

//                  -- Hashmap --

typedef struct ark_Hashmap ark_Hashmap;

// the key as default is const char*
ark_Hashmap* ark_Hashmap_create(int sizeof_val);
void ark_Hashmap_insert(ark_Hashmap* hm , const char* key , void* val);
int ark_Hashmap_remove(ark_Hashmap* hm , const char* key);
void ark_Hashmap_setHashFunction(ark_Hashmap* hm , uint64_t (*hash_function)(const char*));
void ark_Hashmap_destroy(ark_Hashmap* hm);

void* ark_Hashmap_get(ark_Hashmap* hm , const char* key);

void _ark_Hashmap_debug(ark_Hashmap* hm);

//                  -- Gapbuffer --

typedef struct ark_Gapbuffer ark_Gapbuffer;

// gapbuffer size is fixed and does not change (is is not dynamic)
ark_Gapbuffer* ark_Gapbuffer_create(int capacity , int sizeof_obj);
void ark_Gapbuffer_insert(ark_Gapbuffer* gb , void* val);
void ark_Gapbuffer_remove(ark_Gapbuffer* gb);
void ark_Gapbuffer_moveLeft(ark_Gapbuffer* gb);
void ark_Gapbuffer_moveRight(ark_Gapbuffer* gb);
void ark_Gapbuffer_destroy(ark_Gapbuffer* gb);

void* ark_Gapbuffer_at(ark_Gapbuffer* gb , int idx);
int ark_Gapbuffer_getGapStart(ark_Gapbuffer* gb);
int ark_Gapbuffer_getGapEnd(ark_Gapbuffer* gb);
bool ark_Gapbuffer_isFull(ark_Gapbuffer* gb);

void ark_Gapbuffer_info(ark_Gapbuffer* gb);

/**                 -- Log --
 * 
 * 
 */

typedef enum
{
    ARK_TRACE       = 0 ,
    ARK_INFO        = 1 ,
    ARK_WARNING     = 2 ,
    ARK_ERROR       = 3 ,
    ARK_FATAL       = 4
} ark_LogLevel;

typedef struct ark_Log ark_Log;

struct ark_Log
{
    FILE* output;
    ark_LogLevel minLevel;
    char* tempBuff;
    bool showTimestamp;
    bool showLocation;
};

#define ARK_LOG(log , level , fmt , ...)                                    \
    do {                                                                    \
        if ((log)->minLevel <= level)                                       \
        {                                                                   \
            sprintf((log)->tempBuff , fmt , ##__VA_ARGS__);                 \
            ark_Log_log((log) , level , __FILE__ , __func__ , __LINE__);    \
        }                                                                   \
    } while(0)                                                              \

#define ARK_TRACE(log , fmt , ...) ARK_LOG(log , ARK_TRACE , fmt , ##__VA_ARGS__)
#define ARK_INFO(log , fmt , ...) ARK_LOG(log , ARK_INFO , fmt , ##__VA_ARGS__)
#define ARK_WARNING(log , fmt , ...) ARK_LOG(log , ARK_WARNING , fmt , ##__VA_ARGS__)
#define ARK_ERROR(log , fmt , ...) ARK_LOG(log , ARK_ERROR , fmt , ##__VA_ARGS__)
#define ARK_FATAL(log , fmt , ...) ARK_LOG(log , ARK_FATAL , fmt , ##__VA_ARGS__)

ark_Log* ark_Log_create(FILE* output , ark_LogLevel min_log_level , bool show_timestamp , bool show_location);

void ark_Log_log(ark_Log* log , ark_LogLevel level , const char* file , const char* function , int line);

void ark_Log_destroy(ark_Log* log);


/**                 -- MemoryManager --
 * 
 * 
 */


typedef struct ark_MemoryManager
{
    ark_Vector* addressAllocated;
    int memAllocated;
    char* log;
} ark_MemoryManager;

ark_MemoryManager* ark_MemoryManager_create(char* log);
void* ark_malloc(ark_MemoryManager* mem_manager , size_t _size , const char* _name);
void ark_free(ark_MemoryManager* mem_manager , void* _memory);
void ark_MemoryManager_destroy(ark_MemoryManager* mem_manager);

/**                 -- Assert --
 * 
 * 
 */

#define ARK_ASSERT(cond , msg)                              \
    do                                                      \
    {                                                       \
        if (!(cond))                                        \
        {                                                   \
            fprintf(stdout , "%s   %s\n" , #cond , msg);    \
            abort();                                        \
        }                                                   \
    }                                                       \
    while (0)

#endif