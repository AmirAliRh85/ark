#include "../ark.h"



int main()
{
    int a = 5;
    int b = 3;
    int c = 10;

    ark_Array* arr = ark_Array_create(32 , sizeof(int));
    
    ark_Array_insert(arr , &a , 0);
    ark_Array_insert(arr , &a , 1);
    ark_Array_insert(arr , &a , 4);

    for (int i = 0 ; i < 32 ; i++)
    {
        printf("%i , %0x\n" , i , ark_Array_at(arr , i));
    }

    ark_Array_destroy(arr);

    return 0;
}