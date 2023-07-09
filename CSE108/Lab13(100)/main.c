// NOTE: removeNode function does not work properly
#include <stdio.h>
#include "util.h"

struct BST {
struct Node* root;
};

int main() {
    char selection = ' ';
    while (selection != '9') {
        printf("1. Generate Binary Search Tree from file\n"
        "2. Add Node\n"
        "3. Remove Node\n"
        "4. Search Node\n"
        "5. Print Binary Search Tree\n"
        "6. Print Node Count\n"
        "7. Print Max Depth\n"
        "8. Print Leaf Node Count\n"
        "9. Exit\n"
        "> ");
        scanf(" %c", &selection);
        // Check input buffer
        char a = getc(stdin);
        if (a != '\n') {
            while (getc(stdin) != '\n');
            selection = 'x';
        }
        struct BST* bst;
        struct Node* foundNode;
        char filename[50];
        double value;
        switch (selection)
        {
        case '1':
            printf("Enter filename: ");
            scanf("%s", filename);
            bst = generateBST(filename);
            break;
        case '2':
            printf("Enter value: ");
            scanf("%lf", &value);
            addNode(bst->root,value);
            break;
        case '3':
            printf("Enter value: ");
            scanf("%lf", &value);
            removeNode(bst,value);
            break;
        case '4':
            printf("Enter value: ");
            scanf("%lf", &value);
            foundNode = searchNode(bst, value);
            if (foundNode != NULL) printf("Node with value %f found at adress %p.\n", value,foundNode);
            else printf("Node with value %f not found.\n", value);
            break;
        case '5':
            printTree(bst);
            printf("\n");
            break;
        case '6':
            printf("Number of Nodes in Binary Search Tree: %d\n", countNodes(bst));
            break;
        case '7':
            printf("Depth of Binary Search Tree: %d\n", getMaxDepth(bst));
            break;
        case '8':
            printf("Number of Leaf Nodes in Binary Search Tree: %d\n", countLeafNodes(bst));
            break;
        case '9':
            printf("Terminating Program...\n");
            break;
        default:
            printf("Invalid selection!\n");
            break;
        }
    }
    return 0;
}