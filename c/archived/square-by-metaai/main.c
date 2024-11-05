#include <stdio.h>

void print_square(int size) {
    for( int i = 0; i < size; i++ ){
        for( int j = 0; j < size; j++ ){
            printf("*");
    }
        printf("\n");
   }
}

int main(){
    int size;
    printf("Enter a square size: ");
    scanf("%d", &size);
    print_square(size);
    return 0;
}
