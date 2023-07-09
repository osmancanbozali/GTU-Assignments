#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A second fractional number: 13/11 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    /*
     TODO: Complete this code to read two fractional numbers and print their 
             multiplication and division results...
    */
    
    // First fractional number
    int num4, den4;
    // Second fractional number
    int num5, den5;
    // An unitilized fractional number
    int num6, den6;

    // Get first fractional number from user
    printf("\nPlease insert the first fractional number's numerator: ");
    scanf("%d",&num4);
    printf("Please insert the first fractional number's denominator: ");
    scanf("%d",&den4);

    // Check undefined case, loop until valid value
    while(den4 == 0) {
        printf("Denominator can not be zero. Please insert a non-zero number: ");
        scanf("%d",&den4);
    }
    printf("First fractional number is: ");
    fraction_print(num4,den4);

    // Get second fractional number from user
    printf("\n\nPlease insert the second fractional number's numerator: ");
    scanf("%d",&num5);
    printf("Please insert the second fractional number's denominator: ");
    scanf("%d",&den5);

    // Check undefined case, loop until valid value
    while(den5 == 0) {
        printf("Denominator can not be zero. Please insert a non-zero number: ");
        scanf("%d",&den5);
    }
    printf("Second fractional number is: ");
    fraction_print(num5,den5);
 
    // Perform arithmetic operations and print result
    printf("\nAddition: ");
    fraction_add(num4, den4, num5, den5, &num6, &den6);
    fraction_print(num6, den6);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num4, den4, num5, den5, &num6, &den6);
    fraction_print(num6, den6);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num4,den4,num5,den5,&num6,&den6);
    fraction_print(num6,den6);
    printf("\n");

    printf("Division: ");
    fraction_div(num4,den4,num5,den5,&num6,&den6);
    fraction_print(num6,den6);
    printf("\n");

    return 0;
}
