/* NOTE: Compile and run this code using the makefile in the folder
*  in order to run without errors! Just type 'make' to the terminal 
*/

// Required libraries
#include <stdio.h>
#include <string.h>
// Constant values
#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 13 // +1 for '\0' char
#define THRESHOLD 30
// Function checks whether the parameter char exists in parameter array
int is_in_array(char c, char arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (c == arr[i] || c < -1) {
            return 1; // Exists
        }
    }
    return 0; // Not exists
}
// Function that coppies a string from source to destination
void copy_string(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
// Function that reads the dictionary file and stores words in dict array
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]) {
    // Declare variables for word count(specified in the first line of dictionary file)
    int num_word;
    // Open file
    FILE *fp = fopen(file_name,"r");
    if (fp == NULL) {
        return -1; // Negative return means error
    }
    // Get word count from first line
    while (getc(fp) != '=');
    fscanf(fp,"%d", &num_word);
    // Skip first line
    while (getc(fp) != '\n');
    // Declare a char variable for reading the file
    char c;
    // Declare a variable for word count
    int word_counter = 0;
    for (word_counter = 0; ( c = getc(fp)) != EOF ; word_counter++) {
        int letter_counter;
        // Get word char by char
        for (letter_counter = 0; c != ' '; letter_counter++) {
            dict[word_counter][letter_counter] = c;
            c = getc(fp);
        }
        // Add \0 at the end of the string
        dict[word_counter][letter_counter] = '\0';
        // Skip to the next line
        while ((c = getc(fp)) != '\n' && c != EOF);
    }
    // Close file
    fclose(fp);
    // Add sentinel value at the end of the dict array
    dict[word_counter][0] = '-';
    dict[word_counter][1] = '\0';

    // Compare specified word count with read word count, if not same return -1 (ERROR)
    if (word_counter != num_word) {
        return -1;
    }
    // Return word count
    return word_counter;
}
// Function that reads input file and stores words in words array
int read_text(const char * text_file, const char * ignore_file, char words[][MAX_WORD_SIZE]) {
    // Declare a char array for all punctuation chars
    char punctuation_chars[34] = {' ', '\n', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|' ,'}', '~'};
    // Declare a pointer variable for file operations
    FILE *fp;
    // Open ignore words file
    fp = fopen(ignore_file,"r");
    if (fp == NULL) {
        return -1; // Negative return means error
    }
    // Declare a variable for ignore word count
    int ignore_word_count= 0;
    // Find word count in the file
    char c;
    while ((c = getc(fp)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            ignore_word_count++;
        }
    }
    // Declare an string array for ignore words
    char ignore_words[ignore_word_count][MAX_WORD_SIZE];
    // Set file pointer to starting point of file
    fseek(fp,0,SEEK_SET);
    // Get ignore words from file
    for (int i = 0; i < ignore_word_count; i++) {
        fscanf(fp,"%s", ignore_words[i]);
    }
    // Close file
    fclose(fp);

    // Open input file
    fp = fopen(text_file,"r");
    if (fp == NULL) {
        return -1; // Negative return means error
    }
    // Declare a variable for word count
    int word_counter = 0;
    c = getc(fp);
    for (word_counter = 0; c != EOF ; word_counter++) {
        // Skip if the char is punctuation char  
        while (is_in_array(c,punctuation_chars,13) == 1) {
            c = getc(fp);
        }
        // Declare a variable for letter count
        int letter_counter;
        // Declare a flag variable for punctuation check
        int flag = 1;
        // Get word char by char
        for (letter_counter = 0; flag == 1 && letter_counter < MAX_WORD_COUNT; letter_counter++) {
            words[word_counter][letter_counter] = c;
            c = getc(fp);
            // Set flah to 0 if char is a punctuation char
            if (is_in_array(c,punctuation_chars,34) == 1) {
                flag = 0;
            }
            
        }
        // Add \0 at the end of the string
        words[word_counter][letter_counter] = '\0';
        // Check whether the word is in ignore word array or not
        for (int i = 0; i < ignore_word_count; i++) {
            // If the word exists in the ignore word array, decrement word count by 1
            if (strcmp(words[word_counter],ignore_words[i]) == 0) {
                word_counter--;
                break;
            }
        }
        // Skip possible punctuation chars
        c = getc(fp);
        while (is_in_array(c,punctuation_chars,34) == 1) {
            c = getc(fp);
        }
    }
    // Add sentinel value at the end of words array
    words[word_counter][0] = '-';
    words[word_counter][1] = '\0';
    // Return word count
    return word_counter;
}
// Function that reads vector values of words in dictionary file
int read_vectors(const char * file_name, double vectors[][400], int size) {
    // Declare pointer variable for file operations
    FILE *fp;
    // Open file
    fp = fopen(file_name,"r");
    if (fp == NULL) {
        return -1; // Negative return means error
    }
    // Get vector count from the first line of file
    char c;
    for (int i = 0; i < 2; i++) {
        while ((c = getc(fp)) != '=');        
    }
    int vector_count;
    fscanf(fp,"%d", &vector_count);
    // Get vector values and store them in vectors array
    for (int word = 0; word < size; word++) {
        while ((c = getc(fp)) != ' ');
        for (int vector_num = 0; vector_num < vector_count; vector_num++) {
            fscanf(fp,"%lf", &vectors[word][vector_num]);
        }        
    }
    // Set sentinel value
    vectors[size][0] = -1.0;
    // Close file
    fclose(fp);
    // Return vector count
    return vector_count;
}
/* Function that calculates dissimilarity 
*  between parameter word and all words in 
*  dict array. If dissimilarity is smaller
*  than threshold, returns nearest word with
*  w2 parameter.
*/
double dissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, double vectors[][400] ) {
    // Declare a variable for vector count and get value from vectors array
    int vector_count;
    for ( vector_count = 0; vectors[0][vector_count] != 0; vector_count++);
    // Declare a variable for w1's index
    int w1i;
    // Find w1's index
    for ( w1i = 0; strcmp(w1,dict[w1i]) != 0; w1i++);
    // Declare variable for nearest distance
    double distance = threshold;
    // Declare a variable for nearest word's index
    int index = 0;
    // Loop in dict array
    for (int word = 0; dict[word][0] != '-'; word++) {
        // Skip same words
        if (word == w1i) {
            continue;
        }
        // Declare a variable for sum of distances
        double sum = 0;
        // Calculate distance
        for (int i = 0; i < vector_count; i++) {
            sum += (vectors[w1i][i]-vectors[word][i])*(vectors[w1i][i]-vectors[word][i]);
        }
        // If sum is smaller distance, set it to new distance and new nearest word's index
        if (sum < distance)
        {
            distance = sum;
            index = word;
        }
    }
    // Copy the nearest word to w2 parameter
    copy_string(w2,dict[index]);
    // Return distance
    return distance; 
}
// Function that scales occurances and prints */+ according to state and occurance counts
int histogram(const char words[][MAX_WORD_SIZE], const int occurrences[],char hist[][MAX_WORD_SIZE+5+20]) {
    // Declare a variable for max occurance
    int max = occurrences[0];
    // Declare a variable for word count
    int count = 0;
    // Find maximum occurance
    for (count = 1; words[count][0] != '-' ; count++) {
        if (occurrences[count] > max) {
            max = occurrences[count];
        }
    }
    // Calculate scale
    int scale = (max+(max%20))/20;
    // Set scale to 1 if result of calculation is 0
    if (scale == 0) {
        scale = 1;
    }
    // Fill hist array for each word and occurance
    for (int i = 0; i < count; i++) {
        // Declare a variable for indicator char
        char indicator;
        // Determine whether the word is exact or nearest word
        if (hist[i][0] == '+') {
            indicator = '+';
        }
        else {
            indicator = '*';
        }
        // If occurances > 0, add needed amount of indicator char to hist array
        if (occurrences[i] > 0) {
            int j;
            for (j = 0; j < (occurrences[i]/scale); j++) {
                hist[i][j] = indicator;
            }
            hist[i][j] = '\0'; // End string
        }
        // If occurances = 0, fill hist array with NO MATCHES message
        else {
            char message[11] = "NO MATCHES";
            for (int j = 0; j < 11; j++)
            {
                hist[i][j] = message[j];
            }
            hist[i][11] = '\0'; // End string
        }
    }
    // Return scale
    return scale;
}

int main(int argc, char *argv[]) {
    // Declare arrays for user words, input file words and dictionary words
    char user_words[MAX_WORD_COUNT][MAX_WORD_SIZE];
    char input_words[300000][MAX_WORD_SIZE];
    char dict[300000][MAX_WORD_SIZE];
    // Get word(s) from user
    char c;
    printf("Enter word(s): ");
    int wcount = 0; // User entered word count
    // Get words from input
    for (wcount = 0; c != '\n'; wcount++) {
        scanf("%s", user_words[wcount]);
        c = getchar();
    }
    user_words[wcount][0] = '-'; // Sentinel value at the end

    // Fill input words array with words in input.txt
    int input_word_count = read_text("input.txt","ignore.txt",input_words);
    if (input_word_count < 0) {
        printf("ERROR! While reading input file\n");
    }
    else {
        // Fill dict array with words in dictionary file
        int dict_word_count = read_dict("dictionary.txt",dict);
        if (dict_word_count < 0) {
            printf("ERROR! While reading dictionary file\n");
        }
        else {
            // Fill vectors array with vector values of words in dict file 
            double vectors[dict_word_count+1][400];
            int vector_count = read_vectors("dictionary.txt", vectors, dict_word_count);
            if (vector_count < 0) {
                printf("ERROR! While reading vector values from dictionary file\n");
            }
            else {
                // Single word
                if (wcount == 1) {
                    // Declare a variable for occurance count
                    int occurance = 0;
                    // Calculate occurance
                    for (int i = 0; i < input_word_count; i++) {
                        if (strcmp(user_words[0],input_words[i]) == 0) {
                            occurance++;
                        }
                    }
                    // Print result if occurace is greater than 0
                    if (occurance != 0) {
                        printf("\"%s\" appears in \"input.txt\" %d times\n",user_words[0],occurance);
                    }
                    // If occurance = 0
                    else {
                        // Check whether the word is in dictionary or not
                       int is_in_dict = 0;
                       for (int i = 0; i < dict_word_count; i++) {
                        if (strcmp(user_words[0],dict[i]) == 0) {
                            is_in_dict++;
                            break;
                        }
                       }
                       // If the word exists in dictionary
                       if (is_in_dict == 1) {
                        // Find nearest word
                        char nearest[MAX_WORD_SIZE];
                        double min_dis = dissimilarity(user_words[0],nearest,dict,THRESHOLD,vectors);
                        if (min_dis < THRESHOLD) {
                            // Calculate nearest word's occurance
                            for (int i = 0; i < input_word_count; i++) {
                                if (strcmp(nearest,input_words[i]) == 0) {
                                    occurance++;
                                }
                            }
                            // If nearest word exists in input file
                            if (occurance != 0) {
                                printf("\"%s\" doesn't appear in \"input.txt\" but \"%s\" appears %d times\n",user_words[0],nearest,occurance);
                            }
                            // If nearest word does not exists in input file
                            else {
                                printf("\"%s\" doesn't appear in \"input.txt\"\n",user_words[0]);
                            }
                        }
                        // If there are no nearest word found
                        else {
                            printf("\"%s\" doesn't appear in \"input.txt\"\n",user_words[0]);
                        }
                       }
                       // If the word is does not exists in dictionary file
                       else{
                        printf("\"%s\" doesn't appear in \"input.txt\"\n",user_words[0]);
                       }  
                    }
                }
                // Multiple user input
                else {
                    // Declare an array for histogram
                    char hist[wcount][MAX_WORD_SIZE+25];
                    // Declare an array for each word's occurances
                    int occurances[wcount];
                    // Calculate each word's occurances
                    for (int i = 0; i < wcount; i++) {
                        int occurance = 0;
                        for (int j = 0; j < input_word_count; j++) {
                            if (strcmp(user_words[i],input_words[j]) == 0) {
                                occurance++;
                            }
                        }
                        if (occurance == 0) {
                            // Determine whether the word exists in dictionary
                            int is_in_dict = 0;
                            for (int m = 0; m < dict_word_count; m++) {
                                if (strcmp(user_words[i],dict[m]) == 0) {
                                    is_in_dict++;
                                    break;
                                }
                            }
                            // If the word exist in dictionary
                            if (is_in_dict == 1) {
                                // Find closest word
                                char nearest[MAX_WORD_SIZE];
                                double min_dis = dissimilarity(user_words[i],nearest,dict,THRESHOLD,vectors);
                                // If there is a enough similar word exists
                                if (min_dis < THRESHOLD) {
                                    // Calculate occurance of nearest word
                                    for (int k = 0; k < input_word_count; k++) {
                                        if (strcmp(nearest,input_words[k]) == 0) {
                                            occurance++;
                                        }
                                    }
                                    occurances[i] = occurance;
                                    hist[i][0] = '+'; // Add indicator value to hist array
                                }
                                else {
                                    // There are no close enough word (NO MATCHES)
                                    occurances[i] = 0;
                                }
                            }
                            else{
                                // The word does not exists in dictionary (NO MATCHES)
                                occurances[i] = 0;
                            } 
                        }
                        // If occurances > 0
                        else {
                            occurances[i] = occurance;
                        }
                    }
                    // Print scale and fill hist array with histogram function
                    printf("\nScale: %d\n",histogram(user_words,occurances,hist));
                    // Print histogram
                    for (int i = 0; i < wcount; i++) {
                        // Calculate word size for alignment
                        int wsize;
                        for (wsize = 0; user_words[i][wsize] != '\0'; wsize++);
                        // Check indicator
                        if (hist[i][0] == '+') {
                            // Determine nearest word
                            char nearest[MAX_WORD_COUNT];
                            dissimilarity(user_words[i],nearest,dict,THRESHOLD,vectors);
                            // Calculate nearest word's size for alignment
                            int nsize;
                            for (nsize = 0; nearest[nsize] != '\0'; nsize++);
                            // Print histogram for nearest word occurance with alignment 
                            printf("\"%s-->%s\"%*s%s (%d)\n",user_words[i],nearest,20-(wsize+nsize)," ",hist[i],occurances[i]);
                        }
                        // Print words occurance with alignment
                        else {
                            printf("\"%s\"%*s%s (%d)\n",user_words[i],23-wsize," ",hist[i],occurances[i]);
                        }                
                    }             
                }           
            }
        }
    }
    return 0;
}