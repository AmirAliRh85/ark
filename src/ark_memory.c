#include "../ark.h"
#include <stdio.h>

#define ARK_MEMORY
#define ARK_MEMORY_AUTO_FREE


typedef struct ark_Object
{
    const char* name;
    void* address;
    int size;
} ark_Object;


static void ark_memDebug(ark_MemoryManager* mem_manager)
{
    int len = ark_DynamicArray_length(mem_manager->addressAllocated);

    printf("========== Info ==========\n");
    for (int i = 0 ; i < len ; i++)
    {
        ark_Object obj = *(ark_Object*)ark_DynamicArray_at(mem_manager->addressAllocated , i);
        printf("%0x , %s , %i\n" , obj.address , obj.name , obj.size);
    }
    printf("==========================\n");

}

ark_MemoryManager* ark_MemoryManager_create(char* log)
{
    #ifdef ARK_MEMORY
        ark_MemoryManager* mem_manager = (ark_MemoryManager*)malloc(sizeof(ark_MemoryManager));
        mem_manager->addressAllocated = ark_DynamicArray_create(sizeof(ark_Object));
        
        if (!mem_manager || !mem_manager->addressAllocated)
            return NULL;

        mem_manager->memAllocated = 0;
        mem_manager->log = log;

        return mem_manager;
    #else
        #warning "debug mode is not enabled either define ARK_MEMORY in your file or just add -DARK_MEMORY compile flag"
        return NULL;
    #endif
}

void* ark_malloc(ark_MemoryManager* mem_manager , size_t _size , const char* _name)
{
    void* _memory = malloc(_size);

    #ifdef ARK_MEMORY
        char buff[128];

        if (!_memory)
        {
            if (!mem_manager->log)
            {
                sprintf(buff , "[ERROR] Failed to allocate memory for %s\n" , _name);
                strcat(mem_manager->log , buff);
            }

            return NULL;
        }
        else
        {
            ark_Object obj;

            mem_manager->memAllocated += _size;
            obj.name = _name;
            obj.size = _size;
            obj.address = _memory;

            ark_DynamicArray_push(mem_manager->addressAllocated , &obj);

            if (!mem_manager->log)
            {
                sprintf(buff , "[INFO] %i bytes of memory got allocated for \"%s\"\n" , _size , _name);
                strcat(mem_manager->log , buff);
            }
        }
    #else
        #warning "debug mode is not enabled either define ARK_MEMORY in your file or just add -DARK_MEMORY compile flag"
    #endif

    return _memory;
}

void ark_free(ark_MemoryManager* mem_manager , void* _memory)
{
    #ifdef ARK_MEMORY
        int idx = -1;
        int len = ark_DynamicArray_length(mem_manager->addressAllocated);
        ark_Object obj;

        for (int i = 0 ; i < len ; i++)
        {
            obj = *(ark_Object*)ark_DynamicArray_at(mem_manager->addressAllocated , i);

            if (obj.address == _memory)
            {
                idx = i;
                break;
            }
        }

        if (idx < 0)
        {
            if (!mem_manager->log)
                strcat(mem_manager->log , "[WARNING] You either have freed it once or you are freeing a non valid address\n");
        }
        else
        {
            char buff[128];
            obj = *(ark_Object*)ark_DynamicArray_at(mem_manager->addressAllocated , idx);

            if (!mem_manager->log)
            {
                sprintf(buff , "[INFO] \"%s\" got freed at %0x with size of %i bytes\n" , obj.name , obj.address , obj.size);   
                strcat(mem_manager->log , buff);
            }
            
            mem_manager->memAllocated -= obj.size;
            
            ark_memDebug(mem_manager);
            ark_DynamicArray_remove(mem_manager->addressAllocated , idx);
            free(_memory);
            ark_memDebug(mem_manager);
        }
    #else
        #warning "debug mode is not enabled either define ARK_MEMORY in your file or just add -DARK_MEMORY compile flag"
        free(_memory);
    #endif
}

void ark_MemoryManager_destroy(ark_MemoryManager* mem_manager)
{
    #ifdef ARK_MEMORY
        #ifdef ARK_MEMORY_AUTO_FREE
            if (mem_manager->memAllocated > 0)
            {
                if (!mem_manager->log)
                    strcat(mem_manager->log , "[WARNING] There are still some object that has not been freed\n");

                int len = ark_DynamicArray_length(mem_manager->addressAllocated);

                ark_Object obj;
                for (int i = len - 1 ; i >= 0 ; i--)
                {
                    obj = *(ark_Object*)ark_DynamicArray_at(mem_manager->addressAllocated , i);
                    ark_free(mem_manager , obj.address);
                    ark_DynamicArray_pop(mem_manager->addressAllocated);
                }

                if (!mem_manager->log)
                    strcat(mem_manager->log , "[INFO] Remaining allocated memory got freed\n");
            }
        #endif

        ark_DynamicArray_destroy(mem_manager->addressAllocated);
        mem_manager->memAllocated = 0;
        mem_manager->log = NULL;
    #else
        #warning "debug mode is not enabled either define ARK_MEMORY in your file or just add -DARK_MEMORY compile flag"
    #endif
}