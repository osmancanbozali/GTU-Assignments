#include <stdio.h>
#include <stdlib.h>

typedef struct ExamPaper {
    char* studentName;
    long studentNumber;
    int score;
    struct ExamPaper* next;
} ExamPaper;

ExamPaper* push(ExamPaper* stack, char* studentName, long studentNumber, int score) {
    ExamPaper* newPaper = (ExamPaper*)malloc(sizeof(ExamPaper));
    newPaper->studentName = studentName;
    newPaper->studentNumber = studentNumber;
    newPaper->score = score;
    printf("Exam Paper Added:\n");
    printf("Student Name: %s, ", newPaper->studentName);
    printf("Student Number: %ld, ", newPaper->studentNumber);
    printf("Score: %d\n\n", newPaper->score);
    newPaper->next = stack;

    stack = newPaper;

    return stack;
}

ExamPaper* pop(ExamPaper* stack) {
    if (stack == NULL) {
        printf("Error: Stack is empty\n");
        return NULL;
    }

    ExamPaper* topPaper = stack;

    stack = stack->next;

    printf("Last Added Exam Paper:\n");
    printf("Student Name: %s, ", topPaper->studentName);
    printf("Student Number: %ld, ", topPaper->studentNumber);
    printf("Score: %d\n\n", topPaper->score);

    free(topPaper);

    return stack;
}

int isEmpty(ExamPaper* stack) {
    if (stack == NULL)
        return 1; // Stack is empty
    else
        return 0; // Stack is not empty
}

void display(ExamPaper* stack) {
    if (stack == NULL) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Exam Papers in the Stack:\n");

    ExamPaper* current = stack;

    while (current != NULL) {
        printf("%s, ", current->studentName);
        printf("Student Number: %ld, ", current->studentNumber);
        printf("Score: %d\n", current->score);
        current = current->next;
    }
}

int main() {
    ExamPaper* stack = NULL;
    stack = push(stack, "Zehra Bilici", 20220000001, 90);
    stack = push(stack, "Bariş Özcan", 20190000001, 85);
    stack = push(stack, "Mehmet Burak Koca", 20180000001, 95);

    stack = pop(stack);

    printf("isEmpty(stack): \n");
    if (isEmpty(stack))
        printf("Stack is empty\n\n");
    else
        printf("Stack is not empty\n\n");

    display(stack);
    
    while (stack != NULL) {
        ExamPaper* temp = stack;
        stack = stack->next;
        free(temp);
    }

    return 0;
}
