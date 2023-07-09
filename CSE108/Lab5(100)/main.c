#include <stdio.h>

// PART 1

// Get menu selection from user and return the selection
char get_selection() {
    char selection;
    printf("Enter your choice (1-3): ");
    scanf(" %c", &selection);
    return selection;
}
// Convert Celcius --> Fahrenheit
void celcius_to_fahr() {
    // Declare variables
    double cel, fahr;
    // Get celcius value from user
    printf("Enter the temperature value to convert: ");
    scanf("%lf", &cel);
    // Calculate fahrenheit
    fahr = cel*(9.0/5.0) + 32;
    // Print the result
    printf("%.2f Celcius = %.2f Fahrenheit\n",cel,fahr);
}
// Convert Fahrenjeit --> Celcius
void fahr_to_celcius() {
    // Declare variables
    double cel, fahr;
    // Get fahrenheit value from user
    printf("Enter the temperature value to convert: ");
    scanf("%lf", &fahr);
    // Calculate celcius
    cel = (fahr-32)*(5.0/9.0);
    // Print the result
    printf("%.2f Fahrenheit = %.2f Celcius\n",fahr,cel);
}
// Menu and main body for part 1
void temp_converter() {
    // Declare variable for menu selection
    char selection;
    do {
        // Print the menu
        printf("\nTemperature Conversion Menu\n"
        "1. Convert Celcius to Fahrenheit\n"
        "2. Convert Fahrenheit to Celcius\n"
        "3. Quit\n");
        // Get selection from user
        selection = get_selection();
        // Determine operation and perform
        switch (selection) {
        case '1':
            celcius_to_fahr();
            break;
        case '2':
            fahr_to_celcius();
            break;
        case '3':
            printf("Quitting..");
            break;
        default:
            printf("Invalid selection!\n");
            break;
        }
    } while (selection != '3');
} // END OF PART 1

// PART 2

// Calculate and return digit count of an integer
int digit_count(int num) {
    int count = 0;
    while (num > 0) {
        num/=10;
        count++;
    }
    return count; 
}
// Get number from user and print the reversed number
void reverse_integer() {
    // Declare variable for number
    int num, dcount;
    // Get number from user
    printf("\nEnter a number (3,4,5 digit): ");
    scanf("%d", &num);
    // Calculate digit count
    dcount = digit_count(num);

    // Get a number from user until the digit count is valid
    while (dcount < 3 || dcount > 5) {
        printf("Wrong digit count! Enter a valid number: ");
        scanf("%d",&num);
        dcount = digit_count(num);
    }

    // Reverse print the number
    printf("Reversed number: ");
    for (int i = 0; i < dcount; i++) {
        printf("%d", num%10);
        num/=10;
    }
} // END OF PART 2

// PART 3

// Get operation from user and return operation
char select_op() {
    // Declare variable for operation
    char op;
    // Get operation from user
    printf("Enter your choice: ");
    scanf(" %c", &op);
    // Return operation
    return op;
}
// Convert Decimal --> Binary
int convert_to_binary(int num) {
    // Declare variable for binary equilavent
    int binary =0;
    // Declare variable for digit management
    int digit =1;
    // Declare variable for remainder value
    int remainder;

    while (num > 0) {
        remainder = num%2; // Find remainder
        binary += remainder * digit; // Add to the binary with proper digit count
        num /= 2;
        digit *=10; // Increment digit count
    }
    return binary; // Return result
}
// Get a number from user and print decimal, binary, octal, hexadecial equilavents
void base_convertion() {
    // Declare a variable for number
    int num;
    // Get number from user
    printf("Enter a number: ");
    scanf("%d", &num);
    // Check negativity
    while (num < 0) {
        printf("Please enter a non-negative number: ");
        scanf("%d", &num);
    }
    // Print decimal equilavent
    printf("Decimal equivalent: %d\n",num);
    // Print binary equilavent
    printf("Binary equivalent: %d\n",convert_to_binary(num));
    // Print octal equilavent
    printf("Octal equivalent: %o\n",num);
    // Print hexadecimal equilavent
    printf("Hexadecimal equivalent: %X\n",num);
}
// Menu and main body of Part 3
void number_converter() {
    // Declare variable for selection
    char selection;
    do {
        // Print the menu
        printf("Menu:\n"
        "1. Convert a number to decimal, binary, octal, and hexadecimal\n"
        "2. Quit\n");
        // Get selection from user
        selection = select_op();
        // Determine selection
        switch (selection)
        {
        case '1':
            base_convertion();
            break;
        case '2':
            // Print quiting message
            printf("Quitting!..");
            break;
        default:
            // Print error message
            printf("Invalid selection!\n");
            break;
        }

    } while (selection != '2');  
} // END OF PART 3

int main() {
    // Run parts one by one
    printf("==========(Part 1)==========\n");
    temp_converter();
    printf("\n==========(Part 2)==========");
    reverse_integer();
    printf("\n==========(Part 3)==========\n");
    number_converter();
    return 0;
}
