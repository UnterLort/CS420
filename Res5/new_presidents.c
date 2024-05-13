#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kyle Stewart.
 * Project: new_presidents.
 * 2/23/2024.*/

#define MAX_NAME_LENGTH 100

int compareNames(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <inputfile1> <inputfile2> <outputfile>\n", argv[0]);
        return 1;
    }

    FILE *inputFile1 = fopen(argv[1], "r");
    FILE *inputFile2 = fopen(argv[2], "r");
    FILE *outputFile = fopen(argv[3], "w");

    if (inputFile1 == NULL || inputFile2 == NULL || outputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

    char name[MAX_NAME_LENGTH];
    char *names[1000];
    int count = 0;

    while (fscanf(inputFile1, "%s", name) != EOF) {
        names[count] = strdup(name);
        count++;
    }

    while (fscanf(inputFile2, "%s", name) != EOF) {
        names[count] = strdup(name);
        count++;
    }

    qsort(names, count, sizeof(char *), compareNames);

    for (int i = 0; i < count; i++) {
        fprintf(outputFile, "%s\n", names[i]);
        free(names[i]); // Free the memory allocated by strdup
    }

    fclose(inputFile1);
    fclose(inputFile2);
    fclose(outputFile);

    return 0;
}