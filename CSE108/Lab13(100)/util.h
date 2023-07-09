#ifndef _UTIL_H_
#define _UTIL_H_

struct BST* generateBST(const char* filename);

struct Node* addNode(struct Node* root, double value);

void removeNode(struct BST* bst, int value);

struct Node* searchNode(struct BST* bst, int value);

int countNodes(struct BST* bst);

int getMaxDepth(struct BST* bst);

int countLeafNodes(struct BST* bst);

void printTree(struct BST* bst);

#endif /* _UTIL_H_ */