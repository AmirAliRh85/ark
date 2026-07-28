#include "./ark.h"


int main()
{
    const char* first_key = "amirali";
    int first_val = 19;
    const char* second_key = "ali";
    int second_val = 17;
    const char* third_key = "reza";
    int third_val = 39;

    ark_Hashmap* hm = ark_Hashmap_create(sizeof(int));

    ark_Hashmap_insert(hm , first_key , &first_val);
    ark_Hashmap_insert(hm , second_key , &second_val);
    ark_Hashmap_insert(hm , third_key , &third_val);

    _ark_Hashmap_debug(hm);

    int* reza = (int*)ark_Hashmap_get(hm , "reza");

    printf("%0x\n" , reza);
    printf("%i\n" , *reza);

    ark_Hashmap_destroy(hm);
}