#include <stdio.h>
#include <stdlib.h> // rand() function
#include <time.h> // time() function

#define MAX_MOVE_COUNT 1300000 // MAX MOVE COUNT FOR PC_PLAY
// Define constant values for menu items
#define USER_PLAY '1'
#define PC_PLAY '2'
#define SHOW_BEST_SCORE '3'
#define EXIT '4'

// Define constants for game states 
#define CONTINUE 0
#define GAMEOVER 1

// Struct for game board
typedef struct{
    char matrix[3][3];
    char last_move;
    int move_count;
}board;

// Function that checks whether a game board is unsolvable
// Return: 0-> Solveable 1-> Unsolveable 
int is_unsolvable(char characters[]) {
    int inversions = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = i+1; j < 9 && characters[i] != '_'; j++) {
            if (characters[i] > characters[j]) {
                inversions++;
            }
        }
    }
    return inversions%2;
}

// Function that generates a board bt shuffling characters randomly
void generate_random_board(board * b) {
    char characters[9] = {'1','2','3','4','5','6','7','8','_'};
    
    // Shuffle characters
    do {
        for(int i = 8; i > 0; i--) {
            int j = rand() % (i + 1);
            char temp = characters[i];
            characters[i] = characters[j];
            characters[j] = temp;
        }
    } while (is_unsolvable(characters) == 1); // Check solvability

    // Put in board
    for (int i = 0; i < 9; i++) {
        b->matrix[i/3][i%3] = characters[i];
    }
}

// Function that prints the game board to the terminal
void print_board(board b) {
    for (int i = 0; i < 3; i++) {
        printf("%c %c %c\n",b.matrix[i][0],b.matrix[i][1],b.matrix[i][2]);
    }
}

// Function that saves the game board to a given file with move count
void save_game_board(char * filename, char * mode, board b) {
    FILE *fp = fopen(filename,"a+");
    fprintf(fp,"Move #%d\n",b.move_count);
    
    for (int i = 0; i < 3; i++) {
        fprintf(fp,"%c %c %c\n",b.matrix[i][0],b.matrix[i][1],b.matrix[i][2]);
    }
    fclose(fp);
}

/* Function that checks whether the game is over or not
*  0 --> Continue
*  1 --> Game Finished
*/
int check_game_state(board b) {
    char correct_order[8] = {'1','2','3','4','5','6','7','8'};
    for (int i = 0; i < 8; i++) {
        if (b.matrix[i/3][i%3] != correct_order[i]) {
            return CONTINUE;
        } 
    }
    return GAMEOVER;
}

// Function that prints best score according to best_score.txt file
void print_best_score() {
    FILE* fp;
    int best_score;
    fp = fopen("best_score.txt","r");
    fscanf(fp,"%d",&best_score);
    printf("\nThe best score is %d...\n\n",best_score);
}

/* Function that compares parameter score 
*  with best score in best_scores file
*  Updates best score if parameter score
*  is bigger than best score 
*/
void update_best_score(int score) {
    FILE* fp;
    int best_score;
    fp = fopen("best_score.txt","r+");
    fscanf(fp,"%d",&best_score);
    if (score > best_score) {
        fseek(fp,0,SEEK_SET);
        fprintf(fp,"%d",score);
    }
    fclose(fp);
}

// Function that gets move from user
int get_move(char move[4]) {
    int flag = 1; // Validity flah
    printf("Enter your move (number-direction, e.g., 2-R): ");
    scanf("%3s",move);
    move[3] = '\0';

    if (move[2] >= 'a' && move[2] <= 'z') {
        move[2] = move[2] - 'a' + 'A';
    }
    
    if (getchar() != '\n') {
        flag = 0;
        while (getchar() != '\n');
    }
    if (move[1] != '-') {
        flag = 0;
    }
    
    return flag;
}

// Function for border control (Limits: {0,max})
int scale(int num,int max) {
    if (num > max) {
        return max;
    }
    else if (num < 0) {
        return 0;
    }
    return num;
}

// Function that checks whether the input move is valid or not
int check_validity(char move[4],int coordinates[4], board b) {
    int flag = 0; // Flag for validity
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 && flag == 0; j++) {
            if (move[0] == b.matrix[i][j]) {
                flag = 1;
                coordinates[0] = i;
                coordinates[2] = i;
                coordinates[1] = j;
                coordinates[3] = j;
            }
        }   
    }

    if (flag == 1) {
        // Determine move
        switch (move[2]) {
        case 'U':
            coordinates[2] = scale(coordinates[0]-1,2);
            break;
        case 'D':
            coordinates[2] = scale(coordinates[0]+1,2);
            break;
        case 'L':
            coordinates[3] = scale(coordinates[1]-1,2);
            break;    
        case 'R':
            coordinates[3] = scale(coordinates[1]+1,2);
            break;
        default:
            flag = 0;
            break;
        }
    }
    // Check whether move is valid or not
    if (flag == 1 && b.matrix[coordinates[2]][coordinates[3]] != '_') {
        flag = 0;
    }
        
    return flag;
}

// Function that updates game board with new move
void make_move(int coordinates[4], board * b) {
    char temp = b->matrix[coordinates[0]][coordinates[1]];
    b->matrix[coordinates[0]][coordinates[1]] = b->matrix[coordinates[2]][coordinates[3]];
    b->matrix[coordinates[2]][coordinates[3]] = temp;
}

// Play as user mode
void play_as_user() {
    // Create a board struct and generate random board
    board g_board = {{0},'S',0};
    generate_random_board(&g_board);
    // Remove state file
    remove("state.txt");
    // Save initial state to file  
    save_game_board("state.txt","w",g_board);
    // Loop until game over
    while (check_game_state(g_board) == CONTINUE) {
        print_board(g_board);
        char move[4];
        int coordinates[4] = {0,0,0,0};
        if (get_move(move) == 1) { // Get move from user
            if (check_validity(move,coordinates,g_board) == 1) { // Check validity
                make_move(coordinates, &g_board); // Make move
                g_board.move_count++; // Increment move count
                save_game_board("state.txt","w",g_board); // Save state to file
            }
            else {
                printf("%s is an illegal move!!! Make legal move!!!\n", move);
            }
        }
        else {
            printf("Please enter the move in correct format!\n");
        }
    }
    print_board(g_board); // Print end of game state
    int score = 1000-(g_board.move_count*10); // Calculate score
    printf("\nCongratulations! You have finished the game.\n"
    "Total number of moves: %d\n"
    "Your Score: %d\n",g_board.move_count,score);
    update_best_score(score); // Update best score
}
/* Function that generates a random move until it is valid
*  Returns valid move with coordinates
*/
void generate_move(char move[4],int coor[4], board * b) {
    do {
        char dir[4] = {'U','D','L','R'};
        while ((move[0] = b->matrix[rand()%3][rand()%3]) == '_');
        move[2] = dir[rand()%4];
    } while (check_validity(move,coor,*b) == 0 || move[2] == b->last_move);

    switch (move[2]) {
    case 'U':
        b->last_move = 'D';
        break;
    case 'D':
        b->last_move = 'U';
        break;
    case 'L':
        b->last_move = 'R';
        break;
    case 'R':
        b->last_move = 'L';
        break;
    default:
        break;
    }
}
/* Recursive function
*  Generate and make a random valid move
*  Calls itself until game over
*/
int auto_finish(board * b, char move[4], int coor[4]) {
    print_board(*b);
    // Check game state
    if (check_game_state(*b) == GAMEOVER) {
        printf("Total number of computer moves: %d\n",b->move_count);
        return 1; // Game Over
    }

    if (b->move_count == MAX_MOVE_COUNT)
    {
        printf("Computer was not able to solve this puzzle in %d moves\n"
        "Please try again with different board...\n",MAX_MOVE_COUNT);
        return 1;
    }
    
    generate_move(move,coor,b); // Generate a random valid move
    printf("Computer Move: %s\n",move);
    make_move(coor, b);
    b->move_count++;
    save_game_board("state.txt","a",*b);
    return auto_finish(b,move,coor);
}

// Play as pc mode
void play_as_pc() {
    // Declare an int array for coordinates
    int coor[4];
    // Declare a string for move
    char move[4] = "0-I";
    // Declare a board struct and generate random board
    board b = {{0},'S',0} ; 
    generate_random_board(&b);
    // Remove state file
    remove("state.txt");
    // Create a file and save initial state to file
    save_game_board("state.txt","w",b);
    // Recursion until game over
    auto_finish(&b,move,coor);
}

// Main menu function
char main_menu() {
    printf("Welcome to the 8-Puzzle Game!\n"
    "Please select an option:\n"
    "1. Play game as a user\n"
    "2. Finish the game with PC\n"
    "3. Show the best score\n"
    "4. Exit\n"
    "> ");
    char selection;
    scanf(" %c", &selection);
    switch (selection) {
    case USER_PLAY:
        play_as_user();
        break;
    case PC_PLAY:
        play_as_pc();
        break;
    case SHOW_BEST_SCORE:
        print_best_score();
        break;
    case EXIT:
        printf("Program terminated...\n");
        break;
    default:
        printf("Invalid Selection!\n");
        break;
    }
    return selection; 
}

int main() {
    srand(time(NULL)); // Set seed for random number generator
    while (main_menu() != EXIT);
    return 0;
}
