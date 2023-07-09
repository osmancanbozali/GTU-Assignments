#include <stdio.h>
#include <stdlib.h>
#include "util.h"

struct Node {
double Value;
struct Node* Leftnode; struct Node* Rightnode; };

struct BST {
struct Node* root;
};

struct Node* createNode(double value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->Value = value;
    newNode->Leftnode = NULL;
    newNode->Rightnode = NULL;
    return newNode;
}

struct Node* addNode(struct Node* root, double value) {
    struct Node* newNode = createNode(value);
    
    if (root == NULL) {
        return newNode;
    }
    
    struct Node* current = root;
    struct Node* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        
        if (value < current->Value) {
            current = current->Leftnode;
        } 
        else if (value > current->Value) {
            current = current->Rightnode;
        } 
        else {
            printf("Duplicate values are not allowed.\n");
            free(newNode);
            return root;
        }
    }
    
    if (value < parent->Value) {
        parent->Leftnode = newNode;
    } else {
        parent->Rightnode = newNode;
    }
    
    return root;
}

struct BST* generateBST(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

    struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
    if (bst == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    bst->root = NULL;

    int value;
    if (fscanf(file, "%d", &value) == 1) {
        bst->root = createNode(value);
    } else {
        printf("Invalid file format.\n");
        exit(1);
    }

    while (fscanf(file, "%d", &value) == 1) {
        addNode(bst->root, value);
    }

    fclose(file);
    return bst;
}

struct Node* searchNode(struct BST* bst, int value) {
    if (bst == NULL || bst->root == NULL) {
        return NULL;
    }

    struct Node* current = bst->root;
    while (current != NULL) {
        if (value < current->Value) {
            current = current->Leftnode;
        } else if (value > current->Value) {
            current = current->Rightnode;
        } else {
            return current;
        }
    }

    return NULL;
}

void inorderPrint(struct Node* node) {
    if (node != NULL) {
        inorderPrint(node->Leftnode);
        printf("%f ", node->Value);
        inorderPrint(node->Rightnode);
    }
}

void preorderPrint(struct Node* node) {
    if (node == NULL) {
        return;
    }

    printf("%f ", node->Value);
    preorderPrint(node->Leftnode);
    preorderPrint(node->Rightnode);
}

void printTree(struct BST* bst) {
    int choice;
    printf("0 -> Print inorder\n"
    "1 -> Print preorder\n");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1) {
        printf("Invalid choice! Please enter a valid one: ");
        scanf("%d", &choice);
    }
    if (choice == 0) inorderPrint(bst->root);
    if (choice == 1) preorderPrint(bst->root);
}

int countNodesHelper(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    return 1 + countNodesHelper(node->Leftnode) + countNodesHelper(node->Rightnode);
}

int countNodes(struct BST* bst) {
    if (bst == NULL || bst->root == NULL) {
        return 0;
    }

    return countNodesHelper(bst->root);
}

int getMaxDepthHelper(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    int leftDepth = getMaxDepthHelper(node->Leftnode);
    int rightDepth = getMaxDepthHelper(node->Rightnode);

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

int getMaxDepth(struct BST* bst) {
    if (bst == NULL || bst->root == NULL) {
        return 0;
    }

    return getMaxDepthHelper(bst->root);
}

int countLeafNodesHelper(struct Node* node) {
    if (node == NULL) {
        return 0;
    }

    if (node->Leftnode == NULL && node->Rightnode == NULL) {
        return 1; // Leaf node found
    }

    int leftLeaves = countLeafNodesHelper(node->Leftnode);
    int rightLeaves = countLeafNodesHelper(node->Rightnode);

    return leftLeaves + rightLeaves;
}

int countLeafNodes(struct BST* bst) {
    if (bst == NULL || bst->root == NULL) {
        return 0;
    }

    return countLeafNodesHelper(bst->root);
}

struct Node* findMinNode(struct Node* node) {
    struct Node* current = node;
    while (current->Leftnode != NULL) {
        current = current->Leftnode;
    }
    return current;
}

struct Node* removeNodeHelper(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->Value) {
        root->Leftnode = removeNodeHelper(root->Leftnode, value);
    } else if (value > root->Value) {
        root->Rightnode = removeNodeHelper(root->Rightnode, value);
    } else {
        if (root->Leftnode == NULL) {
            struct Node* temp = root->Rightnode;
            free(root);
            return temp;
        } else if (root->Rightnode == NULL) {
            struct Node* temp = root->Leftnode;
            free(root);
            return temp;
        }

        struct Node* temp = findMinNode(root->Rightnode);
        root->Rightnode = temp->Rightnode;
        root->Rightnode = removeNodeHelper(root->Rightnode, temp->Value);
    }

    return root;
}

void removeNode(struct BST* bst, int value) {
    if (bst == NULL || bst->root == NULL) {
        printf("Empty tree. No node to remove.\n");
        return;
    }

    bst->root = removeNodeHelper(bst->root, value);
}