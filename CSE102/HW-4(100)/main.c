// Required Libraries
#include <stdio.h>
#include <time.h> // strftime() func
#include <stdlib.h> // rand() func

// Define S/P/S equilavents (PART 2)
#define STONE 1
#define PAPER 2
#define SCISSORS 3

// PART 1

/* Print the receipt from
*  receipt.txt file char by char
*/
void print_receipt() {
    // Declare variable for file operations
    FILE *fptr;
    // Open receipt file
    fptr = fopen("receipt.txt","r");
    // Declare a char variable, set initial value to the first char of receipt file
    char c = fgetc(fptr);
    //Skip a line before printing
    printf("\n");
    // Print receipt char by char
    while (c != EOF) {
        printf("%c",c);
        c = fgetc(fptr);
    }
    // Close file
    fclose(fptr);
}

/* Take total price as parameter
*  Check discount situations
*  Calculate discounts and final price
*  Write them to the receipt file
*/
void calculate_price(double total_price) {
    // Declare variable for student status
    char stu_status;
    // Declare variable for discounts
    double discount= 0;
    double stu_discount = 0;
    // Open receipt file
    FILE *fptr;
    fptr = fopen("receipt.txt", "a");
    // Print total price to the file
    fprintf(fptr,"Total:%*.2lf\n",28,total_price);

    // Ask wheter the user is student or not
    printf("Are you student? (Y/N): ");
    scanf(" %c", &stu_status);
    // Check invalid answer situation and get proper answer
    while (!((stu_status == 'Y' || stu_status == 'y') || (stu_status == 'N' || stu_status == 'n'))) {
        printf("Please enter valid answer (Y/N): ");
        scanf(" %c", &stu_status);
    }

    // If student, make 12.5% discount
    if (stu_status == 'Y' || stu_status == 'y') {
        // Calculate discount
        stu_discount = total_price/8.0; // 12.5/100 = 8.0

        // Print discount to the receipt
        fprintf(fptr,"Student discount:%*.2lf\n",17,-stu_discount);
    }

    // If total price > 150.0, make 10% discount
    if (total_price > 150.0) {
        // Calculate discount
        discount = total_price/10.0; // 10.0/100.0 = 10.0
        // Print discount to the receipt
        fprintf(fptr,"Discount:%*.2lf\n",25,-discount);
    }
    // Calculate total price after discounts  
    total_price -= (discount+stu_discount);

    fprintf(fptr,"------------------------------------\n");
    // Print total price without VAT
    fprintf(fptr,"Price:%*.2lf\n",28,total_price);
    // Calculate and add VAT (18%)
    total_price += total_price*18.0/100.0;
    // Print total price after VAT
    fprintf(fptr,"Price + VAT:%*.2lf\n",22,total_price);
    // Close file
    fclose(fptr);
}

/* Print restaurant menu with line numbers
*  Return dish count
*  NOTE: You can add new dishes to menu.txt file,
*  menu will be automatically updated when you
*  re-run the program
*/
int print_menu() {
    // Declare variable for dish count
    int dish_count =1;
    // Open menu file
    FILE *fptr;
    fptr = fopen("menu.txt","r");
    // Declare a variable for characters
    char c = '\n';
    // Skip first line
    while (fgetc(fptr) != '\n');
    // Print the menu
    printf("Yemek Listesi:");
    while (c != EOF) {
        // Print line number each line       
        if (c == '\n') {
            printf("\n%2d. ", dish_count);
            dish_count++;
        }
        // Get next character
        c = fgetc(fptr);
        // Skip spaces and prices
        if (c == ' ') {
            while(c != '\n' && c != EOF) {
                c = fgetc(fptr);
            }
        }
        else {
            printf("%c",c);
        }    
    } 
    // Return dish count
    return dish_count;
}

/* Find selected dish according to the dish number
*  Get dish name and price from menu file
*  Write serving count, dish name and 
*  total price of selected dish to the receipt file
*  Return total price of selected dish (price * serving)
*/
double write_to_receipt(int d_number, int serving) {
    // Declare variable for price value
    double price;
    // Declare variable for character count
    int c_count=0;
    // Open both menu and receipt files
    FILE *mptr, *rptr;
    mptr = fopen("menu.txt", "r");
    rptr = fopen("receipt.txt","a");
    // Pass to the selected dish's line
    for (int i = 0; i < d_number; i++) {
        while (fgetc(mptr) != '\n');
    }
    // Print serving count to the receipt file
    if (serving > 1) {
        fprintf(rptr,"%d* ",serving);
        int temp = serving;
        // Calculate used character count
        while (temp != 0) {
            temp/=10;
            c_count++;
        }
        c_count+=2;
    }
    // Print dish name to the receipt
    char c = getc(mptr);
    while (c != ' ') {
        fprintf(rptr,"%c",c);
        c = getc(mptr);
        c_count++;
    }
    // Get price value from menu file
    fscanf(mptr,"%lf", &price);
    // Print total price of selected dish (price*serving)
    fprintf(rptr,"%*.2lf\n", 34-c_count, price* serving);
    // Close both menu and receipt files
    fclose(mptr);
    fclose(rptr); 
    // Return total price of selected dish (price*serving)
    return price * serving;   
}

/* Ask the user for product and serving count
*  Send input data to write_to_receipt function
*  Get total price of selected dish and add to the
*  total count. When the user has done with selection,
*  call calculate_price function in order to calculate
*  and print the final price to the receipt
*/
void select_dish(int dish_count) {
    // Declare variable for dish number and serving count
    int dish,servings;
    // Declare variable for total price
    double total_price= 0.0;
    // Get selected dish and serving count from user
    while (servings != 0) {
        // Get selected dish
        printf("\nPlease choose a product (1-%d): ",dish_count-1);
        scanf("%d", &dish);
        // Check whether the number is on menu, If not; ask for valid number
        while (!(dish >0 && dish <dish_count)) {
            printf("Product not found, Please enter a valid product: ");
            scanf("%d", &dish);
        }
        // Get serving count
        printf("How many servings do you want? ");
        scanf("%d", &servings);
        // If servings < 0 , ask for valid serving count
        while (servings <0) {
            printf("Invalid serving count, Please enter a valid count: ");
            scanf("%d", &servings);
        }
        // If serving count is valid, calculate the total price of dish
        // Add to the total price and print them to the receipt
        if (servings != 0) {
            total_price += write_to_receipt(dish, servings);
            }
        }
        // Calculate final price
        calculate_price(total_price);
}

/* Initialize the header of the receipt
*  Print student number with the creation date & time
*/
void initialize_receipt() {
    // Get current computer date & time
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    time( &rawtime );
    info = localtime( &rawtime );
    strftime(buffer,80,"%d.%m.%Y/%H:%M",info);

    // Create and open the receipt file
    FILE *fptr;
    fptr = fopen("receipt.txt", "w");
    // Print student number and date & time
    fprintf(fptr,"220104004011        %s\n",buffer);
    // Initialize and print header info
    fprintf(fptr,"------------------------------------\n");
    fprintf(fptr,"Product                   Price (TL)\n");
    fprintf(fptr,"------------------------------------\n");
    // Close the file
    fclose(fptr);
}

/* Main body of Part 1
*  Run the functions in correct order
*/
void order_system() {
    initialize_receipt();
    select_dish(print_menu());
    print_receipt();
} // END OF PART 1

// PART 2

// Take choice from user, print the choice and return it
int user_choice() {
    // Declare variable for user selection
    int user_selection;
    //Print input message
    printf("Please make a choice!\n"
        "1: Stone 2: Paper 3: Scissors\n");
    // Get user selection
    scanf("%d", &user_selection);
    // Check validity
    while (!(user_selection > 0 && user_selection <4)) {
        printf("Please enter valid choice: ");
        scanf("%d", &user_selection);
    }
    // Determine selection and print it
    switch (user_selection) {
        case 1:
            printf("You choose Stone. ");
            break;
        case 2:
            printf("You choose Paper. ");
            break;
        case 3:
            printf("You choose Scissors. ");
            break;
        default:
            break;
    }
    // Return selection
    return user_selection;
}
// Create a random selection, print and return it
int com_choice() {
    // Random selection
    int com_selection = (rand() % 3) + 1;
    // Determine selection and print 
    switch (com_selection) {
        case 1:
            printf("I choose Stone. ");

            break;
        case 2:
            printf("I choose Paper. ");
            break;
        case 3:
            printf("I choose Scissors. ");
            break;
        default:
            break;
        }
        // Return selection
        return com_selection;

}
// Take choices as parameter, compare them and print result
void find_winner(int u_choice, int c_choice) {
    // Check wheter they are the same
    if (u_choice == c_choice) {
        printf("It's a tie!");
    }
    else {
        // Check all possibilites
        if (u_choice == STONE) {
            if (c_choice == PAPER) {
                printf("I won!");
            }
            else {
                printf("You won!");
            }
        }
        else if (u_choice == PAPER) {
            if (c_choice == SCISSORS) {
                printf("I won!");
            }
            else {
                printf("You won!");
            }   
        }
        else {
           if (c_choice == STONE) {
                printf("I won!");
            }
            else {
                printf("You won!");
            }   
        }
    }
    printf("\n");
}
// Loop the game until user selects N
void rps_gameloop() {
    // Declare variable for state
    char state = 'Y';
    while (state == 'Y' || state == 'y') {
        // Play round and print
        find_winner(user_choice(),com_choice());

        // Check wheter user want to continue or not
        printf("\nDo you want to play again? (Y/N): ");
        scanf(" %c", &state);
        // Control invalid selection
        while (!((state == 'Y' || state == 'y') || (state == 'N' || state == 'n'))) {
            printf("Invalid input, Please enter a valid input: ");
            scanf(" %c", &state);
        }
    }
    // Print terminating message
    printf("Thank you for playing!\n");
} // END OF PART 2

int main() {
    // Run parts one by one
    printf("|===============>(PART 1)<==============|\n");
    order_system();
    printf("\n|===============>(PART 2)<==============|\n");
    rps_gameloop();
    return 0;
}
