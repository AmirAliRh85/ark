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
    int* x = malloc(sizeof(int));
    int* y = malloc(5 * sizeof(int));
    double* d = malloc(sizeof(double));


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

    ark_DynamicArray_reserve(da , 200);
    printdArrayInfo(da , -1);

    ark_DynamicArray_destroy(da);

    #if 0
    // Stack
    ark_Stack* s = ark_Stack_create();

    *x = 5;
    ark_Stack_push(s , x);
    printf("%i , size: %i\n" , *(int*)ark_Stack_top(s) , ark_Stack_size(s));
    
    y[0] = 3;
    ark_Stack_push(s , y);
    printf("%i , size: %i\n" , *(int*)ark_Stack_top(s) , ark_Stack_size(s));
    
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
    #endif
    /*______________________________________________________________________________________________________*/

    ark_Queue* q = ark_Queue_create();

    *x = 10;
    y[0] = 1;
    y[1] = 2;
    y[2] = 3;
    y[3] = 4;
    y[4] = 5;
    *d = 12345.6789;

    ark_Queue_push(q , x);
    ARK_ASSERT(*(int*)ark_Queue_front(q) == 10 , "queue push test");
    ARK_ASSERT(ark_Queue_size(q) == 1 , "queue size test");

    printf("%i\n" , *(int*)ark_Queue_front(q));
    
    ark_Queue_push(q , y);
    ARK_ASSERT(ark_Queue_size(q) == 2 , "queue size test");

    ark_Queue_pop(q);
    ARK_ASSERT(ark_Queue_size(q) == 1 , "queue size test");
    
    int* y_ptr = ark_Queue_front(q);
    
    printf("%i %i %i %i %i \n" , *(y_ptr + 0) , y_ptr[1] , y_ptr[2] , y_ptr[3] , y_ptr[4]);

    ARK_ASSERT(!ark_Queue_isEmpty(q) , "queue isEmpty test");
    ark_Queue_pop(q);
    ARK_ASSERT(ark_Queue_isEmpty(q) , "queue isEmpty test");
    ARK_ASSERT(ark_Queue_size(q) == 0 , "queue isEmpty test");

    ark_Queue_push(q , d);
    ARK_ASSERT(ark_Queue_size(q) == 1 , "queue size test");
    ARK_ASSERT(*(double*)ark_Queue_front(q) == *d , "queue front test");
    ARK_ASSERT((double*)ark_Queue_front(q) == d , "queue front test");

    ark_Queue_destory(q);

    free(x);
    free(y);
    free(d);

    ark_Gapbuffer* gb = ark_Gapbuffer_create(32 , sizeof(char));
    ark_Gapbuffer_info(gb);
    char ch = 'a';
    ark_Gapbuffer_insert(gb , &ch);
    ch = 'l';
    ark_Gapbuffer_insert(gb , &ch);
    ch = 'i';
    ark_Gapbuffer_insert(gb , &ch);
    ch = '5';
    ark_Gapbuffer_insert(gb , &ch);
    ark_Gapbuffer_moveLeft(gb);
    ark_Gapbuffer_moveLeft(gb);
    ark_Gapbuffer_moveLeft(gb);
    ark_Gapbuffer_remove(gb);
    ch = 'A';
    ark_Gapbuffer_insert(gb , &ch);

    ark_Gapbuffer_info(gb);

    for (int i = 0 ; i < ark_Gapbuffer_getGapStart(gb) ; i++)
    {
        putchar(*(char*)ark_Gapbuffer_at(gb , i));
    }

    // printf("seperator\n");
    
    for (int i = ark_Gapbuffer_getGapEnd(gb) + 1 ; i < 32 ; i++)
    {
        putchar(*(char*)ark_Gapbuffer_at(gb , i));
    }


    ark_Gapbuffer_destroy(gb);
}