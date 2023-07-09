// Required Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Declare a struct for linked list nodes
typedef struct Node {
    void* data;
    struct Node* next;
} Node;
// Declare a struct for asset1
typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;
// Declare a struct for asset2
typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;
// Declare a struct for asset3
typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;
// Declare a struct for asset4
typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;
/* Function that creates and inserts a new node
*  to the linked list.
*  Takes head pointer and data pointer as parameters
*/
void createAndInsertNode(Node** head, void* data) {
    // Dynamically Allocate space for new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    // Fill node with parameter data
    newNode->data = data;
    newNode->next = NULL;
    // Add to the beginning if ll is empty
    if (*head == NULL) {
        *head = newNode;
    }
    else { // Loop until end of ll and insert new node
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
/* Function that randomly generates assets with random
*  values (10-20 times each call) and inserts them to
*  the linked list.
*  Takes head pointer as parameter.
*/
void fillLinkedList(struct Node** head) {
    srand(time(NULL)); // Set seed for random number generator
    // Declare a strings array to randomly select strings.
    char strings[12][20] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    // Generate a random number between 10 and 20
    int assetCount = rand() % 11 + 10;

    for (int i = 0; i < assetCount; i++) {
        // Randomly select asset type
        int assetType = rand() % 4;
        // Determine type and create assets
        switch (assetType) {
            case 0: { // Asset 1
                Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
                strcpy(asset->type, "Asset1");
                asset->ivals[0] = rand() % 1000;
                asset->svals[0] = (double)(rand() % 1000) / 10.0;
                createAndInsertNode(head, asset);
                break;
            }
            case 1: { // Asset 2
                Asset2* asset = (Asset2*)malloc(sizeof(Asset2));
                strcpy(asset->type, "Asset2");
                asset->svals[0] = (double)(rand() % 1000) / 10.0;
                asset->svals[1] = (double)(rand() % 1000) / 10.0;
                asset->ivals[0] = rand() % 1000;
                asset->ivals[1] = rand() % 1000;
                createAndInsertNode(head, asset);
                break;
            }
            case 2: { // Asset 3
                Asset3* asset = (Asset3*)malloc(sizeof(Asset3));
                strcpy(asset->type, "Asset3");
                strcpy(asset->string1,strings[rand() % 12]);
                strcpy(asset->string2,strings[rand() % 12]);
                createAndInsertNode(head, asset);
                break;
            }
            case 3: { // Asset 4
                Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
                strcpy(asset->type, "Asset4");
                asset->value1 = (double)(rand() % 100) / 10.0;
                asset->value2 = (float)(rand() % 100) / 10.0f;
                asset->value3 = (double)(rand() % 100) / 10.0;
                createAndInsertNode(head, asset);
                break;
            }
            default:
                break;
        }
    }
}
/* Function that serializes linked list into
*  linkedlist.bin file.
*  Takes head pointer as parameter
*/
void serializeLinkedList(struct Node* head) {
    // Declare file pointer and open file
    FILE* fp = fopen("linkedlist.bin", "wb");
    // Check whether the file opened successfully
    if (fp == NULL) {
        printf("Failed to open the file for writing.\n");
        return;
    }
    // Determine each asset in linked list and write to binary file
    Node* current = head;
    while (current != NULL) {
        if (strcmp(((Asset1*)current->data)->type, "Asset1") == 0) {
            Asset1* asset = (Asset1*)current->data;
            fwrite(asset, sizeof(Asset1), 1, fp);
        } 
        else if (strcmp(((Asset2*)current->data)->type, "Asset2") == 0) {
            Asset2* asset = (Asset2*)current->data;
            fwrite(asset, sizeof(Asset2), 1, fp);
        } 
        else if (strcmp(((Asset3*)current->data)->type, "Asset3") == 0) {
            Asset3* asset = (Asset3*)current->data;
            fwrite(asset, sizeof(Asset3), 1, fp);
        } 
        else if (strcmp(((Asset4*)current->data)->type, "Asset4") == 0) {
            Asset4* asset = (Asset4*)current->data;
            fwrite(asset, sizeof(Asset4), 1, fp);
        }
        // Jump to next node
        current = current->next;
    }
    // Success message
    printf("\nLinked list has successfully serialized and saved to 'linkedlist.bin'\n");
    fclose(fp); // Close file
}
/* Function that deserializes linked list from
*  linkedlist.bin binary file.
*  Takes head pointer as parameter.
*/
void deserializeLinkedList(struct Node** head) {
    // Declare a file pointer and open file
    FILE* fp = fopen("linkedlist.bin", "rb");
    // Check whether the file opened successfully
    if (fp == NULL) {
        printf("Failed to open the file for reading.\n");
        return;
    }

    Node* current = NULL;
    while (1) {
        // Read the asset type from file
        char type[20];
        fread(type, sizeof(char), 20, fp);
        // Break the loop if end of file reached
        if (feof(fp)) {
            break;
        }
        // Revert back file pointer for reading assets
        fseek(fp,-20,SEEK_CUR);
        // Determine and create correct asset with corresponding type
        if (strcmp(type, "Asset1") == 0) {
            // Dynamically allocate space for asset
            Asset1* asset = (Asset1*)malloc(sizeof(Asset1));
            // Read asset data from file
            fread(asset, sizeof(Asset1), 1, fp);
            // Create a new node, fill data from file and insert it to the ll
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = asset;
            newNode->next = NULL;
            if (*head == NULL) {
                *head = newNode;
                current = newNode;
            } 
            else {
                current->next = newNode;
                current = newNode;
            }
        } else if (strcmp(type, "Asset2") == 0) {
            // Dynamically allocate space for asset
            Asset2* asset = (Asset2*)malloc(sizeof(Asset2));
            // Read asset data from file
            fread(asset, sizeof(Asset2), 1, fp);
            // Create a new node, fill data from file and insert it to the ll
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = asset;
            newNode->next = NULL;
            if (*head == NULL) {
                *head = newNode;
                current = newNode;
            } 
            else {
                current->next = newNode;
                current = newNode;
            }
        } else if (strcmp(type, "Asset3") == 0) {
            // Dynamically allocate space for asset
            Asset3* asset = (Asset3*)malloc(sizeof(Asset3));
            // Read asset data from file
            fread(asset, sizeof(Asset3), 1, fp);
            // Create a new node, fill data from file and insert it to the ll
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = asset;
            newNode->next = NULL;
            if (*head == NULL) {
                *head = newNode;
                current = newNode;
            } 
            else {
                current->next = newNode;
                current = newNode;
            }
        } else if (strcmp(type, "Asset4") == 0) {
            // Dynamically allocate space for asset
            Asset4* asset = (Asset4*)malloc(sizeof(Asset4));
            // Read asset data from file
            fread(asset, sizeof(Asset4), 1, fp);
            // Create a new node, fill data from file and insert it to the ll
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = asset;
            newNode->next = NULL;
            if (*head == NULL) {
                *head = newNode;
                current = newNode;
            } 
            else {
                current->next = newNode;
                current = newNode;
            }
        }
    }
    // Success message
    printf("\nLinked List has successfully deserialized from binary file!\n");
    fclose(fp); // Close file
}
/* Function that prints linked list data to terminal
*  Takes head pointer as parameter
*/
void printLinkedList(Node* head) {
    Node* current = head;
    int counter = 1;
    // Determine asset type for each asset in linked list and print them
    while (current != NULL) {
        printf("%2d --> ",counter);
        counter++;
        if (strcmp(((Asset1*)current->data)->type, "Asset1") == 0) {
            Asset1* asset = (Asset1*)current->data;
            printf("Type: Asset1 ivals= %d, svals= %.1f\n", asset->ivals[0], asset->svals[0]);
        } 
        else if (strcmp(((Asset2*)current->data)->type, "Asset2") == 0) {
            Asset2* asset = (Asset2*)current->data;
            printf("Type: Asset2 svals= (%.1f,%.1f), ivals= (%d,%d)\n", asset->svals[0], asset->svals[1], asset->ivals[0], asset->ivals[1]);
        } 
        else if (strcmp(((Asset3*)current->data)->type, "Asset3") == 0) {
            Asset3* asset = (Asset3*)current->data;
            printf("Type: Asset3 string1= %s, string2= %s\n", asset->string1, asset->string2);
        } 
        else if (strcmp(((Asset4*)current->data)->type, "Asset4") == 0) {
            Asset4* asset = (Asset4*)current->data;
            printf("Type: Asset4 value1= %.1f, value2= %.1f, value3= %.1f\n", asset->value1, asset->value2, asset->value3);
        }
        // Jump to next node
        current = current->next;
    }
}
// Main function
int main() {
    // Declare pointers for linked lists
    Node* head = NULL;
    Node* head2 = NULL;
    // Fill first linked list with randomly generated assets
    fillLinkedList(&head);
    // Print linked list data
    printf("Randomly Generated Linked List:\n");
    printLinkedList(head);
    // Serialize linked list to linkedlist.bin file
    serializeLinkedList(head);
    // Deserialize linked list 
    deserializeLinkedList(&head2);
    // Print deserialized linked list data
    printf("\nDeserialized Linked List:\n");
    printLinkedList(head2);
    return 0;
}