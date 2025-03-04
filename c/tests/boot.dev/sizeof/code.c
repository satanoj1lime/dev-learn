#include <stdio.h>
#include <stdbool.h>

int main(){
    printf("Size of char: %6.zu\n", sizeof(char));
    printf("Size of bool: %6.zu\n", sizeof(bool));
    printf("Size of int: %6.zu\n", sizeof(int));
    printf("Size of float: %6.zu\n", sizeof(float));
    printf("Size of double: %6.zu\n", sizeof(double));
    printf("Size of size_t: %6.zu\n", sizeof(size_t));
    return 0;
}
