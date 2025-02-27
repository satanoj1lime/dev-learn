#include <stdio.h>

long double A(long double R){
    long double n = 3.14159; 
    long double result = ((long double)n * (R * R)); 
    return result;
}

int main(){
    // long double A = n.R^2
    // n = 3.14159
    // R is the input value
    long double R;
    scanf("%Lf", &R); 
    long double result = A(R);
    printf("A=%.4Lf\n", result);
    return 0;
}
