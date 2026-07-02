#include "../ark.h"
#include <stdio.h>

#define HRT_DEBUG
#define HRT_AUTO_FREE


ark_ResourceTracker ResourceTracker;


typedef struct ark_Object
{
    const char* name;
    void* address;
    int size;
} ark_Object;


void ark_ResouceTracker_create()
{
    #ifdef HRT_DEBUG
        ResourceTracker.addressAllocated = ark_DynamicArray_create(sizeof(ark_Object));
        ResourceTracker.memAllocated = 0;
    #else
        #warning "debug mode is not enabled either define HRT_DEBUG in your file or just add -DHRT_DEBUG compile flag"
        return;
    #endif
}

void* ark_malloc(size_t _size , const char* _name)
{
    void* _memory = malloc(_size);

    #ifdef HRT_DEBUG
        if (!_memory)
        {
            printf("[error] Failed to allocate memory for%s\n" , _name);
            return NULL;
        }
        else
        {
            ark_Object obj;

            ResourceTracker.memAllocated += _size;
            obj.name = _name;
            obj.size = _size;
            obj.address = _memory;

            ark_DynamicArray_push(ResourceTracker.addressAllocated , &obj);

            printf("[info] Memory got allocated for %s\n" , _name);
        }
    #else
        #warning "debug mode is not enabled either define HRT_DEBUG in your file or just add -DHRT_DEBUG compile flag"
    #endif

    return _memory;
}

void ark_free(void* _memory)
{
    #ifdef HRT_DEBUG
        int idx = -1;
        int len = ark_DynamicArray_length(ResourceTracker.addressAllocated);
        ark_Object obj;

        for (int i = 0 ; i < len ; i++)
        {
            obj = *(ark_Object*)ark_DynamicArray_at(ResourceTracker.addressAllocated , i);

            if (obj.address == _memory)
            {
                idx = i;
                break;
            }
        }

        if (idx < 0)
        {
            printf("[warning] You either have freed it once or you are freeing a non valid address\n");
        }
        else
        {
            obj = *(ark_Object*)ark_DynamicArray_at(ResourceTracker.addressAllocated , idx);

            printf("[info] %s got freed at %0x with size %i\n" , obj.name , obj.address , obj.size);
            
            ResourceTracker.memAllocated -= obj.size;
            
            ark_DynamicArray_remove(ResourceTracker.addressAllocated , idx);
            free(_memory);
        }
    #else
        #warning "debug mode is not enabled either define HRT_DEBUG in your file or just add -DHRT_DEBUG compile flag"
        free(_memory);
    #endif
}

void ark_memDebug()
{
    #ifdef HRT_DEBUG
        int len = ark_DynamicArray_length(ResourceTracker.addressAllocated);
        ark_Object* obj;

        printf("========== memDebug ==========\n");
        printf("total memory allocated: %i\n" , ResourceTracker.memAllocated);
        
        for (int i = 0 ; i < len ; i++)
        {
            obj = (ark_Object*)ark_DynamicArray_at(ResourceTracker.addressAllocated , i);
            printf("%-20s 0x%-20x %i\n" , obj->name , obj->address , obj->size);
        }
    #else
        #warning "debug mode is not enabled either define HRT_DEBUG in your file or just add -DHRT_DEBUG compile flag"
    #endif
}

void ark_ResouceTracker_destroy()
{
    #ifdef HRT_DEBUG
        ark_memDebug();
        
        #ifdef HRT_AUTO_FREE
            if (ResourceTracker.memAllocated > 0)
            {
                int len = ark_DynamicArray_length(ResourceTracker.addressAllocated);

                ark_Object obj;
                for (int i = len - 1 ; i >= 0 ; i--)
                {
                    obj = *(ark_Object*)ark_DynamicArray_at(ResourceTracker.addressAllocated , i);
                    ark_free(obj.address);
                    ark_DynamicArray_pop(ResourceTracker.addressAllocated);
                }

                printf("[info] remaining allocated memory got freed\n");
            }

            ark_memDebug();
        #endif

        ark_DynamicArray_destroy(ResourceTracker.addressAllocated);
        ResourceTracker.memAllocated = 0;
    #else
        #warning "debug mode is not enabled either define HRT_DEBUG in your file or just add -DHRT_DEBUG compile flag"
    #endif
}