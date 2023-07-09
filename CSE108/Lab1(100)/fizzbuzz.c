/* Program that gets a number between 1 and 100
*  and prints out Fizz/Buzz/FizzBuzz by the conditions
*  specified from the pdf file by using only two
*  if-else statements (Part 1)
*/

// Required library
#include <stdio.h>

int main() {
    // Declare variable for number
    int num;

    // Get the number from user
    printf("\nPlease enter a value between 1 and 100: ");
    scanf("%d", &num);

    // Check fizz/buzz conditions and print result
    if(num % 3 == 0) {
        if(num > 5 && num < 50) {
            //Fizzbuzz
            printf("\nFizzBuzz\n");
        }
        else {
            //Fizz
            printf("\nFizz\n");
        }
    }
    else if(num > 5 && num < 50) {
        // Buzz
        printf("\nBuzz\n");
    }
    return 0;
}
