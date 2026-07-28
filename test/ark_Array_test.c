#include "../ark.h"



int main()
{
    int a = 5;
    int b = 3;
    int c = 10;

    ark_Array* arr = ark_Array_create(sizeof(int) , 32);

    if (arr == NULL)
        printf("Error\n");

    ark_Array_insert(arr , 0 , &a);
    ark_Array_insert(arr , 1 , &b);
    ark_Array_insert(arr , 4 , &c);

    for (int i = 0 ; i < 32 ; i++)
    {
        printf("%i , %0x\n" , i , ark_Array_at(arr , i));
    }

    printf("a: %i\n" , *(int*)ark_Array_at(arr , 0));
    printf("b: %i\n" , *(int*)ark_Array_at(arr , 1));
    printf("c: %i\n" , *(int*)ark_Array_at(arr , 4));

    ark_Array_destroy(arr);

    return 0;
}