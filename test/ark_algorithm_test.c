#include "../ark.h"

typedef struct OBJ
{
    int id;
    const char* name;
} OBJ;

void printdArrayInfo(ark_DynamicArray* da , int idx)
{
    if (idx < 0)
        printf("[dArray] size: %i , capacity: %i\n" , ark_DynamicArray_size(da) , ark_DynamicArray_capacity(da));
    else
        printf("[dArray] address: %0x , size: %i , capacity: %i\n" , ark_DynamicArray_at(da , idx) , ark_DynamicArray_size(da) , ark_DynamicArray_capacity(da));
}

int main()
{
    // DynamicArray
    ark_DynamicArray* da = ark_DynamicArray_create(sizeof(OBJ));
    printdArrayInfo(da , -1);
    printdArrayInfo(da , 0);
    
    ark_DynamicArray_push(da , &(OBJ){23 , "line 23"});
    ark_DynamicArray_push(da , &(OBJ){30 , "line 30"});
    ark_DynamicArray_push(da , &(OBJ){1 , "line 1"});
    ark_DynamicArray_push(da , &(OBJ){2 , "line 2"});
    ark_DynamicArray_push(da , &(OBJ){3 , "line 3"});

    printdArrayInfo(da , 2);
    OBJ* obj1 = ark_DynamicArray_at(da , 2);
    ARK_ASSERT((obj1->id == 1) && !strcmp(obj1->name , "line 1") , "dArrat at test");

    int index = ark_DynamicArray_find(da , obj1);
    ARK_ASSERT((index == 2) , "dArray find test");

    ark_DynamicArray_shrink(da);
    printdArrayInfo(da , -1);
    ARK_ASSERT(ark_DynamicArray_capacity(da) == 5, "dArray shrink failed");

    ark_DynamicArray_pop(da);
    ark_DynamicArray_pop(da);
    ark_DynamicArray_pop(da);

    obj1 = ark_DynamicArray_at(da , 0);
    ARK_ASSERT((obj1->id == 23) , "dArray pop test failed");

    printdArrayInfo(da , -1);

    ark_DynamicArray_remove(da , 0);
    printdArrayInfo(da , -1);

    obj1 = ark_DynamicArray_at(da , 0);
    ARK_ASSERT((obj1->id == 30) , "dArray remove test failed");

    ark_DynamicArray_destroy(da);

    // Stack
    ark_Stack* s = ark_Stack_create();

    int* x = malloc(4);
    *x = 5;
    ark_Stack_push(s , x);
    printf("%i , size: %i\n" , *(int*)ark_Stack_top(s) , ark_Stack_size(s));
    
    int* y = malloc(20);
    y[0] = 3;
    ark_Stack_push(s , y);
    printf("%i , size: %i\n" , *(int*)ark_Stack_top(s) , ark_Stack_size(s));
    
    double* d = malloc(8);
    *d = 5.555;
    ark_Stack_push(s , d);
    printf("%.2f , size: %i\n" , *(double*)ark_Stack_top(s) , ark_Stack_size(s));

    ark_Stack_pop(s);
    printf("size: %i\n" , ark_Stack_size(s));
    ark_Stack_pop(s);
    printf("size: %i\n" , ark_Stack_size(s));

    printf("%i , size: %i\n" , *(int*)ark_Stack_top(s) , ark_Stack_size(s));
    
    ark_Stack_pop(s);
    printf("size: %i\n" , ark_Stack_size(s));

    ark_Stack_destroy(s);
}