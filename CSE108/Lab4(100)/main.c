#include <stdio.h>

void draw_square(int size) {
    // Declare a variable and calculate column size
    int col_size = 2*size-1;
    // Print the square
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < col_size; col++) {
            // Specify and print * to borders
            if (row == 0 || row == size-1) {
                if (col%2 == 0)
                printf("*");
                else
                printf(" ");
            }
            else if(col == 0 || col == col_size -1) {
                printf("*");
            }
            // Print space to the inner square
            else
            printf(" ");
        }
        printf("\n"); //Jump to next line
    }  
}

void draw_triangle(int size) {
   for(int i = 0; i < size-1; i++) {
        // Print spaces
        for(int space = 1; space < size-i; space++) {
            printf(" ");
        }
        // Print stars
        for (int star = 0; star <= 2*i; star++) {
            if(star==0 || star==2*i)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    // Print bottom row
    for(int i=0; i<2*size-1; i++){
        printf("*");
    }
    printf("\n");
}

void main_menu() {
    FILE *fptr; // For file operatons
    char shape; // Variable for selected shape s/t
    int size; // Size of the shape
    int state =0; // Menu state

    while (state !=3) {
        char selection; // Variable for selection
        // Print menu
        printf("Welcome to Shape Reader! Please make your choice to continue:\n");
        printf("1-) Generate a shape file\n");
        printf("2-) Read and draw a shape file\n");
        printf("3-) Terminate the program\n");
        // Get selection from user
        scanf(" %c", &selection);
        switch (selection) {
        case '1':
            // Create shapes file
            fptr = fopen("shapes.txt","w");
            while (shape != 'e') {
                // Get shape from user
                printf("Select shape [s](square) / [t](triange): ");
                scanf(" %c", &shape);

                if (shape == 's' || shape == 't') {
                    // Get size from user
                    printf("Enter size: ");
                    scanf("%d", &size);
                    while (size < 3) {
                        printf("Size can not be smaller than 3\nEnter valid size: ");
                        scanf("%d", &size);
                    }
                    // Print to the txt file
                    fprintf(fptr,"%c,%d\n",shape,size);
                }
                else if (shape == 'e') {
                    printf("File successfully created!\n");
                    break;
                }
                else
                printf("Invalid shape!\n");                
            }
            fclose(fptr); // Close file
            state = 1; // Set state
            break;
        case '2':
            // Check if file created by state value
            if(state == 1) {
                fptr = fopen("shapes.txt","r"); // open file
                while (fscanf(fptr,"%c,%d\n",&shape,&size) != EOF) {
                    printf("Shape:\n");
                    // Determine and print shape
                    if (shape == 's') {
                        draw_square(size);
                        }
                    else if (shape == 't') {
                        draw_triangle(size);
                        }
                }  
                fclose(fptr);
            }
            else
            printf("First, you need to generate a shape file!\n");
            break;
        case '3':
            printf("Terminating program..\n");
            // Set state to exit
            state =3;
            break;
        default:
            printf("Invalid selection, please enter a valid selection: ");
            break;
        }

    }
    
}

int main() {
   main_menu();
    return 0;
}