#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 100
// Declare book struct
typedef struct Book{
    char ISBN[14];
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    char status[10];
    int publicationYear;
    struct Book* next;
}Book;
// Declare student struct
typedef struct Student{
    char name[MAX_LENGTH];
    char ID[100];
    int borrowedBookCount; // Element count of borrowedBooks array
    Book* borrowedBooks;
    struct Student* next;
}Student;
/* Function that adds student to linked list of students
*  by taking the student data as parameters.
*/
void addStudent(Student** head, char* name, char* id, int borrowedBookCount, Book *borrowedBooks) {
    // Allocate memory for student struct
    Student* newStudent = (Student*)malloc(sizeof(Student));
    // Check whether the allocation failed
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    // Copy parameter values to student struct
    strcpy(newStudent->name,name);
    strcpy(newStudent->ID,id);
    newStudent->borrowedBookCount = borrowedBookCount;
    newStudent->next = NULL;
    newStudent ->borrowedBooks = borrowedBooks;
    
    // Add to beginning if linked list is empty
    if (*head == NULL) {
            *head = newStudent;
        }
    // Add to end if linked list is not empty
    else {
        Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}
/* Function that reads student data from parameter file
*  and fills the linked list of students.
*  Takes linked list of students head pointer and
*  file name as parameters.
*/
void readStudentsFromFile(Student** head, char* file){
    // Open file 
    FILE *fp = fopen(file,"r");
    // Check whether the file is opened
    if (fp == NULL) {
        printf("File can not opened!\n");
        return;
    }
    // Declare variables for student info
    char name[MAX_LENGTH];
    char ID[100];
    int borrowedBookCount;
    char c = ' ';
    // Read file until END OF FILE
    while (c != EOF) {
        fscanf(fp,"%[^,]s",name);
        fgetc(fp);
        fscanf(fp,"%[^,]s",ID);
        fgetc(fp);
        fscanf(fp,"%d",&borrowedBookCount);
        c = fgetc(fp);
        // Dynamically allocate a book struct array
        Book* borrowedBooks = (Book*)malloc(borrowedBookCount*sizeof(Book));
        // Check whether the allocation is failed or not
        if (borrowedBooks == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        // Read borrowed book info from file
        for (int i = 0; i < borrowedBookCount; i++) {
            fscanf(fp,"%[^,]s",borrowedBooks[i].ISBN);
            fgetc(fp);
            fscanf(fp,"%[^,]s",borrowedBooks[i].title);
            fgetc(fp);
            fscanf(fp,"%[^,]s",borrowedBooks[i].author);
            fgetc(fp);
            fscanf(fp,"%d",&borrowedBooks[i].publicationYear);
            c = fgetc(fp); 
        }
        // Add student to linked list
        addStudent(head,name,ID,borrowedBookCount,borrowedBooks);
    }
    // Close file
    fclose(fp);
}
/* Function that adds a new book to linked list of books
*  with selected method by taking the book data as parameters.
*  Methods: 0 -- > FIFO , 1 --> LIFO
*/
void addBook(Book** head, char* isbn, char* title, char* author, int publicationYear, int method, char* status) {
    // Dynamically allocate a book struct
    Book* newBook = (Book*)malloc(sizeof(Book));
    // Check whether the allocation is failed or not
    if (newBook == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    // Copy parameter values to dynamically allocated struct
    strcpy(newBook->ISBN,isbn);
    strcpy(newBook->title,title);
    strcpy(newBook->author,author);
    strcpy(newBook->status,status);
    newBook->publicationYear = publicationYear;
    newBook->next = NULL;
    if (method) { // Add by Last in First Out (LIFO) method
        newBook->next = *head;
        *head = newBook;
    }
    else { // Add by First in First Out (FIFO) method
        if (*head == NULL) { // Add to beginning if linked list is empty
            *head = newBook;
        }
        else { // Add to the end of the linked list
            Book* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newBook;
        }
    }
}
/* Function that updates the selected book's
*  title / author / publication year according to isbn number.
*  Takes linked list of books head pointer, isbn number
*  feature name and feature value as parameters.
*/
void updateBook(Book* head, char* isbn, char* feature, char* value) {
    // Declare a temporary book struct pointer
    // and set it to the beginning of the linked list
    Book* temp = head;
    while (temp != NULL) {
        // Check whether parameter isbn and linked list isbn mathces
        if (strcmp(temp->ISBN,isbn) == 0) {
            // Change title
            if (strcmp(feature,"title") == 0) strcpy(temp->title,value);
            // Change author
            if (strcmp(feature,"author") == 0) strcpy(temp->author,value);
            // Change publication year
            if (strcmp(feature,"publicationYear") == 0) temp->publicationYear = atoi(value);
            // Success message
            printf("Book successfully updated.\n");
            return;
        }
        // Jump to next node
        temp = temp->next;
    }
    // Fail message
    printf("Book not found in the linked list. Update failed.\n");
}
/* Function that searches books according to
*  search choice (ISBN / author / title) and
*  corresponding value.
*  Takes linked list of books head pointer, search choice
*  and search value as parameters.
*/
void searchBooks(Book* head, int searchChoice, char* searchValue) {
    // Declare a variable for search count
    int counter = 0;
    // Declare a temporary book struct pointer
    // and set it to the beginning of the linked list
    Book* temp = head;
    // Determine search choice and perform operation
    switch (searchChoice)
    {
    case 0: // Search by ISBN number
        while (temp != NULL) {
            // Print book info if ISBN numbers matches
            if (strcmp(temp->ISBN,searchValue) == 0) {
                printf("ISBN: %s ", temp->ISBN);
                printf("Title: %s ", temp->title);
                printf("Author: %s ", temp->author);
                printf("Publication Year: %d ", temp->publicationYear);
                printf("Status: %s\n", temp->status);
                return;
            }
            // Jump to next node
            temp = temp->next;
        }
        break;
    case 1: // Search by author
        while (temp != NULL) {
            // Print book info if authors matches
            if (strcmp(temp->author,searchValue) == 0) {
                printf("ISBN: %s ", temp->ISBN);
                printf("Title: %s ", temp->title);
                printf("Author: %s ", temp->author);
                printf("Publication Year: %d ", temp->publicationYear);
                printf("Status: %s\n", temp->status);
                counter++;
            }
            // Jump to next node
            temp = temp->next;
        }
        break;
    case 2: // Search by title
        while (temp != NULL) {
            // Print book info if titles matches
            if (strcmp(temp->title,searchValue) == 0) {
                printf("ISBN: %s ", temp->ISBN);
                printf("Title: %s ", temp->title);
                printf("Author: %s ", temp->author);
                printf("Publication Year: %d ", temp->publicationYear);
                printf("Status: %s\n", temp->status);
                counter++;
            }
            // Jump to next node
            temp = temp->next;
        }
        break;
    default:
        break;
    }
    // Print error message if book[s] not found
    if (counter == 0) {
        printf("Book[s] not found!\n");
    }
}
/* Function that reverses the linked list of books.
*  Takes linked list of books head pointer as parameter.
*/
void reverseBookList(Book** head) {
    Book *prev = NULL, *current = *head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
    printf("Book list reversed.\n");
}
/* Function that prints student's borrowed book
*  list according to parameter student id.
*  Takes linked list of students head pointer
*  and student id as parameters.
*/
void showStudentsBorrowedBookList(Student* head, char *id) {
    // Check whether the linked list is empty
    if (head == NULL) {
        printf("Student list is empty.\n");
        return;
    }
    // Declare a temporary student struct pointer
    // and set it to the beginning of the linked list
    Student* temp = head;
    while (temp != NULL) {
        // Print student info if IDs matches
        if (strcmp(temp->ID,id) == 0) {
            printf("Name: %s ", temp->name);
            printf("ID: %s\n", temp->ID);
            // Print borrowed books info
            for (int i = 0; i < temp->borrowedBookCount; i++) {            
                printf("ISBN: %s ", temp->borrowedBooks[i].ISBN);
                printf("Title: %s ", temp->borrowedBooks[i].title);
                printf("Author: %s ", temp->borrowedBooks[i].author);
                printf("Publication Year: %d\n", temp->borrowedBooks[i].publicationYear);
            }
            // Print error message if no borrowed books
            if (temp->borrowedBookCount == 0) printf("No borrowed books found..\n");
            return;
        }
        temp = temp->next;
    }
    // Print error message if student not found
    printf("Student can not found..\n");
}
/* Function that writes linked list of students data
*  to the parameter file.
*  Takes linked list of students head pointer and
*  file name as parameters.
*/
void writeStudentsToFile(Student* head, char* file) {
    // Open file
    FILE *fp = fopen(file,"w");
    // Check whether file opened or not
    if (fp == NULL) {
        printf("File can not opened!\n");
        return;
    }
    // Declare a temporary student struct pointer
    // and set it to the beginning of the linked list
    Student* temp = head;
    while (temp != NULL) {
        // Write student info to the file
        fprintf(fp,"%s,%s,%d",temp->name,temp->ID,temp->borrowedBookCount);
        if (temp->borrowedBookCount > 0){
            // Write borrowed books info to the file
            for (int i = 0; i < temp->borrowedBookCount-1; i++) {
                fprintf(fp,"\n%s,%s,%s,%d",temp->borrowedBooks[i].ISBN,temp->borrowedBooks[i].title,temp->borrowedBooks[i].author,temp->borrowedBooks[i].publicationYear);
            }
            fprintf(fp,"\n%s,%s,%s,%d\n",temp->borrowedBooks[temp->borrowedBookCount-1].ISBN,temp->borrowedBooks[temp->borrowedBookCount-1].title,temp->borrowedBooks[temp->borrowedBookCount-1].author,temp->borrowedBooks[temp->borrowedBookCount-1].publicationYear);
        }
        else {
            if(temp->next != NULL) fprintf(fp,"\n");
        }
        temp = temp->next;
    }
    fclose(fp);
}
/* Function that reads book data from parameter file
*  and fills the linked list of books.
*  Takes linked list of books head pointer and
*  file name as parameters.
*/
void readBooksFromFile(Book** head, char* file){
    // Open file
    FILE *fp = fopen(file,"r");
    // Check whether file opened or not
    if (fp == NULL) {
        printf("File can not opened!\n");
        return;
    }
    while (fgetc(fp) != '\n'); // Skip first line
    // Declare variables for book info
    char ISBN[14];
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    char status[10];
    int publicationYear;
    char c = ' ';
    // Loop in the file until END OF FILE
    while (c != EOF) {
        // Get book info
        fscanf(fp,"%[^,]s",ISBN);
        fgetc(fp);
        fscanf(fp,"%[^,]s",title);
        fgetc(fp);
        fscanf(fp,"%[^,]s",author);
        fgetc(fp);
        fscanf(fp,"%d,",&publicationYear);
        fscanf(fp,"%[^\n]s",status);
        c = fgetc(fp);
        // Add book to the linked list
        addBook(head,ISBN,title,author,publicationYear,0,status);
    }
    // Close file
    fclose(fp);
}
/* Function that writes linked list of books data
*  to the parameter file
*  Takes linked list of books head pointer and
*  file name as parameters.
*/
void writeBooksToFile(Book* head, char* file) {
    // Open file
    FILE *fp = fopen(file,"w");
    // Check whether file opened or not
    if (fp == NULL) {
        printf("File can not opened!\n");
        return;
    }
    // Print indicator line
    fprintf(fp,"ISBN,Title,Author,Publication Year,Status\n");
    // Loop in linked list and print each info to the file
    Book* temp = head;
    while (temp->next != NULL) {
        fprintf(fp,"%s,%s,%s,%d,%s\n",temp->ISBN,temp->title,temp->author,temp->publicationYear,temp->status);
        temp = temp->next;
    }
    fprintf(fp,"%s,%s,%s,%d,%s",temp->ISBN,temp->title,temp->author,temp->publicationYear,temp->status);
    // Close file
    fclose(fp);
}
/* Function that borrows a book to a student
*  according to parameter id and isbn number
*  Takes linked list of books head pointer,
*  linked list of students head pointer,
*  student id and isbn number as parameters.
*/
void borrowBook(Book* head, Student* shead,char* id, char* isbn) {
    Book* current = head;
    // Iterate through the linked list of books
    while (current != NULL) {
        // Check whether the ISBN numbers matches
        if (strcmp(current->ISBN,isbn) == 0) {
            // Check whether the book is available to borrow
            if (strcmp(current->status,"available") == 0) {
                // Iterate through the linked list of students
                Student* temp = shead;
                while (temp != NULL) {
                    // Check whether the IDs matches
                    if (strcmp(temp->ID,id) == 0) {
                        temp->borrowedBookCount += 1; // Increment borrowed book count
                        // Dynamically allocate borrowedBooks array for new book
                        temp->borrowedBooks = (Book*)realloc(temp->borrowedBooks, temp->borrowedBookCount * sizeof(Book));
                        // Copy book information to borrowedBooks array
                        strcpy(temp->borrowedBooks[temp->borrowedBookCount-1].ISBN,current->ISBN);
                        strcpy(temp->borrowedBooks[temp->borrowedBookCount-1].title,current->title);
                        strcpy(temp->borrowedBooks[temp->borrowedBookCount-1].author,current->author);
                        temp->borrowedBooks[temp->borrowedBookCount-1].publicationYear = current->publicationYear;
                        printf("Book successfully borrowed.\n"); // Success message
                        // Set book status to borrowed
                        strcpy(current->status,"borrowed");
                        return;
                    }
                    // Jump to next node
                    temp = temp->next;
                }
                // Fail message
                printf("Student can not found!\n");
                return;
            }
            printf("Book has already borrowed!\n");
            return;
        }
        // Jump to the next node
        current = current->next;
    }
    printf("Book not found!\n");
}
/* Function that returns the book and sets status to 
*  available according to parameter isbn number.
*  Takes linked list of books head pointer,
*  linked list of students head pointer and
*  isbn number as parameters.
*/
void returnBook(Book* head, Student* shead, char* isbn) {
    // Iterate through linked list of books
    Book* current = head;
    while (current != NULL) {
        // Check whether the ISBN numbers matches
        if (strcmp(current->ISBN,isbn) == 0) {
            // Check whether the book is borrowed or not
            if (strcmp(current->status,"borrowed") == 0) {
                // Iterate through linked list of students
                Student* temp = shead;
                while (temp != NULL) {
                    // Loop through borrowedBooks array
                    for (int i = 0; i < temp->borrowedBookCount; i++) {
                        // Check whether the ISBN numbers matches
                        if (strcmp(temp->borrowedBooks[i].ISBN,isbn) == 0) {
                            // Shift books in new order
                            for (int j = i; j < temp->borrowedBookCount-1; j++) {
                                strcpy(temp->borrowedBooks[j].ISBN,temp->borrowedBooks[j+1].ISBN);
                                strcpy(temp->borrowedBooks[j].title,temp->borrowedBooks[j+1].title);
                                strcpy(temp->borrowedBooks[j].author,temp->borrowedBooks[j+1].author);
                                temp->borrowedBooks[j].publicationYear = temp->borrowedBooks[j+1].publicationYear;
                            }
                            temp->borrowedBookCount -=1; // Increment borrowed book count
                            // Reallocate borrowedBooks array and decrease its size
                            temp->borrowedBooks = (Book*)realloc(temp->borrowedBooks, temp->borrowedBookCount * sizeof(Book));
                            // Set book's status to available
                            strcpy(current->status,"available");
                            // Print success message
                            printf("Book successfully returned from %s/%s\n", temp->name, temp->ID);
                            return;
                        }
                    }
                    // Jump to next node
                    temp = temp->next;
                }
                printf("Borrowed student can not found!\n");
                return;
            }
            printf("Book has already returned!\n");
            return;
        }
        // Jump to the next node
        current = current->next;
    }
    printf("Book not found!\n");
}
/* Function that deletes the book from linked lists
*  according to the parameter isbn number.
*  Takes linked list of books head pointer, isbn number and 
*  linked list of students head pointer as parameters.
*/
void deleteBook(Book** head, char* isbn, Student* shead) {
    // Check whether the linked list is empty or not
    if (*head == NULL) {
        printf("Linked list is empty.\n");
        return;
    }
    Book* temp = *head;
    Book* prev = NULL;
    // Check whether the ISBN numbers matches with first element
    if (temp != NULL && strcmp(temp->ISBN,isbn) == 0) {
        // Delete from linked list of students if the book is borrowed
        if (strcmp(temp->status,"borrowed") == 0) {
            returnBook(*head,shead,temp->ISBN);
            writeStudentsToFile(shead,"students.txt");
        }
        // Set head pointer to next element
        *head = temp->next;
        // Deallocate element
        free(temp);
        printf("Book successfully deleted.\n");
        return;
    }
    // Iterate through linked list of books
    while (temp != NULL && strcmp(temp->ISBN,isbn) != 0) {
        prev = temp;
        temp = temp->next;
    }
    // If book not found
    if (temp == NULL) {
        printf("Book not found in the linked list.\n");
        return;
    }
    // If book found
    // Delete from linked list of students if the book is borrowed
    if (strcmp(temp->status,"borrowed") == 0) {
            returnBook(*head,shead,temp->ISBN);
            writeStudentsToFile(shead,"students.txt");
    }
    // Set head pointer to next element
    prev->next = temp->next;
    // Deallocate element
    free(temp);
    printf("Book successfully deleted.\n");
}
/* Function that filters, sorts books and print them.
*  Takes Book pointer, filter choice, filter value 
*  and sort choice as parameters.
*  Filter --> by author / publication year
*  Sort --> by title / author / publication year
*/
void filterAndSortBooks(Book* head, int filterChoice, char* filter, int sortChoice) {
    Book* temp = head;
    // Declare a book array pointer
    Book* filteredBooks = NULL;
    // Declare a variable for filtered book count
    int filteredBookCount = 0;
    if (filterChoice == 0) { // Filter by author
        // Iterate through linked list of books
        while (temp != NULL) {
            // Check whether author matches with filter value
            if (strcmp(temp->author,filter) == 0) {
                // Reallocate filteredBooks array, increment its size by 1
                filteredBooks = (Book*)realloc(filteredBooks,(filteredBookCount+1) * sizeof(Book));
                // Copy book info to the filteredBooks array
                strcpy(filteredBooks[filteredBookCount].ISBN,temp->ISBN);
                strcpy(filteredBooks[filteredBookCount].title,temp->title);
                strcpy(filteredBooks[filteredBookCount].author,temp->author);
                strcpy(filteredBooks[filteredBookCount].status, temp->status);
                filteredBooks[filteredBookCount].publicationYear = temp->publicationYear;
                filteredBookCount += 1; // Increment filtered book count
            }
            // Jump to next node
            temp = temp->next;
        }
    }
    else if (filterChoice == 1) { // Filter by publication year
        // Iterate through linked list of books
        while (temp != NULL) {
            // Check whether publication year matches with filter value
            if (temp->publicationYear == atoi(filter)) {
                // Reallocate filteredBooks array, increment its size by 1
                filteredBooks = (Book*)realloc(filteredBooks,(filteredBookCount+1) * sizeof(Book));
                // Copy book info to the filteredBooks array
                strcpy(filteredBooks[filteredBookCount].ISBN,temp->ISBN);
                strcpy(filteredBooks[filteredBookCount].title,temp->title);
                strcpy(filteredBooks[filteredBookCount].author,temp->author);
                strcpy(filteredBooks[filteredBookCount].status, temp->status);
                filteredBooks[filteredBookCount].publicationYear = temp->publicationYear;
                filteredBookCount += 1; // Increment filtered book count
            }
            // Jump to next node
            temp = temp->next;
        }
    }
    // Sort Books
    if(sortChoice == 0) { // Sort by title
        Book temp;
        // Bubble sort array elements (Alphabetical order of titles)
        for (int i = 0; i < filteredBookCount - 1; i++) {
            for (int j = 0; j < filteredBookCount - i - 1; j++) {
                if (strcmp(filteredBooks[j].title, filteredBooks[j + 1].title) > 0) {
                    temp = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = temp;
                }
            }
        }
    }
    else if(sortChoice == 1) { // Sort by Author
        Book temp;
        // Bubble sort array elements (Alphabetical order of authors)
        for (int i = 0; i < filteredBookCount - 1; i++) {
            for (int j = 0; j < filteredBookCount - i - 1; j++) {
                if (strcmp(filteredBooks[j].author, filteredBooks[j + 1].author) > 0) {
                    temp = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = temp;
                }
            }
        }
    }
    else if(sortChoice == 2) { // Sort by publication year
        Book temp;
        // Bubble sort array elements (newer to older publication year)
        for (int i = 0; i < filteredBookCount - 1; i++) {
            for (int j = 0; j < filteredBookCount - i - 1; j++) {
                if (filteredBooks[j].publicationYear < filteredBooks[j+1].publicationYear) {
                    temp = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = temp;
                }
            }
        }
    }
    // Print filtered books
    for (int i = 0; i < filteredBookCount; i++) {
        printf("%s,%s,%s,%d,%s\n",filteredBooks[i].ISBN,filteredBooks[i].title,filteredBooks[i].author,filteredBooks[i].publicationYear,filteredBooks[i].status);
    }
    // Free filteredBooks array
    free(filteredBooks);
    // Print message if no filtered books
    if (filteredBookCount == 0) {
        printf("No records found!\n");
    }
}
/* Function that updates linked list of students
*  If there is a change in borrowed book's attributes
*/
void updateStudentBook(Student* head, char* isbn, char* feature, char* value) {
    Student* temp = head;
    // Iterate throug linked list of students
    while (temp != NULL) {
        // Loop through borrowedBooks array
        for (int i = 0; i < temp->borrowedBookCount; i++) {
            // Check whether the ISBN numbers matches or not
            if (strcmp(temp->borrowedBooks[i].ISBN,isbn) == 0) {
                // Update corresponding value
                if (strcmp(feature,"title") == 0) strcpy(temp->borrowedBooks[i].title,value);
                if (strcmp(feature,"author") == 0) strcpy(temp->borrowedBooks[i].author,value);
                if (strcmp(feature,"publicationYear") == 0) temp->borrowedBooks[i].publicationYear = atoi(value);
                return;
            }
        }
        // Jump to next node
        temp = temp->next;
    }
}
/* Main function that prints menu
*  Determines selection and performs operation
*  Loops until exit selection
*/
int main() {
    // Declare a book pointer for linked list of books
    Book* head = NULL;
    // Fill linked list of books with data in the txt file
    readBooksFromFile(&head,"books.txt");
    // Declare a book pointer for linked list of students
    Student* shead = NULL;
    // Fill linked list of students with data in the txt file
    readStudentsFromFile(&shead,"students.txt");
    char selection = ' ';
    printf("Welcome to library book management system\n"); // Greeting message
    // Loop until exit
    while (selection != '0') {
        // Print menu
        printf("Select from menu:\n"
        "1-Show Student's Borrowed Book List\n"
        "2-Add Book\n"
        "3-Delete Book\n"
        "4-Update Book\n"
        "5-Filter and Sort Books\n"
        "6-Reverse Book List\n"
        "7-Search Books\n"
        "8-Borrow Book\n"
        "9-Return Book\n"
        "0-Exit\n"
        "> ");
        // Get selection from user
        scanf(" %c", &selection);
        // Check input buffer
        char a = getc(stdin);
        if (a != '\n') {
            while (getc(stdin) != '\n');
            selection = 'x';
        }
        // Declare needed variables for addBook func
        char ISBN[14];
        char title[MAX_LENGTH];
        char author[MAX_LENGTH];
        char status[10];
        int publicationYear;
        int method;
        // Declare needed variables for searchBooks func
        int searchChoice;
        char searchValue[MAX_LENGTH];
        // Declare variables for updateBook func
        char feature[MAX_LENGTH];
        char value[MAX_LENGTH];
        // Declare variable for borrowBook func
        char id[MAX_LENGTH];
        // Declare variables for filterAndSortBooks func
        int filterChoice;
        int sortChoice;
        char filter[MAX_LENGTH];
        // Determine selection and perform operations
        switch (selection) {
        case '1': // Show Student's Borrowed Book List
            printf("Enter Student ID: ");
            scanf("\n%[^\n]s\n", id);
            showStudentsBorrowedBookList(shead,id);
            break;
        case '2': // Add Book
            printf("Enter ISBN number: ");
            scanf("\n%[^\n]s\n", ISBN);
            printf("Enter title: ");
            scanf("\n%[^\n]s\n", title);
            printf("Enter author: ");
            scanf("\n%[^\n]s\n", author);
            printf("Enter publication year: ");
            scanf("%d", &publicationYear);
            printf("Enter method (0: FIFO, 1: LIFO): ");
            scanf("%d",&method);
            // Check invalid method
            while (method != 0 && method != 1) {
                printf("Invalid method! Please enter a valid one: ");
                scanf("%d",&method);
            }
            addBook(&head,ISBN,title,author,publicationYear,method,"available");
            writeBooksToFile(head,"books.txt");
            break;
        case '3': // Delete Book
            printf("Enter ISBN number: ");
            scanf("\n%[^\n]s\n", ISBN);
            deleteBook(&head,ISBN,shead);
            writeBooksToFile(head,"books.txt");
            break;
        case '4': // Update Book
            printf("Enter ISBN number: ");
            scanf("\n%[^\n]s\n", ISBN);
            printf("Enter the name of the feature you want to update (title/author/publicationYear): ");
            scanf("\n%[^\n]s\n", feature);
            printf("Enter the new value for %s: ",feature);
            scanf("\n%[^\n]s\n", value);
            updateBook(head,ISBN,feature,value);
            updateStudentBook(shead,ISBN,feature,value);
            writeBooksToFile(head,"books.txt");
            writeStudentsToFile(shead,"students.txt");
            break;
        case '5': // Filter and Sort Books
            printf("0 --> Filter by Author\n"
            "1 --> Filter by Publication Year\n"
            "> ");
            scanf("%d", &filterChoice);
            //Check invalid filter choice
            while (filterChoice != 0 && filterChoice != 1) {
                printf("Invalid filter choice! Please enter a valid one: ");
                scanf("%d",&filterChoice);
            }
            printf("Enter your filter: ");
            scanf("\n%[^\n]s\n", filter);
            printf("0 --> Sort by Title\n"
            "1 --> Sort by author\n"
            "2 --> Sort by Publication Year (newer to older)\n"
            "> ");
            scanf("%d", &sortChoice);
            // Check invalid sort choice
            while (sortChoice < 0 || sortChoice > 2) {
                printf("Invalid sort choice! Please enter a valid one: ");
                scanf("%d",&sortChoice);
            }
            filterAndSortBooks(head,filterChoice,filter,sortChoice);
            break;
        case '6': // Reverse Book List
            reverseBookList(&head);
            writeBooksToFile(head,"books.txt");
            break;
        case '7': // Search Books
            printf("0 --> Search by ISBN number\n"
            "1 --> Search by author\n"
            "2 --> Search by title\n"
            "> ");
            scanf("%d", &searchChoice);
            // Check invalid search choice
            while (searchChoice < 0 || searchChoice > 2) {
                printf("Invalid selection! Please select a valid one: ");
                scanf("%d", &searchChoice);
            }
            printf("Enter your search value: ");
            scanf("\n%[^\n]s\n", searchValue);
            searchBooks(head,searchChoice,searchValue);
            break;
        case '8': // Borrow Book
            printf("Enter Student ID: ");
            scanf("\n%[^\n]s\n", id);
            printf("Enter ISBN number of the book you want to borrow: ");
            scanf("\n%[^\n]s\n", ISBN);
            borrowBook(head,shead,id,ISBN);
            writeBooksToFile(head,"books.txt");
            writeStudentsToFile(shead,"students.txt");
            break;
        case '9': // Return Book
            printf("Enter ISBN number of the book you want to return: ");
            scanf("\n%[^\n]s\n", ISBN);
            returnBook(head,shead,ISBN);
            writeBooksToFile(head,"books.txt");
            writeStudentsToFile(shead,"students.txt");
            break;
        case '0': // Exit
            printf("Terminating program...\n");
            break;
        default: // Invalid Selection
            printf("Invalid selection!\n");
            break;
        }
    }
    return 0;
}