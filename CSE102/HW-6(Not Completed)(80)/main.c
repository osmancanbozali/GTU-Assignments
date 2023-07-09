#include <stdio.h>

// My implementation of strcmp func in string.h library
int str_cmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] == str2[i]) {
        if (str1[i] == '\0' || str2[i] == '\0')
            break;
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0')
        return 0;
    else
        return str1[i] - str2[i];
}

// PART 2 FUNCTIONS

/* Function that calculates feature count
*  of products by determining comma count
*/
int feature_count() {
    // Declare a pointer variable for file and open products.txt file
    FILE *fptr = fopen("products.txt","r");
    // Declare a variable for feature count with initial value 1
    int fcount = 1;
    // Declare a variable for chars in file
    char c = fgetc(fptr);
    // Loop until next line
    while (c != '\n') {
        // If char is [,] increment feature count
        if (c == ',') {
            fcount++;
        }
        // Get next char
        c = fgetc(fptr);
    }
    // Close file
    fclose(fptr);
    // Return feature count
    return fcount;
}

/* Function that returns the item count in the given file
*  Take file name as a parameter
*  Return item count (line count -1)
*/
int item_count(char file[20]) {
    // Declare a pointer variable for file and open file
    FILE *fptr = fopen(file,"r");
    // Declare a variable for item count
    int icount = 0;
    // Declare a variable for chars in file
    char c = fgetc(fptr);
    // Loop until end of file
    while (c != EOF) {
        // If new line, increment item count
        if (c == '\n') {
            icount++;
        }
        // Get next char from file
        c = fgetc(fptr);
    }
    // Close file
    fclose(fptr);
    // Return item count
    return icount;
}
/* Function that adds new feature to products
*  Set new feature value of all products to 'None' 
*/
void add_feature() {
    // Declare an array for new feature's name
    char new_feature[10];
    // Get feature name from user
    printf("Please enter the new feature's name (max 10 characters): ");
    scanf("%s",new_feature);
    // Declare pointer variables for files
    FILE *fp, *temp;
    // Open products file
    fp = fopen("products.txt","r+");
    // Open a temporary file
    temp = fopen("temp.txt","w+");
    // Declare a variable for chars in file
    char c = fgetc(fp);
    // Skip first line
    while (c != '\n') {
        fputc(c,temp);
        c = fgetc(fp);
    }
    // Print new feature's name
    fprintf(temp,",%s\n",new_feature);
    // Print none at the end of lines until file finished
    c = fgetc(fp);
    while (c != EOF) {
        if (c == '\n') {
            fprintf(temp,",%s\n","None");
        }
        else {
            fputc(c,temp);
        }
        c = fgetc(fp);
    }
    fprintf(temp,",%s","None");
    // Close files
    fclose(temp);
    fclose(fp);
    // Swap temp file with products file
    remove("products.txt");
    rename("temp.txt","products.txt");
}
/* Function that adds new product to the
*  end of the products file
*/
void add_product() {
    // Open products file
    FILE *fptr;
    fptr = fopen("products.txt","a+");
    // Calculate extra feature count (user added features)
    int extra_fcount = feature_count()-5;
    // Declare an array to store feature names
    char features[extra_fcount][10];
    // If there are extra counts
    if (extra_fcount > 0)
    {
        fseek(fptr,0,SEEK_SET); // Set pointer to the beginning of the file
        char c;
        int comma_count = 0;
        // Skip default features
        while (comma_count < 5) {
            c =fgetc(fptr);
            if (c == ',') {
                comma_count++;
            }    
        }
        // Add feature names to features array
        for (int i = 0; i < extra_fcount; i++) {
            fscanf(fptr,"%[^,||\n]s",features[i]);
            fgetc(fptr);
        }
        fseek(fptr,0,SEEK_END); // Set pointer to the end of the file
    }
    // Increment and print pID to the file
    fprintf(fptr,"\n%d", item_count("products.txt")+1);
    // Take type from user and print to the file
    char type;
    printf("Enter Type: ");
    scanf(" %c", &type);
    fprintf(fptr,",%c",type);
    // Take name from user and print to the file
    char name[8];
    printf("Enter Name: ");
    scanf("%s", name);
    fprintf(fptr,",%s",name);
    // Take name from user and print to the file
    char brand[5];
    printf("Enter Brand: ");
    scanf("%s", brand);
    fprintf(fptr,",%s",brand);
    // Take price from user and print to the file
    double price;
    printf("Enter price: ");
    scanf("%lf", &price);
    fprintf(fptr,",%.2lf", price);
    // Take values for extra features and print them to the file
    if (extra_fcount) {
        for (int i = 0; i < extra_fcount; i++) {
            char fvalue[10];
            printf("Enter %s: ",features[i]);
            scanf("%s", fvalue);
            fprintf(fptr,",%s",fvalue);
        }
    }
    fclose(fptr); // Close file
}
/* Function that adds new stock info at the
*  end of the stocks file
*/
void add_stock() {
    // Open stocks.txt file
    FILE *fptr;
    fptr = fopen("stocks.txt","a+");
    // Increment sID and print to the file
    fprintf(fptr,"\n%d", item_count("stocks.txt")+1);
    int pID;
    int pID_count = item_count("products.txt");
    // Select product pID from products file
    do
    {
        printf("Enter pID number (1-%d): ",pID_count);
        scanf("%d", &pID);
    } while (!(pID > 0 && pID <= pID_count)); // If pID did not match with any product, ask again to the user
    // Print pID to the file
    fprintf(fptr,",%d",pID);
    // Get branch name from user and print to the file
    char branch[10];
    printf("Enter branch: ");
    scanf("%s", branch);
    fprintf(fptr,",%s",branch);
    // Get current stock value from user and print it to the file
    int current_stock;
    do
    {
        printf("Enter current stock: ");
        scanf("%d", &current_stock);
    } while (current_stock <= 0);
    fprintf(fptr,",%d",current_stock);
    fclose(fptr); // Close file
    
}
// Universal line deletation, used for deleting product and stock info
void delete_line(char file[20], char id_type[3]) {
    // Declare variables for item count in file and id
    int icount = item_count(file);
    int ID;
    // Get ID of the line user wants to delete
    do
    {
        printf("Select %s of the product you want to delete (1-%d): ",id_type,icount);
        scanf("%d",&ID);
    } while (!(ID > 0 && ID <= icount));
    // Open a temporary file
    FILE *fp, *temp;
    fp = fopen(file,"r+");
    temp = fopen("temp.txt","w+");
    // Print updated file to the temp file
    char c = fgetc(fp);
    while (c != EOF) {
        int count;
        if (c!= '\n') {
            fputc(c,temp);
        }
        if (c == '\n') {
            // Print new ID
            fscanf(fp,"%d",&count);
            // Skip deleted line
            if (count == ID) {
                c = fgetc(fp);
                while (c != '\n' && c!= EOF) {
                    c = fgetc(fp);
                }
                continue;
            }
            // Arrange ID's of remaining infos
            else if(count < ID) {
                fprintf(temp,"\n%d",count);
            }
            else {
                fprintf(temp,"\n%d",count-1);
            }
        }
        c = fgetc(fp);
    }
    // Close files
    fclose(fp);
    fclose(temp);
    // Swap temporary file with main file
    remove(file);
    rename("temp.txt",file);  
}

// This func will be complated
void update_product() {
    printf("This feature is under construction..!");
}
// This func fill be complated
void update_stock() {
    printf("This feature is under construction..!");
}
/* Function for selecting file operations
*  Print menu, get user's selection and perform it
*/
void file_operations() {
    int op; // Variable for selection
    while (op != 8)  {
        // Menu
        printf("File Operations Menu:\n"
        "1- Add a new product\n"
        "2- Delete a product\n"
        "3- Update a product(-)\n"
        "4- Add feature to products\n"
        "5- Add a new stock entry\n"
        "6- Delete a stock entry\n"
        "7- Update a stock entry(-)\n"
        "8- Back to main menu\n");
        // Get option from user
        scanf("%d", &op);
        if (op < 0 || op > 9) {
        printf("Option can not found, select again: ");
        scanf("%d", &op);
    }
        // Determine operation and perform it
        switch (op)
        {
        case 1:
            add_product();
            break;
        case 2:
            delete_line("products.txt","pID");
            break;
        case 3:
            update_product();
            break;
        case 4:
            add_feature();
            break;
        case 5:
            add_stock();
            break;
        case 6:
            delete_line("stocks.txt","sID");
            break;
        case 7:
            update_stock();
            break;
        case 8:
            printf("Returning to the main menu...\n");
            break;
        default:
            printf("Invalid selection, please enter a valid selection!\n");
            break;
        }
    }
    
} // END OF PART 2 FUNCTIONS

// PART 3 FUNCTIONS

/* Function that lists all products
*  with their featues
*/
void list_all_products() {
    // Declare a variable for feature count
    int fcount = feature_count();
    // Open products file
    FILE *fptr;
    fptr = fopen("products.txt","r");
    // Declare an array for storing feature names
    char features[fcount][10];
    // Get feature names from products file
    for (int i = 0; i < fcount; i++) {
        fscanf(fptr,"%[^,||\n]s", features[i]);
        fgetc(fptr);
    }
    // Declare an array for storing product info
    char product[fcount][10];
    // Get and print products with all features from file
    for (int p = 0; p < item_count("products.txt"); p++) {
        for (int i = 0; i < fcount; i++) {
            fscanf(fptr,"%[^,||\n]s", product[i]);
            fgetc(fptr);
            printf("%s: %s\t",features[i],product[i]);
        }  
        printf("\n");
    }
    fclose(fptr); // Close file
}

/* Function that filters products with
*  user given parameters
*/
void filter_products() {
    // Declare a variable for feature count
    int fcount = feature_count();
    // Declare arrays for filters and corresponding values
    char filter[fcount][10];
    char value[fcount][10];
    char c;
    // Get filters from user
    printf("Enter filters and corresponding values seperated with commas:\n");
    int filter_count = 0;
    while (c != '\n') {
        scanf("\n%[^,]s", filter[filter_count]);
        c = getchar();
        scanf("%[^,||\n]s", value[filter_count]);
        c = getchar();
        filter_count++;
    }

    // Open products file
    FILE *fptr;
    fptr = fopen("products.txt","r");
    // Declare an array for feature names
    char features[fcount][10];
    // Get feature names from file
    for (int i = 0; i < fcount; i++) {
        fscanf(fptr,"%[^,||\n]s", features[i]);
        fgetc(fptr);
    }
    // Declare an array for product values
    char product[fcount][10];
    // Declare a variable for similarity check
    int similarity = 0;
    for (int p = 0; p < item_count("products.txt"); p++) {
        // Store all features of each line to the array
        for (int i = 0; i < fcount; i++) {
            fscanf(fptr,"%[^,||\n]s", product[i]);
            fgetc(fptr);
        }
        // Check similarities with filters
        for (int j = 0; j < filter_count; j++) {
            for (int k = 0; k < fcount; k++) {
                // If similar, increment similarity count
                if (str_cmp(filter[j],features[k]) == 0 && str_cmp(value[j],product[k]) == 0) {
                    similarity ++;
                }
                
            }
            // If similarity count is equal to filter count, print product info to the terminal
            if (similarity == filter_count) {
                // Print product
                for (int i = 0; i < fcount; i++) {
                    printf("%s: %s\t",features[i],product[i]);
                }  
                printf("\n");
            }
        }
        // Reset similarity
        similarity = 0;
    }
    // Close file
    fclose(fptr);
}
/* Function for Search Product
*  Print menu, get operation from user
*  and perform it
*/
void search_product() {
    // Declare a variable for operation
   int op;
    while (op != 3)  {
        // Menu
        printf("Query Products Menu:\n"
        "1- List all products\n"
        "2- Filter products\n"
        "3- Back to main menu\n");
        // Get operation from user
        scanf("%d", &op);
        if (op < 0 || op > 4) {
        printf("Option can not found, select again: ");
        scanf("%d", &op);
    } 
    // Determine operation and perform it
    switch (op)
    {
    case 1:
        list_all_products();
        break;
    case 2:
        filter_products();
        break;
    case 3:
        printf("Returning to main menu...\n");
        break;
    default:
        printf("Invalid option!\n");
        break;
    }
}
}
/* Function for checking stock info by pID and branch
*/
void stock_by_pid_branch() {
    // Declare needed variables
    int pID, sID, fpID, current_stock, match_count = 0;
    char branch[10], fbranch[10];
    int pcount = item_count("products.txt"); // Get product count
    // Get pId and branch name from user
    printf("Enter pID (1-%d) and branch name seperating with commas: ", pcount);
    scanf("%d,%s",&pID,branch);
    while (pID < 0 || pID > pcount) {
        printf("pID not found! Enter a valid pID value (1-%d): ",pcount);
        scanf("%d",&pID);
    }
    // Print info message
    printf("Stock for product %d in branch %s:\n", pID,branch);
    // Open stocks file
    FILE *fp = fopen("stocks.txt","r");
    char c = fgetc(fp);
    // Skip first line of file
    while (c != '\n') {
        c = fgetc(fp);
    }
    // Get values from stocks file
    for (int i = 0; i < item_count("stocks.txt"); i++) {
        fscanf(fp,"%d,%d,%[^,]s",&sID,&fpID,fbranch);
        fscanf(fp,",%d",&current_stock);
        // Check similarity with determined filters
        if (pID == fpID && str_cmp(branch,fbranch) == 0) {
            // Print sID and current stock to the terminal
            printf("Stock ID: %d\tCurrent Stock: %d\n",sID,current_stock);
            match_count++; // Increment match count
        }
    }
    // If no match, print info message
    if (match_count == 0) {
        printf("No records can found!\n");
    }
    fclose(fp); // Close file
}
/* Function that prints stock info of selected branch
*/
void stock_by_branch() {
    // Declare arrays for branch names
    char branch[10], fbranch[10];
    // Get branch name from user
    printf("Enter branch name: ");
    scanf("%s",branch);
    printf("Products in branch %s:\n",branch);
    // Open stocks file
    FILE *fp = fopen("stocks.txt","r");
    // Skip first line of file
    char c = fgetc(fp);
    while (c != '\n') {
        c = fgetc(fp);
    }
    // Declare needed variables
    int sID,pID,current_stock, match_count = 0;
    // Get stock info from file
    for (int i = 0; i < item_count("stocks.txt"); i++) {
        fscanf(fp,"%d,%d,%[^,]s",&sID,&pID,fbranch);
        fscanf(fp,",%d",&current_stock);
        // Check whether branches match
        if (str_cmp(branch,fbranch) == 0) {
            // Print sID and Current Stock to the terminal
            printf("Product ID: %d\tCurrent Stock: %d\n",pID,current_stock);
            match_count++; // Increment match count
        }
    }
    // Print a message if no match found
    if (match_count == 0) {
        printf("No records can found!\n");
    }
    fclose(fp); // Close file
}
/* Function that prints out-of-stock
*  products in given branch
*/
void out_of_stock_by_branch() {
    // Declare arrays for branch names
    char branch[10], fbranch[10];
    // Get branch name from user
    printf("Enter branch name: ");
    scanf("%s",branch);
    // Print info message
    printf("Out-of-Stock products in branch %s:\n",branch);
    // Open stocks file
    FILE *fp = fopen("stocks.txt","r");
    // Skip the first line of file
    char c = fgetc(fp);
    while (c != '\n') {
        c = fgetc(fp);
    }
    // Declare needed variables
    int sID,pID,current_stock, match_count = 0;
    // Get stock info of each line
    for (int i = 0; i < item_count("stocks.txt"); i++) {
        fscanf(fp,"%d,%d,%[^,]s",&sID,&pID,fbranch);
        fscanf(fp,",%d",&current_stock);
        // If it is out-of-stock, print pID of the product
        if (current_stock == 0 && str_cmp(branch,fbranch) == 0) {
            printf("Product ID: %d\n",pID);
            match_count++; // Increment match count
        }
    }
    // Print info message if no matches
    if (match_count == 0) {
        printf("No records can found!\n");
    }
    fclose(fp); // Close file
}
/* Function for Check Stock
*  Get operation from user and perform it
*/
void check_stock() {
    // Declare variable for operation
    int op;
    while (op != 4) {
        // Menu
        printf("Check Stock Status Menu:\n"
        "1- Check by pID and branch name\n"
        "2- All product in selected branch\n"
        "3- Out of stocks in selected branch\n"
        "4- Back to main menu\n");
        // Get operation from user
        scanf("%d", &op);
        if (op < 0 || op > 5) {
        printf("Option can not found, select again: ");
        scanf("%d", &op);
    }
    // Determine and perform operation
    switch (op)
    {
    case 1:
        stock_by_pid_branch();
        break;
    case 2:
        stock_by_branch();
        break;
    case 3:
        out_of_stock_by_branch();
        break;
    case 4:
        printf("Returning to main menu...\n");
        break;
    default:
        printf("Invalid option!\n");
        break;
    }
    }
    
}
/* Function that prints pIDs and Total Stock values
*  of selected Brand
*/
void brand_stock_control(char brand[]) {
    // Declare a variable for product count
    int pcount = item_count("products.txt");
    // Declare a 2D array for storing product infp
    double array[pcount][3];
    // Open products file
    FILE *fp;
    fp = fopen("products.txt","r");
    // Declare variables for needed values
    char fbrand[10];
    double pID,price;
    int counter = 0;
    while (fgetc(fp) != '\n'); // Skip first line
    for (int i = 0; i < pcount; i++) {
        fscanf(fp,"%lf,",&pID); // Get pID
        // Skip to brand name
        int commas = 0;
        while (commas != 2){
            if (fgetc(fp) == ',') {
                commas++;
            }
        }
        fscanf(fp,"%[^,]s",fbrand); // Get brand name from file
        fgetc(fp);
        fscanf(fp,"%lf,",&price); // Get price value from file
        char c = fgetc(fp);
        // Skip to next line
        while (c != '\n' && c != EOF) {
            c = fgetc(fp);
        }
        // Compare brand names
        if (str_cmp(brand,fbrand) == 0) {
            // If match store those values in array
            array[counter][0] = pID;
            array[counter][1] = price;
            counter++; // Increment counter
        }
    }
    fclose(fp); // Close file
    // Open stocks file
    FILE *fptr;
    fptr = fopen("stocks.txt","r");
    // Declare variable for stocks count and current stock values
    int scount = item_count("stocks.txt");
    double current_stock;
    while (fgetc(fptr) != '\n'); // Skip first line
    for (int i = 0; i < scount; i++) {
        // Skip to pID
        int commas = 0;
        while (commas != 1){
            if (fgetc(fptr) == ',') {
                commas++;
            }
        }
        fscanf(fptr,"%lf,",&pID); // Get pID from file
        fscanf(fptr,"%[^,]s",fbrand); // Get brand name from file
        fgetc(fptr);
        fscanf(fptr,"%lf,",&current_stock); // Get current stock value from file
        // Compare with array values
        for (int j = 0; j < counter; j++) {
            if (array[j][0] == pID) {
                // Add to the total stock if pID's match
                array[j][2]+= current_stock;
            }
        }
    }
    fclose(fptr); // Close file
    // Print values
    printf("Info about %s products:\n",brand);
    for (int i = 0; i < counter; i++) {
        printf("pID: %.0f\tPrice: %.2f\t Current Stocks (Total): %.0f\n",array[i][0],array[i][1],array[i][2]);
    }  
}
// This func will be completed
void export_report(char brand[]) {
    printf("This feature is under construction..!\n");
}
// Main menu
void menu() {
    printf("Please select an option to continue:\n"
    "1- File Operations\n"
    "2- Query products\n"
    "3- Check stock status\n"
    "4- Stock control by brand\n"
    "5- Export report(-)\n");
}
/* Function that chooses operation from main menu
*/
int select_operation() {
    // Declare an array for brand name
    char brand[5];
    // Declare a variable for selection
    int selection;
    // Get selection from user
    scanf("%d", &selection);
    if (selection < 0 || selection > 5) {
        printf("Option can not found, select again: ");
        scanf("%d", &selection);
    }
    // Determine selection and perform operation
    switch (selection){
    case 1:
        file_operations();
        break;
    case 2:
        search_product();
        break;
    case 3:
        check_stock();
        break;
    case 4:
        // Get brand name from user
        printf("Enter brand name: ");
        scanf("%s", brand);
        brand_stock_control(brand);
        break;
    case 5:
        export_report(brand);
        break;
    default:
        printf("Invalid selection!\n");
        break;
    }
    return selection;
}

// Main function
int main() {
    // Welcome message
    printf("Welcome operator, ");
    // Flag for terminating
    int flag;
    // Loop until terminate flag
    while (flag != 5) {
        menu();
        flag = select_operation();
    }
}