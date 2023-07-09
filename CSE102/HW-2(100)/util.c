// Required Libraries
#include <stdio.h>
#include "util.h"

// PART 1

/* Determine whether the year is leap or not 
*  Leap --> return 1 , not leap --> return 0
*/
void leap_check(int year) {
    /* Rules for leap year
    *  1) Must be divisible by 4
    *  2) If it is divisible by 100, it must be divisible by 400 also
    *  3) If it is divisible with 400, it must not be divisible by 4000 
    *  Determine by the rules and print whether the year is leap or not
    */
    if(year % 4 == 0) {
        if(year % 100 == 0 && year % 400 != 0) {
            printf("%d is not a leap year", year);
        }
        else if(year % 400 ==0 && year % 4000 ==0) {
           printf("%d is not a leap year", year); 
        }
        else {
            printf("%d is a leap year", year);
        }
    }
    else {
        printf("%d is not a leap year", year);
    }
}

// Get year from user and print the leap state
void leap_year() {
    // Declare variable for year value
    int year;

    // Get year from user
    printf("\nPlease enter a year: ");
    scanf("%d", &year);
    // Determine and print result
    leap_check(year);

} // END OF PART 1

// PART 2

// Arrange digit counts according to m and n values and print result
void scientific_print(int m, int n, long double result) {
    int epower = 0;
    // Go back to all decimal
    while (result > 1.0) {
        result/=10.0;
        epower++;        
    }
    // Arrange before decimal point digit count to m
    for (int i = 0; i < m; i++) {
        result*=10.0;
        epower--;
    }
    // Arrange after decimal point digit count to n
    for (int i = 0; i < n; i++) {
        result/=10.0;
        epower++;
    }  
    // Print the arranged number with e power;
    printf("%.*Lfe%d",n,result,epower);
}

/* Get two numbers from user
*  sum them and print "num1+num2= "
*  Return result
*/
long double summation() {
    // Declare variables for numbers and result
    long double num1,num2,result;
    // Get the numbers from user for calculations
    printf("Enter the first operand: ");
    scanf("%Lf", &num1);
    printf("Enter the second operand: ");
    scanf("%Lf", &num2);
    // Calculate result
    result = num1 + num2;
    // Print the result
    printf("%Lf+%Lf= ",num1,num2);
    return result;
}

/* Get two numbers from user
*  subtract them and print "num1-num2= "
*  Return result
*/
long double subtraction() {
    // Declare variables for numbers and result
    long double num1,num2,result;
    // Get the numbers from user for calculations
    printf("Enter the first operand: ");
    scanf("%Lf", &num1);
    printf("Enter the second operand: ");
    scanf("%Lf", &num2);
    // Calculate result
    result = num1 - num2;
    // Print the result
    printf("%Lf-%Lf= ",num1,num2);
    return result;
}
/* Get two numbers from user
*  multiply them and print "num1*num2= "
*  Return result
*/
long double multiplication() {
    // Declare variables for numbers and result
    long double num1,num2,result;
    // Get the numbers from user for calculations
    printf("Enter the first operand: ");
    scanf("%Lf", &num1);
    printf("Enter the second operand: ");
    scanf("%Lf", &num2);
    // Calculate result
    result = num1 * num2;
    // Print the result
    printf("%Lf*%Lf= ",num1,num2);
    return result;
}
/* Get two numbers from user
*  divide them and print "num1/num2= "
*  Return result
*/
long double division() {
    // Declare variables for numbers and result
    long double num1,num2,result;
    // Get the numbers from user for calculations
    printf("Enter the first operand: ");
    scanf("%Lf", &num1);
    printf("Enter the second operand: ");
    scanf("%Lf", &num2);
    // Calculate result
    result = num1 / num2;
    printf("%Lf/%Lf= ",num1,num2);
    return result;
}
/* Get two numbers from user
*  take modulus and print "num1%num2= "
*  Return result
*/
long double modulus(){
    long double num1,num2,result;
    // Get the numbers from user for calculations
    printf("Enter the first operand: ");
    scanf("%Lf", &num1);
    printf("Enter the second operand: ");
    scanf("%Lf", &num2);
    // Calculate result
    result = num1-((int)(num1/num2))*num2;
    printf("%Lf%%%Lf= ",num1,num2);
    return result;
}
/* Get a number from user
*  Compute factorial and print "num! = "
*  Return result
*/
long double factorial() {
    long double num, result;
    // Get the number from user for calculations
    printf("Enter the operand: ");
    scanf("%Lf", &num);
    while (num < 0.0) {
        printf("Number can not be negative, insert a positive number: ");
        scanf("%Lf", &num);
    }
    // Calculate result
    result =1;
        for (int i = 2; i <= (int)num; i++) {
            result = result*i;
        }
        printf("%.0Lf! = ",num);
    return result;
}
/* Get two numbers from user
*  Compute num1^num2 and print "num1^num2= "
*  Return result
*/
long double exponentiation() {
    long double num1, num2, result;
    int negative_flag =0;
    // Get the numbers from user for calculations
    printf("Enter the first operand: ");
    scanf("%Lf", &num1);
    printf("Enter the second operand: ");
    scanf("%Lf", &num2);
    // Check negativity
    if (num2 <0.0) {
        num2 = -num2;
        negative_flag =1;
    }
    // Calculate result
    result = 1;
    for (int i = 0; i < (int)num2; i++) {
        result *= num1;
    }
    // Convert the result if num2 negative
    if (negative_flag) {
        result = 1.0/result;
        num2 = -num2;
    }
    printf("%Lf^%.0Lf= ",num1,num2);
    return result;
}

/* Determine the format type
*  Determine the operation and perform it
*  (Main body of Part 2)
*/
void enhanced_calc() {
    // Declare variables for format and operation selection
    char format, operation;

    // Get format type from user
    printf("\nEnter the format of output (S or I) : ");
    scanf(" %c", &format);

    if(format == 'S') {
        // Declare variables for digit counts
        int n,m;

        // Get m and n values from user
        printf("Enter m and n values: ");
        scanf("%d %d",&m,&n);

        // Warn about n>m situation and get appropriate values for them
        while(n>=m || n<=0 || m<=0 ) {
            printf("Error! Please enter a valid entry:  ");
            scanf("%d %d",&m,&n);
        }

        // Get the operation from user
        printf("Enter the operation (+,-,*,/,%%,!,^): ");
        scanf(" %c", &operation);

        // Determine the operation which user is inserted
        switch (operation)
        {
        case '+':
            scientific_print(m,n,summation());
            break;
        case '-':
            scientific_print(m,n,subtraction());
            break;
        case '*':
            scientific_print(m,n,multiplication());
            break;
        case '/':
            scientific_print(m,n,division());
            break;
        case '%':
            scientific_print(m,n,modulus());
            break;
        case '!':
            scientific_print(m,n,factorial());
            break;
        case '^':
            scientific_print(m,n,exponentiation());
            break;
        default:
            // Print error message if operation can not found
            printf("Error, invalid operation!");
            break;
        }
    }

    else if (format == 'I') {
        // Get the operation from user
        printf("Enter the operation (+,-,*,/,%%,!,^): ");
        scanf(" %c", &operation);

        // Determine the operation
        switch (operation)
        {
        case '+':
            printf("%ld",(long int)summation());
            break;
        case '-':
            printf("%ld",(long int)subtraction());
            break;
        case '*':
            printf("%ld",(long int)multiplication());
            break;
        case '/':
            printf("%ld",(long int)division());
            break;
        case '%':
            printf("%ld",(long int)modulus());
            break;
        case '!':
            printf("%ld",(long int)factorial());
            break;
        case '^':
            printf("%ld",(long int)exponentiation());
            break;
        default:
            // Print error message if operation can not found
            printf("Error, invalid operation!");
            break;
        }
    }
    else {
        // Print error message if format can not found
        printf("Error, invalid format!");
    }
    
} // END OF PART 2

// PART 3

// Calculate final grade and print
void calc_fgrade(int exam1, int exam2, int exam3, int asgmt1, int asgmt2) {
     // Declare and calculate final grade
    double fgrade = (((exam1 + exam2 + exam3)/3) * 0.6) + (((asgmt1 + asgmt2) / 2) * 0.4);

    // Print the final grade
    printf("Final grade: %.1f", fgrade);
    
    // Check passed/failed conditions and print it
    if(fgrade < 60.0) {
        printf(" Failed!\n");
    }
    else {
        printf(" Passed!\n");
    }
}

/* Get exam and assignment grades from user
*  Calculate and print final grade with passed/failed conditions
*/
void grade_calc() {
    // Declare variables for exam grades
    int exam1, exam2, exam3;
    // Declare variables for assignments grades
    int asgmt1, asgmt2;

    // Get grades from user
    printf("\nEnter 3 exam grades for student: ");
    scanf("%d %d %d", &exam1, &exam2, &exam3);

	// Check >100 and <0 situations for each exam grade
	while (exam1 > 100 || exam1 < 0) {
		printf("Exam grades can not be larger than 100 or smaller than 0"
		"\nPlease insert correct exam grade for first exam: ");
		scanf("%d", &exam1);
	}
	while (exam2 > 100 || exam2 < 0) {
		printf("Exam grades can not be larger than 100 or smaller than 0"
		"\nPlease insert correct exam grade for second exam: ");
		scanf("%d", &exam2);
	}
	while (exam3 > 100 || exam3 < 0) {
		printf("Exam grades can not be larger than 100 or smaller than 0"
		"\nPlease insert correct exam grade for third exam: ");
		scanf("%d", &exam3);
	}
	
	// Get assignment grades from user
    printf("Enter 2 assignment grades for student: ");
    scanf("%d %d", &asgmt1, &asgmt2);
	
	// Check >100 and <0 situations for each assignment grade
	while (asgmt1 > 100 || asgmt1 < 0) {
		printf("Assignment grades can not be larger than 100 or smaller than 0"
		"\nPlease insert correct assignment grade for first asignment: ");
		scanf("%d", &asgmt1);
	}
	while (asgmt2 > 100 || asgmt2 < 0) {
		printf("Assignment grades can not be larger than 100 or smaller than 0"
		"\nPlease insert correct assignment grade for second assignment: ");
		scanf("%d", &asgmt2);
	}
    // Calculate and print final grade
    calc_fgrade(exam1,exam2,exam3,asgmt1,asgmt2);
} // END OF PART 3
