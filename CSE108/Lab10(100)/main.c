#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function that generates a dynamically 
*  allocated array with parameter size
*  Fills the array with user inputs
*  Returns array 
*/
int* generate_array(int size) {
    // Dynamically allocate array
    int* array = (int*)malloc(size * sizeof(int));
    // If allocation fails
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // Get values from user
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    // Return array
    return array;
}
// Student struct for part 3
typedef struct {
    int ID;
    int age;
    float gpa;
}Student;

/* Function that dynamically allocates a 
*  Student array with size of 10000. 
*  Randomly fills attributes of student structs
*  Returns average of GPA values
*/ 
float create_students() {
    // Dynamically allocate array
    Student* students = (Student*) malloc(10000 * sizeof(Student));
    float gpa_sum = 0.0; // For summing gpa values
    // Fill attributes
    for (int i = 0; i < 10000; i++) {
        // There is no info about whether id's must be unique or not
        // so i just assigned them random values
        students[i].ID = 100000 + (rand()%100000); // 6 digit random id
        students[i].age = 17+ (rand() % 34); // 18-50 age range
        students[i].gpa = (float)rand() / ((float)RAND_MAX / (4.0)); // 0.0 - 4.0 gpa range
        gpa_sum += students[i].gpa; // Add gpa to gpa_sum
    }
    // Deallocate array
    free(students);
    // Return average of gpa
    return gpa_sum/10000.0;

}

// Main function
int main() {
    // PART 1
    printf("---------------(PART 1)---------------\n");
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* arr = generate_array(size);

    // Find minimum value
    int min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    printf("Min of the array elements: %d\n",min_val);
    free(arr); // Deallocate array

    // PART 2
    printf("---------------(PART 2)---------------\n");
    int size2;
    printf("Enter the size of the array: ");
    scanf("%d", &size2);
    int* arr2 = generate_array(size2);
    int* cumulative_sum = (int*) calloc(size, sizeof(int)); // Dynamically allocate with calloc
    // Fill cumulative sums array
    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < i+1; j++) {
            cumulative_sum[i] += arr2[j];
        }
    }
    // Print first array
    printf("First array: ");
    for (int i = 0; i < size2; i++) {
        printf("%d ",arr2[i]);
    }
    // Print second array
    printf("\nSecond array (cumulative sum): ");
    for (int i = 0; i < size2; i++) {
        printf("%d ",cumulative_sum[i]);
    }
    // Deallocate arrays
    free(cumulative_sum);
    free(arr2);
    // PART 3
    printf("\n---------------(PART 3)---------------\n");
    srand(time(NULL)); // Set seed for random number generator
    // Run function 10000 times and sum average gpas
    float sum_of_averages = 0.0;
    for (int i = 0; i < 10000; i++) {
        sum_of_averages += create_students();
    }
    // Print average of average gpas
    printf("Average GPA of 10.000x10.000 students: %.6f\n", sum_of_averages/10000.0);
    return 0;
}