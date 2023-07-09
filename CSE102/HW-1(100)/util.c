#include <stdio.h>
#include "util.h"

/* (Part 1)
*  Get two integers from user
*  Calculate greatest common divisor (GDC) of them
*/
void find_gcd() {
	// Declare number variables
	int num1,num2;
	int temp; // for switching operations

	// Get numbers from user
	printf("\nPlease insert first number: ");
	scanf("%d", &num1);
	printf("\nPlease insert second number: ");
	scanf("%d", &num2);

	/* Convert to absolute values if any negative
	*  since negativity does not matter while finding GCD
	*/
	if(num1 < 0) {
		num1 = -num1;
	}
	if(num2 < 0) {
		num2 = -num2;
	}

	// Find the greater number
	if(num2 > num1) {
		temp = num1;
		num1 = num2;
		num2 = temp;
	}

	// Print the algorithm step by step
	while(1) {
		printf("\n%d = %d * %d + %d", num1, num2, num1/num2, num1%num2);

		if(num1%num2 == 0) {
			// Print GCD
			printf("\nGCD: %d",num2);
			break;
		}
		else {
			// Swap numbers for next step
			temp = num1;
			num1 = num2;
			num2 = temp%num2;
		}
	}

}

/* (Part 2)
*  Get two numbers from user
*  Visualize and display their sums
*/
void visualize_sum() {
	// Declare number variables
	int num1, num2;
	
	// Get numbers from user
	printf("\nPlease insert first number: ");
	scanf("%d", &num1);
	printf("\nPlease insert second number: ");
	scanf("%d", &num2);

	// Visualize and print summation
	printf("\nFirst number : %d", num1);
	printf("\nSecond number: %d", num2);
	printf("\nResult:");
	printf("\n%12d\n%12d", num1,num2);
	printf("\n     +\n     -------");
	printf("\n%12d", (num1+num2));

}

/* (Part 3)
*  Get two numbers from user
*  Visualize and display their multiples
*/
void visualize_mul() {
    // Declare number variables
	int num1, num2, temp; // temp for switching operations
	int spaces = 14; // Declare space count to align numbers
	
	// Get numbers from user
	printf("\nPlease insert first number: ");
	scanf("%d", &num1);
	printf("\nPlease insert second number: ");
	scanf("%d", &num2);

	// Visualize and print multiplication
	printf("\nFirst number : %d", num1);
	printf("\nSecond number: %d", num2);
	printf("\nResult:");
	printf("\n%14d\n%14d", num1,num2);
	printf("\n    *\n    ----------\n");

	temp = num2; // Assign num2 to temp in order to find digit count

	// Align and print multiplication steps
	while(temp != 0) {
		printf("%*d\n",spaces, num1*(temp%10));
		temp = temp/10; // Decrease digit count
		spaces--; // Decrement space count for next step of multiplication
	}
	printf("    +\n    ----------\n");
	printf("%14d", (num1*num2));
}

/* (Part 4)
*  Get a number between 1-10
*  Determine if it is in correct interval
*  If so, check if it is above 5 or below/equal.
*/
void check_range() {
	// Declare number variable
	int num;
	// Get number from user
	printf("\nPlease insert an integer between 1 and 10 (exclusive): ");
	scanf("%d", &num);

	// Check validity
	if (num >= 10 || num <= 1) {
		printf("\nInvalid input\n");
	}
	else {
		// Check conditions
		if (num <= 5) {
			printf("\nThe integer you entered is less than or equal to 5.\n");
		}
		else {
			printf("\nThe integer you entered is greater than 5.\n");
		}
	}
}