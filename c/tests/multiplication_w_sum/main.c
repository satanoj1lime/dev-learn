#include <stdio.h>
#include <limits.h>

unsigned long f(int x){
    unsigned long result = ((unsigned long)x * x) / 4;
    return result;
}

int main(){
    unsigned long a, b, result;
    
    printf("What is the multiplicand :\n");
    if(scanf("%lu", &a) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("What is the multiplicator :\n");
    if(scanf("%lu", &b) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    result = f(a + b) - (a - b);
    printf("Your result is %lu\n", result);
    return 0;
}
/*
#include <stdio.h>

long double f(int x){
    x = (x * x) / 4;
    return (unsigned long)x;
};

int main(){
    long double a;
    long double b;
    long double result; 
    
    printf("What is the multiplicand:\n");
    scanf("%Lf", &a);

    printf("What is the multiplicator:\n");
    scanf("%Lf", &b);

    result = f(a + b) - (a - b);
    printf("Your result is %.3Lf", result);
    return 0;
}
*/
