// Required libraries
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

// Define Game states for Part 3
#define GAMEOVER 0
#define PLAYER1 1
#define PLAYER2 2

// PART 1

/* Take a char as parameter
*  If it is lower case, convert it
*  to upper case by using ASCII values
*  Return char
*/
char convert_to_upper(char c) {
    if(c >= 'a' && c <= 'z') {
        // Convert lower case character to upper case character
        c = c - 'a' + 'A';
    }
    return c;
}
/* Main body of Part1
*  Ask for a filename, open it and find
*  all letter frequencies, print them.
*/
void letter_frequency() {
    // Declare a variable for file operations
    FILE *fptr;
    // Declare a variable for reading the file char by char
    char c;
    // Declare an array for letter frequency
    int frequency[26] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    // Declare an array for file name
    char filename[50];
    // Get file name from user
    printf("Enter the file name: ");
    scanf("%s", filename);
    // Open file
    fptr = fopen(filename,"r");
    // If file can not found, ask for another file name
    while (fptr == NULL) {
        printf("File can not found, Please insert a existing file name: ");
        scanf("%s", filename);
    	fptr = fopen(filename,"r");
    }
    // Set c to the first char of file
    c = fgetc(fptr);

    // Find frequency until the end of file
    while (c != EOF) {
        // Find the chars queue in the frequency array
        int queue = convert_to_upper(c) - 'A';
        // Check whether the char is in alphabet or not
        if (queue >= 0 && queue <=25) {
            // Increment frequency
            frequency[convert_to_upper(c) - 'A']++;
        }
        // Set c to the next char in file
        c = fgetc(fptr);
    }

    // Print the results in a tabular format
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n",'A'+i,frequency[i]);
    }
    
} // END OF PART 1

// PART 2

// Declare enumeration for colors
enum color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
};

/* Take a char as a parameter
*  Determine color from it's first letter
*  Return color enum value
*/
enum color determineColor(char c) {
    //Declare variable for return color
    enum color return_color;
    // Determine color
    switch (c)
    {
    case 'r':
        return_color = RED;
        break;
    case 'g':
        return_color = GREEN;
        break;
    case 'b':
        return_color = BLUE;
        break;
    case 'y':
        return_color = YELLOW;
        break;
    default:
        return_color = ORANGE;
        break;
    }
    // Return color
    return return_color;
}
/* Take a color value and index number as parameters
*  Fill [RGB] value at the given index
*/
double fill_rgb_array(enum color color, int index) {
    // Declare arrays for each color's [RGB] values
    double red_arr[3] = {1,0,0};
    double green_arr[3] = {0,1,0};
    double blue_arr[3] = {0,0,1};
    double yellow_arr[3] = {0.5,0.5,0};
    double orange_arr[3] = {0.5,0.5,0.2};
    // Declare variable for value
    double value;
    // Determine color and get correct value from array
    switch (color)
    {
    case RED:
        value = red_arr[index];
        break;
    case GREEN:
        value = green_arr[index];
        break;
    case BLUE:
        value = blue_arr[index];
        break;
    case YELLOW:
        value = yellow_arr[index];
        break;
    default:
        value = orange_arr[index];
        break;
    }
    // Return value
    return value;
}
/* Get two color enums as parameter
*  Mix them together, find the closest
*  color by Euclidean distance
*  Return closest color value as final color
*/
enum color mixColors(enum color color1, enum color color2) {
    // Declare arrays for color arrays
    double color1_arr[3];
    double color2_arr[3];
    double fcolor_arr[3] = {0,0,0};
    // Declare a variable for final color value
    enum color fcolor;

    // Fill arrays with [RGB] values
    for (int i = 0; i < 3; i++)
    {
        color1_arr[i] = fill_rgb_array(color1,i);
        color2_arr[i] = fill_rgb_array(color2,i);
        // Fill final array by [(x+y)\2]
        fcolor_arr[i] = (color1_arr[i] + color2_arr[i]) / 2.0;
    }
    // Declare variable for distance with initial value;
    double distance= 9999999999;

    // Compare final array with all other color arrays
    for (int i = RED; i <= ORANGE; i++){
        // Declare a variable for temporary distance
        double temp_distance= 0;
        // Declare an array for comparison color
        double comp_arr[3];
        for (int j = 0; j < 3; j++) {
            // Fill comparison array
            comp_arr[j] = fill_rgb_array(i,j);
            // Calculate and sum the distance
            temp_distance += (comp_arr[j] - fcolor_arr[j])*(comp_arr[j] - fcolor_arr[j]);
        }
        // Check distance, if the compared color is closer, set final value as it
        if (distance > temp_distance)
        {
            distance = temp_distance;
            fcolor = i;
        }
    }
    // Return final color
    return fcolor;  
}
/* Given function prototype for Part 2
*  Take two color enums and a function pointer as parameters
*  Mix colors with the function, determine final color and print result
*/
void colorMixer(enum color color1, enum color color2, enum color (*operation)(enum color, enum color)) {
    // Declare a variable for final color value
    enum color final_color = operation(color1,color2);
    // Determine final color and print result
    switch (final_color)
    {
    case RED:
        printf("Mixed Color: RED [1,0,0]");
        break;
    case GREEN:
        printf("Mixed Color: GREEN [0,1,0]");
        break;
    case BLUE:
        printf("Mixed Color: BLUE [0,0,1]");
        break;
    case YELLOW:
        printf("Mixed Color: YELLOW [0.5,0.5,0]");
        break;
    case ORANGE:
        printf("Mixed Color: ORANGE [0.5,0.4,0.2]");
        break;
    default:
        printf("ERROR!");
        break;
    }
}
/* Main body of Part2
*  Get two chars for colors from user
*  Mix them!
*/
void part2() {
    // Declare variables for chars
    char c1,c2;
    // Declare variables for color enums
    enum color color1,color2;
    // Get first char from user
    do
    {
        printf("Enter Color 1 (r,g,b,y,o): ");
        scanf(" %c", & c1);
    } while (c1 != 'r' && c1 != 'g' && c1 != 'b' && c1 != 'y' && c1 != 'o');
    // Determine first color by it's first letter
    color1 = determineColor(c1);
    // Get second char from user
    do
    {
        printf("Enter Color 2 (r,g,b,y,o): ");
        scanf(" %c", & c2);
    } while (c2 != 'r' && c2 != 'g' && c2 != 'b' && c2 != 'y' && c2 != 'o');
    // Determine second color by it's first letter
    color2 = determineColor(c2);
    // Mix colors
    colorMixer(color1,color2,mixColors);
} // END OF PART 2

// PART 3

/* Check whether the parameter coordinates 
*  are crossing the 3x3 game arena or not
*/
int border_check(int x, int y) {
    int border_crossed;
    if ((x < 0 || x > 2) || (y < 0 || y > 2)) {
        border_crossed = 1;
    }
    else {
        border_crossed = 0;
    }
    return border_crossed;
}

/* Main loop of part 3
*  2 player tic-tac-toe game
*/
void tictactoe() {
    char restart = 'Y';
    while (restart == 'Y' || restart == 'y') {
        // Declare variable for turn state
        int state = PLAYER1;
        int move_count =0;
        // Declare an array for 3x3 game table
        char table[3][3] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}};
        // Loop until game finishes
        while (state != GAMEOVER) {
            // Declare an array for coordinates of move
            int move[2];
            // Player1's turn
            if (state == PLAYER1) {
                // Get move from user
                printf("Player 1 (X), enter your move (row,col): ");
                scanf("%d %d", &move[0], &move[1]);
                // Check if it is a suitable move; if not, take a suitable move
                while (border_check(move[0],move[1]) || (table[move[0]][move[1]] != '_')) {
                    printf("Invalid input, please enter a valid coordinate: ");
                    scanf("%d %d", &move[0], &move[1]);
                }
                // Change the selected coordinates to X on the table
                table[move[0]][move[1]] = 'X';
                // Set turn state to player2 for next turn
                state = PLAYER2;
            }
            // Player2's turn
            else {
                // Get move from user
                printf("Player 2 (O), enter your move (row,col): ");
                scanf("%d %d", &move[0], &move[1]);
                // Check if it is a suitable move; if not, take a suitable move
                while (border_check(move[0],move[1]) || (table[move[0]][move[1]] != '_')) {
                    printf("Invalid input, please enter a valid coordinate: ");
                    scanf("%d %d", &move[0], &move[1]);
                }
                // Change the selected coordinates to O on the table
                table[move[0]][move[1]] = 'O';
                // Set turn state to player2 for next turn
                state = PLAYER1;
            }
            move_count ++;
            // Print the game table
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                printf("%c ", table[row][col]);
                }
                // Jump to a new line
                printf("\n"); 
                }
            // Check game status
            for (int i = 0; i < 3; i++) {
                // Check rows
                if ((table[i][0] != '_') && (table[i][0] == table[i][1]) && (table[i][0] == table[i][2])) {
                    if (table[i][0] == 'X') {
                        printf("Player 1 (X) Wins!");
                    }
                    else {
                        printf("Player 2 (O) Wins!");
                    }
                state = GAMEOVER;
                }
                // Check columns
                else if((table[0][i] != '_') && (table[0][i] == table[1][i]) && (table[0][i] == table[2][i])) {
                    if (table[0][i] == 'X') {
                        printf("Player 1 (X) Wins!");
                    }
                    else {
                        printf("Player 2 (O) Wins!");
                    }
                    state = GAMEOVER;
                    } 
                }
            // Check cross game status (\)
            if (table[0][0] != '_' && table[0][0] == table[1][1] && table [0][0] == table[2][2]) {
                if (table[0][0] == 'X') {
                    printf("Player 1 (X) Wins!");
                }
                else {
                    printf("Player 2 (O) Wins!");
                } 
                state = GAMEOVER;
            }
            // Check cross game status (/)
            else if(table[0][2] != '_' && table[0][2] == table[1][1] && table [0][2] == table[2][0]) {
                if (table[0][2] == 'X') {
                    printf("Player 1 (X) Wins!");
                }
                else {
                    printf("Player 2 (O) Wins!");
                }
                state = GAMEOVER;
            }
            // Check move count
            if (state != GAMEOVER && move_count == 9) {
                printf("Draw!");
                state = GAMEOVER;
            }
        }
        // Ask user for restart
        printf("\nDo you want to play again? (Y/N): ");
        scanf(" %c", &restart);
        // If selection is invalid, get a valid selection
        while (!((restart == 'Y' || restart == 'y') || (restart == 'N' || restart == 'n'))) {
            printf("\nInvalid selection, enter a valid selection (Y/N): ");
            scanf(" %c", &restart);
        }
    }
    // Terminating message
    printf("Thank you so much for playing :)\n");        
} // END OF PART 3
