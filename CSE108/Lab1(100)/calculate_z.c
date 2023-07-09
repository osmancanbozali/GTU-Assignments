/* Program that get two decimal numbers 
*  x and y from user calculate Z value 
*  according to the given formula 
*  on pdf file (Part2)
*/

// Required library
#include <stdio.h>

int main() {
    // Declare variables for needed values
    double x,y,z,max;
    
    // Get x and y values from user
    printf("\n Please enter X value: ");
    scanf("%lf", &x);
    printf("\n Please enter Y value: ");
    scanf("%lf", &y);
    
    // Find maximum value
    max = x;
    if(y > max) {
        max = y;
    }

    // Calculate z value
    z = (x/y) + (max/(x+y));

    // Print the result
    printf("\nZ value is: %f\n",z); 

    return 0;
}
