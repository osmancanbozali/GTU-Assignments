// Required libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Constants for Block types
#define OBSTACLE 'o'
#define BAIT 'b'
#define EMPTY 'e'
// Declare point struct for snake
typedef struct {
    int row;
    int col;
}point;
// Declare Block struct for board
typedef struct {
    char type;
    int value;
}Block;
/* Function that initializes a 10x10x1 game board
*  Randomly generates a bait and an obstacle
*  Returns the 3d board array
*/
Block*** init_board() {
    srand(time(NULL)); // Seed for random number generator
    // Dynamically allocate 1st dimension (row) of board array
    Block*** board = (Block***)malloc(10 * sizeof(Block**));

    for (int i = 0; i < 10; i++) {
        // Dynamically allocate each 2nd dimension (col) of board array
        board[i] = (Block**)malloc(10 * sizeof(Block*));
        
        for (int j = 0; j < 10; j++) {
            // Dynamically allocate each 3nd dimension (depth) of board array
            board[i][j] = (Block*)malloc(1 * sizeof(Block));
            // Set initial type and value
            board[i][j][0].type = EMPTY;
            board[i][j][0].value = 0;
        }
    }
    // Declare variables for x and y coordinates
    int x,y;
    // Generate a bait at a random position
    do {
        x = rand() % 10;
        y = rand() % 10;
    } while (x == 0 && y == 0);
    board[x][y][0].type = BAIT;
    // Generate an obstacle at a random position
    do {
        x = rand() % 10;
        y = rand() % 10;
    } while (x == 0 && y == 0);
    board[x][y][0].type = OBSTACLE;
    board[x][y][0].value = 1;

    return board;
}
/* Function that prints the game board to the terminal
*  Takes board array, snake array and length of snake as parameter
*/
void draw_board(Block*** board, point* snake, int * len) {
    // Declare an integer variable for snake flag
    int sflag;
    // Print upper border
    for (int i = 0; i < 12; i++) {
        printf("- ");
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            sflag = 0;
            for (int k = 0; k < *len; k++){
                if (snake[k].row == i && snake[k].col == j-1) {
                    sflag = 1;
                    // Print snake's head
                    if (k == 0) {
                        printf("O ");
                    }
                    // Print snake's body
                    else {
                        printf("X ");
                    }    
                } 
            }
            
            if (sflag == 0) {
                // Print left-right borders
                if (j == 0 || j == 11) {
                    printf("| ");
                }
                // Print bait
                else if (board[i][j-1][0].type == BAIT) {
                    printf(". ");
                }
                // Print obstacles value
                else if (board[i][j-1][0].type == OBSTACLE) {
                    printf("%d ",board[i][j-1][0].value);
                }
                // Print empty cells
                else if (board[i][j-1][0].type == EMPTY) {
                    printf("  ");
                }
            }      
        }
        printf("\n"); 
    }
    // Print lower border
    for (int i = 0; i < 12; i++) {
        printf("- ");
    }
}
/* Function that takes a input move from user
*  Takes snake array, length of snake and previous head position as parameter
*  Updates the snake's head coordinates according to the input
*/
void move(point * snake, int* len, point * previous_head_pos) {
    // Declare a variable for user-input direction
    char direction;
    int flag; // For validity check
    printf("\nEnter direction ['w' (up), 'a' (left), 's' (down), and 'd' (right)]: ");
    do {
        flag = 0;
        scanf(" %c", &direction);
        // Check whether there are more characters in input buffer
        char c;
        if ((c = getchar()) != '\n') {
            while ((c = getchar()) != '\n'); // Clear input buffer         
            printf("Invalid move! Please enter a valid move: ");
            flag =1;
            continue;
        }
        // Update previous head position
        previous_head_pos->row = snake[0].row;
        previous_head_pos->col = snake[0].col;

        // Determine direction and change corresponding value
        switch (direction)
        {
        case 'w':
            snake[0].row--;
            break;
        case 's':
            snake[0].row++;
            break;
        case 'a':
            snake[0].col--;
            break;
        case 'd':
            snake[0].col++;
            break;
        default:
            printf("Invalid move! Please enter a valid move: ");
            flag = 1;
            break;
        }
        // Check whether the snake tries to move againts it's body
        if (*len > 1 && snake[1].col == snake[0].col && snake[1].row == snake[0].row) {
                snake[0].row = previous_head_pos->row;
                snake[0].col = previous_head_pos->col;
                printf("Invalid move! Please enter a valid move: ");
                flag =1;
        }
        } while (flag == 1);
    
}
/* Function that checks game over states and returns game state
*  Takes snake array, length of snake and board array as parameters
*  1) Check whether the snake collides with the wall
*  2) Check whether snake encounters a obstacle which is larger than snake
*  3) Check whether snake hits its own body
*  Return 1 --> GAME OVER, Return 0 --> Continue 
*/
int check_status(point * snake, int* len, Block*** board) {
    // Check whether the snake collides with the wall
    if ((snake[0].row < 0 || snake[0].row > 9) || (snake[0].col < 0 || snake[0].col > 9)) {
        printf("Snake collided with the wall! GAME OVER!\n"); // Game over message
        return 1;
    }
    // Check whether snake encounters a obstacle which is larger than snake
    if (board[snake[0].row][snake[0].col][0].type == OBSTACLE) {
        if (board[snake[0].row][snake[0].col][0].value > *len) {
            printf("Snake(%d) encountered a Obstacle(%d)! GAME OVER!\n",*len,board[snake[0].row][snake[0].col][0].value);
            return 1;
        }
    }
    // Check whether snake hits its own body
    for (int i = 1; i < *len-1; i++) {
        if (snake[i].row == snake[0].row && snake[i].col == snake[0].col) {
            printf("Snake crashed to its own body! GAME OVER!\n");
            return 1;
        } 
    }
    return 0;
}
/* Function that updates game board
*  Takes snake array, length of snake, board array,
*  previous head position and move count pointer as parameters.
*  - Checks whether the bait has eaten, 
*  if so generates a bait at a random position
*  - Checks whether the snake destroyed an obstacle
*  - Updates obstacles every 5 moves
*/
void update(point ** snake, int* len, Block*** board, point* previous_head_pos, int * moveCount) {
    *moveCount += 1; // Increment move count
    int is_bait_eaten = 0;
    // Check whether the bait has eaten
    if (board[(*snake)[0].row][(*snake)[0].col][0].type == BAIT) {
        *len+=1; // Increment snake length
        // Reallocate snake array
        (*snake) = (point*)realloc((*snake),(*len) * sizeof(point));
        // Set bait cell to empty
        board[(*snake)[0].row][(*snake)[0].col][0].type = EMPTY;
        // Update flag
        is_bait_eaten = 1;
    }
    // Check whether the snake destroyed an obstacle
    else if (board[(*snake)[0].row][(*snake)[0].col][0].type == OBSTACLE) {
        // Deallocate nested obstacles
        free(board[(*snake)[0].row][(*snake)[0].col]);
        // Allocate and set empty cell at that coordinates
        board[(*snake)[0].row][(*snake)[0].col] = (Block*)malloc(1 * sizeof(Block));
        board[(*snake)[0].row][(*snake)[0].col][0].type = EMPTY;
        board[(*snake)[0].row][(*snake)[0].col][0].value = 0;
    }
    
    // Shift the body of the snake to keep the body and head connected
    int temp_row,temp_col;
    for (int i = 1; i < *len; i++) {
        temp_row= (*snake)[i].row;
        temp_col= (*snake)[i].col;
        (*snake)[i].row = previous_head_pos->row;
        (*snake)[i].col = previous_head_pos->col;
        previous_head_pos->row = temp_row;
        previous_head_pos->col = temp_col;
    }
    // Generate a bait at a random position if bait has eaten
    if (is_bait_eaten == 1) {
        int flag,x,y;
        do{
            flag = 1;
            x = rand() % 10;
            y = rand() % 10;
            if (board[x][y][0].type == EMPTY) {
                for (int i = 0; i < *len; i++) {
                    if ((*snake)[i].row == x && (*snake)[i].col == y) {
                        flag = 0;
                        break;
                    }   
                }
            }
            else {
                flag = 0;
            }
        } while (flag == 0);
        board[x][y][0].type = BAIT;
    }
    // Update obstacles
    if (*moveCount % 5 == 0) {
        // Declare a variable for obstacle count
        int obstacleCount = 0;
        // Find obstacle count
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (board[i][j][0].type == OBSTACLE) {
                    obstacleCount++;
                }  
            }
        }
        // Generate obstacle at a random position (Max obstacle count = 3)
        for (int i = 1; i <= rand()%(4-obstacleCount); i++) {
            int flag,x,y;
            do{
                flag = 1;
                x = rand() % 10;
                y = rand() % 10;
                if (board[x][y][0].type == EMPTY) {
                    for (int i = 0; i < *len; i++) {
                        if ((*snake)[i].row == x && (*snake)[i].col == y) {
                            flag = 0;
                            break;
                        }   
                    }
                }
                else {
                    flag = 0;
                }
            } while (flag == 0);
            board[x][y][0].type = OBSTACLE;
            board[x][y][0].value = 1;
        }

        // Update each obstacles value
        for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (board[i][j][0].type == OBSTACLE) {
                        // Initialize a random number 0-1,
                        // Update obstacle value if the number is equal to 1
                        if (rand() % 2 == 1) {
                            int val = rand() %10; // Declare a new random value (0-9)
                            // Update value if val is greater than it
                            if (val > board[i][j][0].value) {
                                // Reallocate cell depth
                                board[i][j] = (Block*)realloc(board[i][j], val * sizeof(Block));
                                // Fill each cell with corresponding type and value
                                for (int k = 0; k < val; k++) {
                                    board[i][j][k].type = OBSTACLE;
                                    board[i][j][k].value = val;
                                }
                            }
                        }
                    }  
                }
        }
        printf("Obstacles updated @ Move #%d\n",*moveCount);
    }
}
/* Function that loops the game
*  Takes board array as parameter
*/
void play(Block*** board) {
    // Declare variables for move count and snake length
    int moveCount=0;
    int snake_len =1;
    int * p_snake_len = &snake_len;
    // Declare a point variable for previous head position
    point previous_head_pos;
    // Dynamically allocate snake array with size 1
    point * snake = (point*)malloc(*p_snake_len * sizeof(point));
    // Set the snake's head's coordinates
    snake[0].col = 0;
    snake[0].row = 0;
    int flag; // Flag for game state
    // Loop until game over
    while (flag != 1) {
        flag = 1;
        draw_board(board,snake,p_snake_len); // Draw game board
        move(snake,p_snake_len,&previous_head_pos); // Get move from user
        flag = check_status(snake,p_snake_len,board); // Check game state
        if (flag == 0) {
            update(&snake,p_snake_len,board,&previous_head_pos,&moveCount); // Update board 
        }
    }
    
}

int main() {
    printf("220104004011 - CSE102 - HW9\nWelcome to snake game!\n");
    // Initialize a dynamically allocated game board array
    Block*** board = init_board();
    // Loop game
    play(board);
    return 0;
}