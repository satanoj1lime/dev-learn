#include <stdio.h>
#include <string.h>

void hello(){
    // int *gentilico;
    char str[32];
    printf("Qual o seu gentilico?\n");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
    printf("sua frase de efeito é:\n eu sou %s carai!", str);
}

int main(){
    hello();
    return 0;
}
