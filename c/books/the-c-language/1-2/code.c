#include <stdio.h>

int main(){
    printf("Printing escape sequences:\n");
    printf("Alert character: \\a \aaaaa\n");    
    printf("Backspace: \\b \b a a a a\n");
    printf("Formfeed: \\f \faaaa aaaa aaaa aaaa\n");
    printf("Newline: \\n \n");
    printf("Carriage return: \\r \raaaa\raaaa\n");
    printf("Horizontal tab: \\t \taaaa\taaaa\n");
    printf("Vertical tab: \\v \vaaaa aaaa\vaaaa\n");
    printf("Backslash: \\ \n");
    printf("Question mark: \? \n");
    printf("Octal number: \001 \n");
    printf("Hexadecimal: \xff \n");
    return 0;
}
