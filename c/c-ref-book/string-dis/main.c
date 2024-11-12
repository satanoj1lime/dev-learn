#include <stdio.h>

/* This program cover how string are stored in memory */

/* 
    // Some good examples if it is writable or not (just for reference)
    char p1[] = "Always writable";
    char *p2 = "Possibly not writable";
    const char p3[] = "Never writable in standard C"; 
    // They are all pointers to a character array, but they differ in writability.
*/

char *string1, *string2;

int main(){
    string1 = "abcd"; string2 = "abcd";

    if (string1 == string2)
        printf("The strings are the same and shared in memory adress!\n");
    else printf("The strings are not the same and not shared in memory adress!\n");
    
    string1[0] = '1';

    if (*string1 == '1')
        printf("Strings are writable!\n");
    else printf("Strings are not writable\n");
    return 0;
}
