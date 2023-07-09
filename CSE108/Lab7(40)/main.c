#include <stdio.h>

// PART 1
void clear_sequence(char str[]) {
    int count, index, answer = 0;
    char temp;
    while(1) {
        count = 0;
        while (str[count] != '\0') {
            count++;
        }

        if (count != 0) {  
            index = 0;
            temp = str[index];
            while (str[index] == temp) {
                index++;
            }

            for (int i = 0; i < count; i++) {
                    str[i] = str[i+index];
            }

            for (int i = count-index; i < count; i++) {
                str[i] = '\0';
            }
            answer++;
            printf("%d. Step: %s\n",answer,str);
        }
        else{
            break;
        } 
    }
    printf("The move count required is %d\n", answer);
} // END OF PART 1

// PART 2 (NOT WORKING)
void filter_str(char str[], char rule[]) {
    if (rule[1] == '*') {
        int ccount = 0;
        int c1flag = 0;
        int c2flag = 0;
        for (int i = 0; i < 100; i++) {
            if (str[i] == ' ') {
                if (c2flag == 1) {
                    for (int j = 0; j < ccount; j++) {
                        str[i-j] = '\0';
                    }
                    while (str[i] != ' ') {
                        str[i] = '\0';
                        i++;
                    }
                }
                ccount =0;
                c1flag = 0;
                c2flag = 0;
            }
            else {
                ccount++;
                if (str[i] == rule[0]){
                    c1flag = 1;
                }
                if (c1flag ==1 && str[i] == rule[2]) {
                    c2flag = 1;
                }
                
            }
            
        }
        
    }
    printf("\n%s", str);
    
}
void filterization() {
    char str[100];
    printf("Enter words seperated by spaces:\n");
    fgets(str, 100, stdin);
    char rule[3];
    printf("Enter the rule: ");
    scanf(" %s",rule);

    filter_str(str,rule);
} // END OF PART 2

// PART 3
void foo_min_max(int arr[], int n) {
    n--;
    while(n >= 0) {
        if (arr[n] > arr[n-1])
        {
            arr[n-1] = arr[n];
        }
        n--;
    }
    printf("MAX: %d", arr[0]);
    
}

void part3() {
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    n--;
    while(n >= 0) {
        if (arr[n] > arr[n-1])
        {
            arr[n-1] = arr[n];
        }
        n--;
    }
    printf("MAX: %d", arr[0]);
}


int main() {
    printf("PART 1:\n\n");
    char str[50];
    printf("Please enter string: ");
    scanf(" %s", str);
    clear_sequence(str);
    printf("PART 3:\n\n");
    part3();
}