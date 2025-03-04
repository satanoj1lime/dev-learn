#include <stdio.h>

int main(){
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 18.5;
    fahr = lower;

        printf("Fahr table:\t Celsius table:\n");
    while(fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32);
        printf("%10.0f\t %13.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
