#include <stdio.h>
#include <stdlib.h>

/* Kyle Stewart.
 * Project: new_presidents.
 * 2/23/2024.*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char name[100];
    int count = 0;

    printf("Filename: %s\n\n", argv[1]);

    while (fscanf(file, "%s", name) != EOF) {
        printf("%d. %s\n", ++count, name);
    }

    fclose(file);

    return 0;
}