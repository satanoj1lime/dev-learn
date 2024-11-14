#include <stdio.h>

void print_cube(int size) {
	    // Print top face
    for( int i = 0; i < size; i++ ){
        printf(" ");
        for( int j = 0; j < size; j++ ){
            printf("* ");
        }
        printf("\n");
    }
    // Print middle face
    for( int i = 0; i < size; i++ ){
        for( int k = 0; k < size; k++){
	    printf("* ");
        }
	for( int j = 0; j < size; j++){
	    printf(" ");
        }
	for( int k = 0; k < size; k++){
	    printf(" ");
        }
	printf("\n");
    }
    // Print bottom face
    for( int i = 0; i < size; i++ ){
        printf(" ");
        for( int j = 0; j < size; j++ ){
            printf("* ");
        }
    printf("\n");
    }
}

int main(){
    int size;
    printf("Enter cube size: ");
    scanf("%d", &size);
    print_cube(size);
    return 0;
}
