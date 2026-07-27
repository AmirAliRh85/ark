#include "../ark.h"


#define ARK_HASHMAP_DEFAULT_LOAD_FACTOR     0.7f
#define ARK_HASHMAP_DEFAULT_CAPACITY        16


static uint64_t djb2(const char* str)
{
    return 5;
}


typedef uint64_t (*HashFuncPtr_t)(const char*);


struct ark_Hashmap
{
    HashFuncPtr_t hashFunction;
    float loadFactor;
    ark_Pair* pair;                 // key , value
    int capacity;
    int size;
};


ark_Hashmap* ark_Hashmap_create(int sizeof_value)
{
    ark_Hashmap* hm = malloc(sizeof(ark_Hashmap));
    hm->size = 0;
    hm->hashFunction = djb2;
    hm->loadFactor = ARK_HASHMAP_DEFAULT_LOAD_FACTOR;
    hm->pair = ark_Pair_create(sizeof(const char*) , sizeof_value);
    hm->capacity = ark_Pair_capacity(hm->pair);
}

void ark_Hashmap_insert(ark_Hashmap* hm , const char* key , void* val)
{
    
}

int ark_Hashmap_remove(ark_Hashmap* hm , const char* key);
void ark_Hashmap_setHashFunction(ark_Hashmap* hm , uint64_t (*hash_function)(const char*));
void ark_Hashmap_destroy(ark_Hashmap* hm);

void* ark_Hashmap_get(ark_Hashmap* hm , const char* key);
