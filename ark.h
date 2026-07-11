#ifndef ARK_H
#define ARK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ARK_MAJOR_VERSION   0
#define ARK_MINOR_VERSION   3
#define ARK_PATCH_VERSION   0

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
    ARK_FIRST       = 1     ,
    ARK_SECOND      = 2
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

//                  -- Hashmap --



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

#define ARK_LOG(log , level , text) do { ark_Log_log(log , level , text , __FILE__ , __FUNCTION__ , __LINE__); } while(0)

#define ARK_TRACE(log , text) do { ark_Log_log(log , ARK_TRACE , text , __FILE__ , __FUNCTION__ , __LINE__); } while(0)
#define ARK_INFO(log , text) do { ark_Log_log(log , ARK_INFO , text , __FILE__ , __FUNCTION__ , __LINE__); } while(0)
#define ARK_WARNING(log , text) do { ark_Log_log(log , ARK_WARNING , text , __FILE__ , __FUNCTION__ , __LINE__); } while(0)
#define ARK_ERROR(log , text) do { ark_Log_log(log , ARK_ERROR , text , __FILE__ , __FUNCTION__ , __LINE__); } while(0)
#define ARK_FATAL(log , text) do { ark_Log_log(log , ARK_FATAL , text , __FILE__ , __FUNCTION__ , __LINE__); } while(0)

ark_Log* ark_Log_create(FILE* output , ark_LogLevel min_log_level , bool show_timestamp , bool show_location);

void ark_Log_log(ark_Log* log , ark_LogLevel level , const char* text , const char* file , const char* function , int line);

void ark_Log_destroy(ark_Log* log);


/**                 -- Assert --
 * 
 * 
 */



/**                 -- MemoryManager --
 * 
 * 
 */


typedef struct ark_MemoryManager
{
    ark_DynamicArray* addressAllocated;
    int memAllocated;
    char* log;
} ark_MemoryManager;

ark_MemoryManager* ark_MemoryManager_create(char* log);
void* ark_malloc(ark_MemoryManager* mem_manager , size_t _size , const char* _name);
void ark_free(ark_MemoryManager* mem_manager , void* _memory);
void ark_MemoryManager_destroy(ark_MemoryManager* mem_manager);


#endif