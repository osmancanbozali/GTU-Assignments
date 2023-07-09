#include <stdio.h>
// PART 1

/* Take numbers from user until -100 given as a input,
*  Store them in an array and return array count
*/
int take_nums(int *arr) {
    int count = 0;
    int num = 0;
    do {
        printf("Enter an integer and press enter, type -100 to exit: ");
        scanf("%d", &num);
        arr[count] = num;
        count++;
    } while (num != -100 && count != 100);  
    return count;  
}
// Print the numbers in the array each in a new line
void print_nums(int numbers[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d\n", numbers[i]);
    }  
}
/* Take two array pointers as parameter
*  Separate numbers in the array as even/odd
*  Store each numbers information at same index
*  in a second array as e/o
*/
void label_nums(int *narr, char *larr,int count) {
    for (int i = 0; i < count; i++){
        if (narr[i] % 2 == 0) {
            larr[i] = 'e';
        }
        else {
            larr[i] = 'o';
        }
    }   
}
/* Print numbers with labels
*/
void print_with_labels(int *narr, char *larr,int count) {
    for (int i = 0; i < count; i++) {
        printf("%d %c\n",narr[i],larr[i]);
    }  
}
// Main body of part1
void part1() {
    // Declare an array for numbers
    int numbers[100];
    // Declare an array for labels
    char labels[100];
    // Declare a variable for number count
    int count;

    // Take numbers from user and store number count value
    count = take_nums(numbers);
    // Print taken values
    print_nums(numbers, count);
    // Label taken values
    label_nums(numbers,labels,count-1);
    // Print numbers with labels
    print_with_labels(numbers,labels,count-1);
} // END OF PART 1

// PART 2
void part2() {
    // Declare a variable for file operations
    FILE *fp;
    // Declare a variable for line count and people count
    int lcount = 0, pcount = 0;
    // Declare a variable for team
    char team;
    // Declare a variable for average salary
    double average_salary= 0;
    // Open file
    fp = fopen("part2.txt", "r");
    // Get line count from first line
    fscanf(fp, "%d\n", &lcount);
    // Declare arrays
    int age[lcount];
    char occupation[lcount];
    double salary[lcount];
    char teams[lcount];
    // Get values and assign them to arrays
    for (int i = 0; i < lcount; i++) {
        fscanf(fp,"%d %c %lf %c",&age[i],&occupation[i],&salary[i],&teams[i]);
    }
    // Close file
    fclose(fp);
    
    // Ask user for a team
    printf("Please select a team: ");
    scanf(" %c", &team);
    // Find teams and add salary to average salary
    for (int i = 0; i < lcount; i++)
    {
        if (team == teams[i])
        {
            average_salary += salary[i];
            pcount++;
        }
    }

    // If no people supports input team, print a message
    if (pcount == 0) {
        printf("There are no fans of %c in the database!\n", team);
    }
    else {
        // Calculate average salary
        average_salary /= pcount;
        // Print average salary
        printf("Average salaries of fans of %c: %.1lf\n", team, average_salary);
    }
}
    

// Run parts one by one
int main() {
    printf("***************(PART 1)***************\n");
    part1();
    printf("\n***************(PART 2)***************\n");
    part2();
    return 0;
}