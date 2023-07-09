#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Customer {
    char name[25];
    int age;
    char priority_group_name[25];
    int priority_level;
    struct Customer* prev;
    struct Customer* next;
} Customer;

Customer* createCustomer(const char* name, int age,char* priority_group_name, int priority_level) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    strcpy(customer->name, name);
    customer->age = age;
    strcpy(customer->priority_group_name, priority_group_name);
    customer->priority_level = priority_level;
    customer->prev = NULL;
    customer->next = NULL;
    return customer;
}

void insertToQueue(Customer** head, Customer* customer) {
    if (*head == NULL) {
        *head = customer;
    }
    else {
        Customer* current = *head;
        while (current != NULL && current->priority_level >= customer->priority_level) {
            current = current->next;
        }

        if (current == *head) {
            customer->next = *head;
            (*head)->prev = customer;
            *head = customer;
        } else if (current == NULL) {
            Customer* tail = *head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = customer;
            customer->prev = tail;
        } else {
            customer->prev = current->prev;
            customer->next = current;
            current->prev->next = customer;
            current->prev = customer;
        }
    }
}
void readFile(char* filename, Customer** head) {
    FILE* file = fopen(filename, "r");
    char name[25];
    int age;
    char priority_group_name[25];
    int priority_level;
    char c = ' ';
    while (c != EOF) {
        fscanf(file, "%[^,]s", name);
        fgetc(file);
        fscanf(file, "%d,", &age);
        fscanf(file, "%[^,]s", priority_group_name);
        fgetc(file);
        fscanf(file, "%d", &priority_level);
        c = fgetc(file);
        // Add to queue
        Customer* customer = createCustomer(name, age, priority_group_name, priority_level);
        insertToQueue(head, customer);
    }

    fclose(file);
}

void writeFile(char* filename, Customer* head) {
    FILE* file = fopen(filename, "w");
    Customer* current = head;
    while (current != NULL && current->next != NULL) {
        fprintf(file, "%s,%d,%s,%d\n", current->name, current->age, current->priority_group_name, current->priority_level);
        current = current->next;
    }
    fprintf(file, "%s,%d,%s,%d", current->name, current->age, current->priority_group_name, current->priority_level);
    fclose(file);
}

void insertCustomer(Customer** head) {
    char name[25];
    int age;
    char priority_group_name[25];
    int priority_level;
    printf("Please insert customer's name: ");
    scanf("%s", name);
    printf("Please insert customer's age: ");
    scanf("%d", &age);
    printf("Please insert customer's Priority Group: ");
    scanf("%s", priority_group_name);
    if (strcmp(priority_group_name,"VIP") == 0) {
        priority_level = 4;
    }
    else if(strcmp(priority_group_name,"OD") == 0) {
        priority_level = 3;
    }
    else if(strcmp(priority_group_name,"VETERAN") == 0) {
        priority_level = 2;
    }
    else if(strcmp(priority_group_name,"NORMAL") == 0) {
        priority_level = 1;
    }
    else {
        printf("Priority Group is invalid.. Setting it to normal.\n");
        strcpy(priority_group_name,"NORMAL");
        priority_level = 1;
    }
    Customer* customer = createCustomer(name, age, priority_group_name, priority_level);
    insertToQueue(head, customer);
    writeFile("customers.txt", *head);
}

void removeCustomer(Customer** head) {
    char name[25];
    printf("Please enter customer's name: ");
    scanf("%s", name);

    if (*head == NULL) {
        printf("Customer not found.\n");
        return;
    }

    Customer* current = *head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            free(current);
            printf("Customer removed: %s\n", name);
            writeFile("customers.txt", *head);
            return;
        }

        current = current->next;
    }

    printf("Customer not found.\n");
}

void displayCustomers(Customer* head) {
    if (head == NULL) {
        printf("No customers in the priority queue.\n");
        return;
    }

    Customer* current = head;
    printf("Priority Queue of Customers:\n");
    while (current != NULL) {
        printf("Name: %s, Age: %d, Priority Group Name: %s, Priority Level: %d\n",
               current->name, current->age, current->priority_group_name, current->priority_level);
        current = current->next;
    }
}

void searchCustomer(Customer* head, const char* name) {
    if (head == NULL) {
        printf("Customer not found.\n");
        return;
    }

    if (strcmp(head->name, name) == 0) {
        printf("Found: %s - Age: %d - Priority Group Name: %s - Priority Level: %d\n",head->name, head->age, head->priority_group_name, head->priority_level);
        return;
    }
    // Recursion
    searchCustomer(head->next, name);
}

void changePriority(Customer* head) {
    char name[25];
    char newPriorityGroup[25];
    int newpriority_level;
    printf("Please enter customer's name: ");
    scanf("%s", name);
    printf("Please enter new Priority Level: ");
    scanf("%d", &newpriority_level);
    switch (newpriority_level)
    {
    case 1:
        strcpy(newPriorityGroup,"NORMAL");
        break;
    case 2:
        strcpy(newPriorityGroup,"VETERAN");
        break;
    case 3:
        strcpy(newPriorityGroup,"OD");
        break;
    case 4:
        strcpy(newPriorityGroup,"VIP");
        break;
    default:
        printf("Invalid Priority Group. Setting it to normal.");
        strcpy(newPriorityGroup,"VIP");
        newpriority_level = 1;
        break;
    }
    Customer* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->priority_level = newpriority_level;
            strcpy(current->priority_group_name,newPriorityGroup);
            printf("Priority level changed successfully..\nNew properties are following:\n");
            printf("Found: %s - Age: %d - Priority Group Name: %s - Priority Level: %d\n",current->name, current->age, current->priority_group_name, current->priority_level);
            writeFile("customers.txt", head);
            return;
        }
        current = current->next;
    }

    printf("Customer not found.\n");
}

int main() {
    Customer* head = NULL;
    readFile("customers.txt", &head);
    char selection;
    while (selection != '6') {
        printf("Welcome to ABC Bank\n\n"
        "1-Insert new customer\n"
        "2-Remove customer\n"
        "3-Display customers in order\n"
        "4-Search a customer\n"
        "5-Change priority settings\n"
        "6-Exit\n\n"
        "Please select an option: ");
        scanf(" %c",&selection);
        char name[25];
        switch (selection)
        {
        case '1':
            insertCustomer(&head);
            break;
        case '2':
            removeCustomer(&head);
            break;
        case '3':
            displayCustomers(head);
            break;
        case '4':
            printf("Please enter customer's name: ");
            scanf("%s", name);
            searchCustomer(head, name);
            break;
        case '5':
            changePriority(head);
            break;
        case '6':
            printf("Terminating program...\n");
            break;
        default:
            printf("Invalid selection!\n");
            break;
        }
    }
    
    return 0;
}
