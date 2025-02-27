// Card count program
#include <stdio.h>
#include <stdlib.h>

int main() {
		char card_name[3]; // array of 2 characters
		int count = 0;
		while (card_name[0] !='X') {
			puts("Enter the card_name: "); // this function write a string followed by a new line 
			scanf("%2s", card_name); //read formated input
			int val = 0;
			switch(card_name[0]) {
			case 'K':
			case 'Q':
			case 'J':
				val = 10;
				break;
			case 'A':
				val = 11;
				break;
			case 'X':
				continue;
			default:
			  val = atoi(card_name);
			  if ((val < 1) || (val > 10)) {
				puts("I don't understand that value!");
				continue;
			  }
	   } 
		if ((val > 2) && (val < 7)) { // Check if the value is 3 to 6
			count++;
		}
		else if (val == 10) {// Otherwise check if the value was 10, J, Q or K and then output "...gone down"
			count--;
		}
		printf("Current count %i\n", count);
	}
	return 0;
}