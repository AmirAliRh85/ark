#include "ark.h"



int main()
{

    ark_Stack* s = ark_Stack_create();


    int* x = malloc(4);
    *x = 5;
    int* y = malloc(4);
    *y = 10;
    int* z = malloc(4);
    *z = 15;

    ark_Stack_push(s , x);
    int* a = ark_Stack_top(s);
    printf("%i\n" , *a);
    
    ark_Stack_push(s , y);
    a = ark_Stack_top(s);
    printf("%i\n" , *a);

    ark_Stack_push(s , z);
    a = ark_Stack_top(s);
    printf("%i\n" , *a);

    ark_Stack_pop(s);
    a = ark_Stack_top(s);
    printf("%i\n" , *a);

    ark_Stack_pop(s);
    a = ark_Stack_top(s);
    printf("%i\n" , *a);
    

    ark_Stack_destroy(s);

    char log[1024];
    log[0] = '\0';

    ark_MemoryManager* mm = ark_MemoryManager_create(log);
    
    int* t = ark_malloc(mm , 1024 , "array of int");
    char* c = ark_malloc(mm , 4096 , "char");

    ark_free(mm , t);
    ark_free(mm , t);
    ark_free(mm , c);

    // t = NULL;
    t = ark_malloc(mm , 16 , "4 int");

    ark_MemoryManager_destroy(mm);

    printf("%s" , log);

    return 0;
}