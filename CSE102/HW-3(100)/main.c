//Required libraries
#include <stdio.h>
#include <stdlib.h> // rand() function

// Define movement keys
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
// Define game states
#define CONTINUE 0
#define GAMEOVER 1
// Define menu items
#define START_GAME '1'
#define HELP_MENU '2'
#define EXIT '3'

// Used functions
void draw_room(int size, int d_x, int d_y, int c_x, int c_y); // Part 1
char get_selection(); // Get input from stdin and clear input buffer
void gameplay(); // Part 2
int status_control(int d_x,int d_y, int c_x, int c_y); // Part 3
void main_screen(); // Part 4

/* (Part 1)
*  Draw the room with given size
*  Place the door and character according
*  to their coordinates
*/
void draw_room(int size, int d_x, int d_y, int c_x, int c_y){
    int row_count = size+2;
    int column_count = 2*size+1;

    //Scale coordinates to room
    d_x=2*d_x+1;
    d_y+=1;
    c_x=2*c_x+1;
    c_y+=1;
    // Draw the room
    for (int row = 0; row < row_count; row++)
    {
        for (int column = 0; column < column_count; column++)
        {
            // Place the door
            if (column == d_x && row == d_y) 
            {
                printf("D");
                continue;
            }
            // Place the character
            else if (column == c_x && row == c_y)
            {
                printf("C");
                continue;
            }
            // Draw horizontal borders
            else if (row==0 || row == row_count-1)
            {
                printf("-");
                continue;
            }
            // Draw vertical borders
            else if (column == 0 || column == column_count-1)
            {
                printf("|");
            }
            // Draw the inside of the room
            else {
                if(column%2==0) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }   
}

/* Get next selection from user
*  Check whether the input is single character or not
*  Clear input buffer
*  Return selection
*/
char get_selection() {
    char selection;
    scanf(" %c", &selection); // Get next selection from user
    if((getchar()) != '\n' ) { // Check next character from input
        while ((getchar()) != '\n'); // Clear input buffer
        selection = ' '; // Clear selection
    }
    return selection; // Return selection
}

/* (Part 2)
*  Initialize the gameplay
*  Loop it until the door found
*/
void gameplay() {
    // Declare variable for room size
    int size=0;
    // Declare variable for counting movements
    int movecount =0;
    // Get the room size from user
    printf("Enter the size of the room: ");
    scanf("%d", &size);
    while(size <5 || size > 10) {
        printf("Size must be between 5 an 10 (included)"
        "\nEnter a appreciate size for room: ");
        scanf("%d", &size);
    }

    // Randomly initialize initial positions
    int d_x = rand() % size;
    int d_y = rand() % size;
    int c_x = rand() % size;
    int c_y = rand() % size;
    
    // Declare variable for game state
    int state= CONTINUE; // 0 --> game continues, 1 --> game finished
    while (state == CONTINUE) {
        // Declare variables for character movement selection
        char move;

        // Draw the room
        draw_room(size,d_x,d_y,c_x,c_y);

        // Get next move from user
        printf("\nInsert move: ");
        move = get_selection();

        // Change coordinates according to the selection
        switch (move)
        {
        case UP:
            c_y--;
            break;
        case DOWN:
            c_y++;
            break;
        case LEFT:
            c_x--;
            break;
        case RIGHT:
            c_x++;
            break;
        default:
            // Error message if movement can not found
            printf("Undefined move..\n");
            continue;
            break;
        }
        
        // Declare variable for crossing border situation
        int bflag =0; // 1--> Border crossed, 0 --> Border not crossed
        // Check whether the border crossed or not and arrange the coordinates
        if (c_x == size)
        {
            c_x= size-1;
            bflag=1;
        }
        else if(c_x <0) {
            c_x=0;
            bflag=1;
        }

        if (c_y == size)
        {
            c_y= size-1;
            bflag=1;
        }
        else if(c_y <0) {
            c_y=0;
            bflag=1;
        }
        // If border's crossed, print a warning
        if (bflag ==1) {
            printf("Be careful! You can not cross the room border...\n");
        }
        // If move can be done successfully, increment movecount
        else {
            movecount++;
        }

        // Check game state
        state= status_control(d_x,d_y,c_x,c_y);
    }

    // Print a gameover message
    printf("\n**********GAMEOVER**********\n"
    "You win! You've found the door in %d steps\n\n",movecount);
}

/* (Part 3)
*  Take coordinates of the door and the character
*  If they are same, return --> 1
*  If they are different, return --> 0
*/
int status_control(int d_x,int d_y, int c_x, int c_y) {
    // Declare variable for game state
    int state;
    // Compare character and door's coordinates
    if (c_x == d_x && c_y == d_y) {
        // If same, set state to GAMEOVER(1)
        state = GAMEOVER;
    }
    else {
        // If not same, set state to CONTINUE(0)
        state = CONTINUE;
    }
    // Return state
    return state;
    
}


/* (Part 4)
*  Main menu and main menu functionalities
*/
void main_screen() {
    // Define menu state variable
    char menu_state = '0';

    while (menu_state != '3') {
        //Print the main menu
        printf("Welcome to the 2D puzzle game!"
        "\n1. New Game"
        "\n2. Help"
        "\n3. Exit");

        // Get selection from user
        printf("\nSelect from menu: ");
        menu_state = get_selection();

        // Determine menu state
        switch (menu_state)
        {
        case START_GAME:
            // Start game
            gameplay();
            break;
        case HELP_MENU:
            // Print the help menu
            printf("**********OBJECTIVE**********\n"
            "Reach to door(D) with your character(C)\n"
            "**********RULES**********\n"
            "Room size must be between 5 and 10 (included)\n"
            "Character can only move up, down, left and right\n"
            "Character can move 1 step in each input\n"
            "Character can not cross the borders of the room\n"
            "**********HOW TO PLAY**********\n"
            "Insert w(up), s(down), a(left), d(right) for movements\n"
            "******************************\n"
            );
            break;
        case EXIT:
            // Print a goodbye message
            printf("Thank you for playing, See you soon :)\n");
            break;
        default:
            printf("Invalid selection!\n");
            break;
        }
    }
    
}

// Run the game
int main() {
    main_screen();
    return 0;
}