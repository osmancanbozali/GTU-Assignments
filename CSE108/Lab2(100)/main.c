// Required libraries (compile with -lm tag due to added libraries)
#include <stdio.h>
#include <math.h> // sqrt()

// Define constant for pi value
#define PI 3.14

/* (Part 1)
*  Get required properties of cube,
*  rectangular prism, sphere, cone
*  Calculate and print surface area
*  and volume of each.
*/
void area_vol_calculator() {
    // Declare possible needed values for calculations
    int length, width, height, radius;
    // Declare variables for results
    double area, volume;

    /* Get cube's properties
    *  Calculate and print area and volume
    */
    printf("Enter the edge length for cube: ");
    scanf("%d", &length);
    area = 6* (length*length);
    volume = (length*length*length);
    printf("Surface Area: %.2f, Volume: %.2f\n\n", area, volume);

    /* Get rectangular prism's properties
    *  Calculate and print area and volume
    */
    printf("Enter side length for rectangular prism: ");
    scanf("%d", &length);
    printf("Enter side width: ");
    scanf("%d", &width);
    printf("Enter side height: ");
    scanf("%d", &height);
    area = 2*((length*width)+(length*height)+(width*height));
    volume = length * width * height;
    printf("Surface Area: %.2f, Volume: %.2f\n\n", area, volume);

    /* Get sphere's properties
    *  Calculate and print area and volume
    */
    printf("Enter the radius for sphere: ");
    scanf("%d", &radius);
    area = 4 * PI * (radius * radius);
    volume = (4 * (PI * (radius * radius * radius))) / 3;
    printf("Surface Area: %.2f, Volume: %.2f\n\n", area, volume);

    /* Get cone's properties
    *  Calculate and print area and volume
    */
    printf("Enter the radius for cone: ");
    scanf("%d", &radius);
    printf("Enter the height: ");
    scanf("%d", &height);
    area = PI * radius * (radius + sqrt((radius*radius) + (height*height)));
    volume = (PI * (radius*radius) * height) / 3; 
    printf("Surface Area: %.2f, Volume: %.2f\n\n", area, volume);
}



/* (Part2)
*  Get weight and height value from user
*  Calculate Body Mass Index (BMI)
*  Print the BMI with classification
*/
void bmi_calculator() {
    // Declare variables for needed values
    double weight, height, bmi;

    // Get weight and height values from user
    printf("Please enter your weight (kg): ");
    scanf("%lf", &weight);
    printf("Please enter your height (m): ");
    scanf("%lf", &height);

    // Calculate BMI
    bmi = weight / (height*height);

    // Print result with classification
    if(bmi < 18.5) {
        printf("Your BMI is : %.2f, you are underweight.\n", bmi);
    }
    else if(bmi < 24.9) {
        printf("Your BMI is : %.2f, you are average weight.\n", bmi);
    }
    else if(bmi < 29.9) {
        printf("Your BMI is : %.2f, you are over weight.\n", bmi);
    }
    else if(bmi >= 30.0) {
        printf("Your BMI is : %.2f, you are obese.\n", bmi);
    }
    else {
        printf("Error while calculating BMI!\n");
    }
}

int main(){
    // Run parts one by one
    printf("**************(PART 1)**************\n");
    area_vol_calculator();
    printf("**************(PART 2)**************\n");
    bmi_calculator();
    return 0;
}
