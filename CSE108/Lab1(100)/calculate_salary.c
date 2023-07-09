/* Program that gets age and years of experience
*  values from user and calculates salary by
*  the lookup table in the pdf file (Part 3)
*/

// Required library
#include <stdio.h>

int main() {
    
    // Declare variables for age and yoe
    int age, exp;
    // Initial salary value
    int salary =0;

    // Get age and yoe from user
    printf("\nPlease enter the employer's age: ");
    scanf("%d", &age);
    printf("\nPlease enter the employer's year of experience: ");
    scanf("%d", &exp);

    // Determine salary
    if(age < 20 && age>=0) {
        if(exp >= 0 && exp <= 10) {
            salary = 10000;
        }
        else {
            // Error if yoe >= 10 or yeo < 0
            printf("\nError!\n");
        }
    }
    else if(age >= 20 && age <= 50) {
        if(exp >= 0 && exp <= 10) {
            salary = 15000;
        }
        else if(exp >= 10) {
            salary = 20000;
        }
        else {
            // Error if yoe < 0
            printf("\nInvalid years of experience.");
        }
    }
    else if(age > 50) {
        if(exp >= 0 && exp <= 10) {
            salary = 20000;
        }
        else if(exp >= 10) {
            salary = 25000;
        }
        else {
            // Error if yoe < 0
            printf("\nInvalid years of experience.");
        }
    }
    else {
        // Error if age < 0
        printf("\nInvalid age.");
    }

    // Print salary if it is successfully determined
    if(salary != 0) {
        printf("\nSalary successfully calculated.\nSalary : %d\n", salary);
    }

    return 0;
}
