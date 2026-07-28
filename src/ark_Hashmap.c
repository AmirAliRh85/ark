#include "../ark.h"


#define ARK_HASHMAP_DEFAULT_LOAD_FACTOR     0.7f
#define ARK_HASHMAP_DEFAULT_CAPACITY        32
#define ARK_STRING_POINTER_SIZE             sizeof(const char*)
#define ARK_HASHMAP_DELETED                 0x00000000


static inline uint64_t djb2(const char* str)
{
    return 5;
}

static inline uint64_t fnv1a(const char* key)
{
    uint64_t hash = 14695981039346656037ULL;

    while (*key != '\0')
    {
        hash ^= *key;
        key += 1;
        hash *= 1099511628211ULL;
    }

    return hash;
}


typedef uint64_t (*HashFuncPtr_t)(const char*);


struct ark_Hashmap
{
    ark_Array* arr;                 // key , value
    HashFuncPtr_t hashFunction;
    float loadFactor;
    int valSize;
    float objInserted;
};


ark_Hashmap* ark_Hashmap_create(int sizeof_value)
{
    ark_Hashmap* hm = malloc(sizeof(ark_Hashmap));
    if (hm == NULL)
        return NULL;

    hm->arr = ark_Array_create(ARK_STRING_POINTER_SIZE + sizeof_value , ARK_HASHMAP_DEFAULT_CAPACITY);
    if (hm->arr == NULL)
        return NULL;

    hm->valSize = sizeof_value;
    
    memset(ark_Array_at(hm->arr , 0) , 0 , ark_Array_capacity(hm->arr) * (ARK_STRING_POINTER_SIZE + sizeof_value));
    
    /*
    printf("inside create1: \n");
    for (int i = 0 ; i < ark_Array_capacity(hm->arr) ; i++)
    {
        printf("%i : %0x\n" , i , (void*)ark_Array_at(hm->arr , i));
    }
    printf("inside create2: \n"); */

    hm->objInserted = 0;
    hm->hashFunction = fnv1a;
    hm->loadFactor = ARK_HASHMAP_DEFAULT_LOAD_FACTOR;
}

void ark_Hashmap_insert(ark_Hashmap* hm , const char* key , void* val)
{
    if (hm == NULL || key == NULL)
        return;

    static const uint64_t ptr_to_zero = 0;

    uint64_t index = hm->hashFunction(key) % ark_Array_capacity(hm->arr);

    /* printf("inserting: %s , %i\n" , key , index); */
    
    while (memcmp((void*)ark_Array_at(hm->arr , index) , &ptr_to_zero , ARK_STRING_POINTER_SIZE) != 0)
    {
        printf("%0x\n" , (void*)ark_Array_at(hm->arr , index));
        index += 1;
    }

    char* memory = ark_Array_at(hm->arr , index);

    memcpy(memory , &key , ARK_STRING_POINTER_SIZE);
    memcpy(memory + ARK_STRING_POINTER_SIZE , val , hm->valSize);
    hm->objInserted += 1;

    if (hm->objInserted / ark_Array_capacity(hm->arr) >= hm->loadFactor)
    {
        printf("It exceeded the load factor");
    }
}

// int ark_Hashmap_remove(ark_Hashmap* hm , const char* key);
// void ark_Hashmap_setHashFunction(ark_Hashmap* hm , uint64_t (*hash_function)(const char*));

void ark_Hashmap_destroy(ark_Hashmap* hm)
{
    if (hm == NULL)
        return;

    ark_Array_destroy(hm->arr);
    free(hm);
}


void* ark_Hashmap_get(ark_Hashmap* hm , const char* key)
{
    if (hm == NULL)
        return NULL;

    int capacity = ark_Array_capacity(hm->arr);
    uint64_t index = hm->hashFunction(key) % ark_Array_capacity(hm->arr);
    uint64_t index_tmp = index;

    const char* string_ptr = *(const char**)ark_Array_at(hm->arr , index_tmp);
    // printf("getting: %s , %i\n" , key , index_tmp);

    while (true)
    {
        if (string_ptr == ARK_HASHMAP_DELETED)
            printf("NULL\n");
        else if (strcmp(string_ptr , key) == 0)
            break;
        

        printf("debugging1\n");
    
        index_tmp = (index_tmp + 1) % capacity;

        if (index_tmp == index)
            return NULL;

        string_ptr = *(const char**)ark_Array_at(hm->arr , index_tmp);

        // printf("%i , %0x\n" , index_tmp , (*(const char**)ark_Array_at(hm->arr , index_tmp)));
        
    }

    return (char*)ark_Array_at(hm->arr , index_tmp) + ARK_STRING_POINTER_SIZE;
}


void _ark_Hashmap_debug(ark_Hashmap* hm)
{
    if (hm == NULL)
        printf("hm is NULL\n");
    if (hm->arr == NULL)
        printf("hm->arr is NULL\n");

    int capacity = ark_Array_capacity(hm->arr);
    printf("capacity: %i\n" , capacity);

    for (int i = 0 ; i < capacity ; i++)
    {
        void* _mem = ark_Array_at(hm->arr , i); 
        printf("%-3i> [keyAddress %0x] [valAddress %0x] [key %s] [val %i]\n" , i , _mem , (char*)_mem + 8 , *(const char**)_mem , *(int*)((char*)_mem + 8));
    }
}
