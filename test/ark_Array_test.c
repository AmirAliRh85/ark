#include "../ark.h"



int main()
{
    int a[] = {8 , 7 , 6 , 5 , 4 , 3 , 2 , 1};

    ark_Array* arr = ark_Array_create(sizeof(int) , 8);

    if (arr == NULL)
        printf("Error\n");

    ark_Array_insert(arr , 7 , &a[7]);
    ark_Array_insert(arr , 6 , &a[6]);
    ark_Array_insert(arr , 5 , &a[5]);
    ark_Array_insert(arr , 4 , &a[4]);
    ark_Array_insert(arr , 3 , &a[3]);
    ark_Array_insert(arr , 2 , &a[2]);
    ark_Array_insert(arr , 1 , &a[1]);
    ark_Array_insert(arr , 0 , &a[0]);

    _ark_Array_dbg(arr , int);

    ark_Array_resize(arr , 20);
    ARK_ASSERT(ark_Array_capacity(arr) == 20 , "capacity should be 20");
    // _ark_Array_dbg(arr , int);

    ark_Array_resize(arr , 6);
    ARK_ASSERT(ark_Array_capacity(arr) == 6 , "capacity should be 6");
    // _ark_Array_dbg(arr , int);

    ark_Array_resize(arr , 16);
    ARK_ASSERT(ark_Array_capacity(arr) == 16 , "capacity should be 16");
    // _ark_Array_dbg(arr , int);

    ark_Array* arr2 = ark_Array_slice(arr , 1 , 5);
    _ark_Array_dbg(arr2 , int);

    ark_Array_concat(arr , arr2);
    ARK_ASSERT(ark_Array_capacity(arr) == 20 , "capacity should be 16");
    _ark_Array_dbg(arr , int);
    // _ark_Array_dbg(arr2 , int);

    ark_Array_destroy(arr);
    ark_Array_destroy(arr2);
}