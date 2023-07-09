#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char customerName[100];
    int orderID;
    char items[100];
    char orderTime[100];
    struct Order* next;
}Order;

Order* enqueue(Order* queue, char* customerName, int orderID, char* items, char* orderTime) {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    if (newOrder == NULL) {
        printf("Memory allocation failed.\n");
        return queue;
    }
    
    strcpy(newOrder->customerName, customerName);
    newOrder->orderID = orderID;
    strcpy(newOrder->items, items);
    strcpy(newOrder->orderTime, orderTime);
    newOrder->next = NULL;

    printf("Enqueued: ");
    printf("Order ID: %d,", newOrder->orderID);
    printf("Customer Name: %s,", newOrder->customerName);
    printf("Items: %s\n", newOrder->items);
    if (queue == NULL) {
        queue = newOrder;
    } else {
        Order* current = queue;
        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = newOrder;
    }
    
    return queue;
}

Order* dequeue(Order* queue) {
    if (queue == NULL) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }

    Order* dequeuedOrder = queue;
    queue = queue->next;

    free(dequeuedOrder);

    return queue;
}

void updateOrder(Order* queue, int orderID, char* newItems) {
    Order* current = queue;
    
    while (current != NULL) {
        if (current->orderID == orderID) {
            strcpy(current->items, newItems);
            printf("Updated Order: ");
            printf("Order ID: %d,", orderID);
            printf("Customer Name: %s,", current->customerName);
            printf("Items: %s\n", current->items);
            return;
        }
        current = current->next;
    }
    
    printf("Order ID %d can not found.\n", orderID);
}

void display(Order* queue) {
    if (queue == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    
    Order* current = queue;
    while (current != NULL) {
        printf("Order ID: %d,", current->orderID);
        printf("Customer Name: %s,", current->customerName);
        printf("Items: %s\n", current->items);
        current = current->next;
    }
}

int main() {
    Order* queue = NULL;
    
    printf("Enqueue Operation:\n");
    queue = enqueue(queue, "Baris Ozcan", 101, "Burger, Fries, Coke", "8:30");
    printf("\nDisplay by order time:\n");
    display(queue);
    queue = enqueue(queue, "Zehra Bilici", 102, "Pizza, Salad, Ice Cream", "9:00");
    printf("\nDisplay by order time:\n");
    display(queue);
    queue = enqueue(queue, "Mehmet Burak Koca", 103, "Steak, Mashed Potatoes, Salad", "10:00");
    printf("\nDisplay by order time:\n");
    display(queue);
    printf("\nDequeue Operation:\n");
    queue = dequeue(queue);
    printf("\nDisplay by order time:\n");
    display(queue);
    printf("\nUpdate Order:\n");
    updateOrder(queue,102,"Pizza, Salad, Coke");
    printf("\nDisplay by order time:\n");
    display(queue);
    printf("\nDequeue Operation:\n");
    queue = dequeue(queue);
    printf("\nDisplay by order time:\n");
    display(queue);

    return 0;
}