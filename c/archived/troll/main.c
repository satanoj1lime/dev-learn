#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    while(1){
        printf("Russian Roulette Game\nChoose a number starting from 1 to 6:\n");
        int choice;
        int bullet = rand() % 6 + 1;
        /*printf("Random value on [0,%d]: %d\n", RAND_MAX, bullet);*/
        scanf("%d", &choice);
        if(choice == bullet){
            printf("You are safe!\n");
        }else if (choice < 1 || choice > 6){
            printf("Invalid choice!\n\n");
            continue;
        }else{
            printf("Deleting. . . (C:\\Windows\\System32)\n");
            break;
        }
    }
    return 0;
}