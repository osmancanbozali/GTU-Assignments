//Required library
#include <stdio.h>

/* (Part 1)
*  Get three numbers from user
*  Find median of them using only 
*  single conditional if-else statements
*/
void find_median() {
    // Declare variables for integers
    int num1, num2, num3, median;

    // Get integers from user
    printf("Enter 3 integers: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    // Find median
    if (num1 > num2) {
        if (num1 < num3) {
            median = num1;
        }
        else {
            if (num2 > num3) {
                median = num2;
            }
            else {
                median = num3;
            }
        }  
    }
    else {
        if (num2 < num3) {
            median = num2;
        }
        else {
            if(num3 > num1) {
                median = num3;
            }
            else {
                median = num1;
            }
            }  
    }

    // Print median value
    printf("Median number is: %d",median);
}

/* (Part 2)
*  Get three exam scores from user
*  Find equivalent letter grades for each
*  score using switch statements
*  Print the letter notes with average of scores
*/
void letter_note() {
    // Declare variables for exam scores and average
    double score1, score2, score3, average;

    // Get scores from user
    printf("Enter your scores: ");
    scanf("%lf %lf %lf", &score1, &score2, &score3);

    // Calculate average of scores
    average =  (score1+score2+score3) / 3  ;

    // Floor numbers to interval points
    score1= score1 - ((int)score1 % 10);
    score2= score2 - ((int)score2 % 10);
    score3= score3 - ((int)score3 % 10);

    // Print letter notes and average
    printf("Your letter grades are");

    // Find first score's letter note
    switch ((int)score1) {
    case 100:
        printf(" A+");
        break;

    case 90:
        printf(" A+");
        break;
    
    case 80:
        printf(" A");
        break;
    
    case 70:
        printf(" B+");
        break;
    
    case 60:
        printf(" B");
        break;
    
    case 50:
        printf(" C");
        break;
    
    case 40:
        printf(" D");
        break;
    
    default:
        printf(" F");
        break;
    }
    // Find second score's letter note
    switch ((int)score2) {
    case 100:
        printf(" A+");
        break;
        
    case 90:
        printf(" A+");
        break;
    
    case 80:
        printf(" A");
        break;
    
    case 70:
        printf(" B+");
        break;
    
    case 60:
        printf(" B");
        break;
    
    case 50:
        printf(" C");
        break;
    
    case 40:
        printf(" D");
        break;
    
    default:
        printf(" F");
        break;
    }
    // Find third score's letter note
    switch ((int)score3) {
    case 100:
        printf(" A+");
        break;
        
    case 90:
        printf(" A+");
        break;
    
    case 80:
        printf(" A");
        break;
    
    case 70:
        printf(" B+");
        break;
    
    case 60:
        printf(" B");
        break;
    
    case 50:
        printf(" C");
        break;
    
    case 40:
        printf(" D");
        break;
    
    default:
        printf(" F");
        break;
    }
    // Print average
    printf(" with an %.1f average", average);
}

/* (Part 3)
*  Get two numbers and a result from user
*  Perform 4 basic arithmetic operations
*  Compare correct result with user's result
*  Give feedback whether it is true or not
*/
void correctness_check() {
    // Declare variable for operation selection
    char operation = 'o';
    // Declare variables for numbers and results
    int num1, num2, uresult, rresult;

    // Get operation from user
    printf("Enter an arithmetic operation (+,-,*,/): ");
    scanf(" %c", &operation);
    
    // Get numbers and result from user
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    printf("Result: ");
    scanf("%d", &uresult);

    // Find real result with selected operation
    switch (operation)
    {
    case '+':
        rresult = num1 + num2;
        break;
    case '-':
        rresult = num1 - num2;
        break;
    case '*':
        rresult = num1 * num2;
        break;
    case '/':
        rresult = num1 / num2;
        break;
    }

    // Check correctness and print it
    if(uresult == rresult) {
        printf("Bravo, correct answer!\n");
    }
    else {
        printf("Wrong answer, try again.\n");
    }

}
int main() {
    // Run parts one by one
    printf("**************(PART 1)**************\n");
    find_median();
    printf("\n**************(PART 2)**************\n");
    letter_note();
    printf("\n**************(PART 3)**************\n");
    correctness_check();
    return 0;
}
