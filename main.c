#include <stdio.h>
#include <stdlib.h>


int main()
{
    const char* str1 = "hello world";
    const char* str2 = "hello world";
    printf("%0x , %s\n%0x , %s" , str1 , str1 , str2 , str2);
}