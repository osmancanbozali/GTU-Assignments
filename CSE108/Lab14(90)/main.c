#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Order{
    char* customerName;
    int orderID;
    char* items;
    time_t orderTime;
    struct Order* next;
}Order;

Order* enqueue(Order* list, char* customerName, int orderID, char* items, time_t orderTime) {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    if (newOrder == NULL) {
        printf("Memory allocation failed.\n");
        return list;
    }
    
    newOrder->customerName = customerName;
    newOrder->orderID = orderID;
    newOrder->items = items;
    newOrder->orderTime = orderTime;
    newOrder->next = NULL;

    struct tm *localTime;
    localTime = localtime(&orderTime);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", localTime);
    
    printf("Order Added: ");
    printf("Customer Name: %s,", newOrder->customerName);
    printf("Order ID: %d,", newOrder->orderID);
    printf("Items: %s,", newOrder->items);
    printf("Order Time: %s\n", buffer);
    if (list == NULL) {
        list = newOrder;
    } else {
        Order* current = list;
        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = newOrder;
    }
    
    return list;
}

Order* dequeue(Order* list, time_t thresholdTime) {
    if (list == NULL) {
        return NULL;
    }

    Order* previous = NULL;
    Order* current = list;
    while (current != NULL && current->orderTime < thresholdTime) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        list = current->next;
    } else {
        previous->next = current->next;
    }

    return current;
}

void display(Order* list) {
    if (list == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    Order* current = list;
    while (current != NULL) {
        printf("Order ID: %d,", current->orderID);
        printf("Customer Name: %s,", current->customerName);
        printf("Items: %s, ", current->items);
        struct tm *localTime;
        localTime = localtime(&current->orderTime);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", localTime);
        printf("Order Time: %s\n",buffer);
        current = current->next;
    }
}

void serializeFIFO(Order* list, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }
    Order* current = list;
    while (current != NULL) {
        fwrite(current, sizeof(Order), 1, file);
        current = current->next;
    }
    fclose(file);
    printf("FIFO data structure serialized to a binary file.\n");
}

Order* deserializeFIFO(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return NULL;
    }

    Order currentOrder;
    Order* head = NULL;

    while (fread(&currentOrder, sizeof(Order), 1, file) == 1) {
        Order* newOrder = (Order*)malloc(sizeof(Order));
        newOrder->customerName = strdup(currentOrder.customerName);
        newOrder->orderID = currentOrder.orderID;
        newOrder->items = strdup(currentOrder.items);
        newOrder->orderTime = currentOrder.orderTime;
        newOrder->next = NULL;

        if (head == NULL) {
            head = newOrder;
        } else {
            Order* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newOrder;
        }
    }
    fclose(file);
    printf("FIFO data structure deserialized from a binary file.\n");
    return head;
}

void reverseOrders(Order** list) {
    Order* previous = NULL;
    Order* current = *list;
    Order* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    *list = previous;
}

void serializeLIFO(Order* list, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    reverseOrders(&list);
    Order* current = list;
    while (current != NULL) {
        fwrite(current, sizeof(Order), 1, file);
        current = current->next;
    }

    fclose(file);
    reverseOrders(&list);
    printf("LIFO data structure serialized to a binary file.\n");
}

Order* deserializeLIFO(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return NULL;
    }

    Order currentOrder;
    Order* head = NULL;

    while (fread(&currentOrder, sizeof(Order), 1, file) == 1) {
        Order* newOrder = (Order*)malloc(sizeof(Order));
        newOrder->customerName = strdup(currentOrder.customerName);
        newOrder->orderID = currentOrder.orderID;
        newOrder->items = strdup(currentOrder.items);
        newOrder->orderTime = currentOrder.orderTime;
        newOrder->next = NULL;

        if (head == NULL) {
            head = newOrder;
        } else {
            Order* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newOrder;
        }
    }
    fclose(file);
    printf("LIFO data structure deserialized from a binary file.\n");
    return head;
}

int main() {
    Order* list = NULL;
    // Enqueue Operations
    list = enqueue(list, "Ali Yılmaz", 101, " Pizza, Salad, Ice Cream ", time(NULL));
    printf("Linked List Data:\n");
    display(list);
    printf("\n");
    list = enqueue(list, "Ayşe Demir", 102, "Steak, Mashed Potatoes, Salad", (time(NULL)+100));
    list = enqueue(list, "Ahmet Sevim", 102, "Burger, Fries, Coke", (time(NULL)+150));
    printf("Linked List Data:\n");
    display(list);
    printf("\n");
    dequeue(list, time(NULL)+1);
    printf("\n");
    // Serialize FIFO
    serializeFIFO(list,"list_data.bin");
    Order* head = deserializeFIFO("list_data.bin");
    printf("deserialized Linked List Data(FIFO):\n");
    display(head);
    printf("\n");
    // Serialize LIFO
    serializeLIFO(list,"list_data.bin");
    Order* head2 = deserializeLIFO("list_data.bin");
    printf("deserialized Linked List Data(LIFO):\n");
    display(head2);
    return 0;
}