#include <stdio.h>
#include <string.h>

void hello(){
    // int *gentilico;
    char str[32];
    printf("Qual o seu gentilico? ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
    printf("Então você é:\n %s disgra!", str);
}

int main(){
    hello();
    return 0;
}
