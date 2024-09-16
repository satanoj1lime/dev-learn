// Card count program
#include <stdio.h>
#include <stdlib.h>

int main() {
    char card_name[3]; // it's a array of 2 characters, not a string. the last character is always \0 (that is a null character, that prints nothing)  
                       // c reads an array like this: s = "shatner" as s = 's', 'h', 'a',...
                       // memorized in the memory like this: s h a t n e r \0 = s[0] s[1] s[2]...
    puts("Enter the card_name: "); // this function write a string followed by a new line  
    scanf("%2s", card_name); //read formated input
//  printf(""); this function write not formated output
// Those switch statements are better than 'if, elses', obviously can vary. (it depends by ur usage)
    int val = 0;
      switch(card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
          val = 10;
        case 'A':
          val = 11;
            break;
        default:
          val = atoi(card_name);
            break;
      } 

      // Check if the value is 3 to 6
      if ((val > 2) && (val < 7))
         puts("Count has gone up");

      // Otherwise check if the value was 10, J, Q or K and then output "...gone down"
      else if (val == 10)
      puts("Count has gone down");
      //  printf("The card value is: %i\n", val);

        return 0;
}