#include <stdio.h>
 
int main() {
     int A,B = 0;
     if(scanf("%d", &A) !=1 ) {
         printf("Presentation Error\n");
     };
     if(scanf("%d", &B) !=1 ) {
         printf("Presentation Error\n");
     };
     int X = A + B;
     printf("X = %d\n", X);
    return 0;
}
