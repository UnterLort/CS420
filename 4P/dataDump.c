/* Kyle Stewart.
 * Project: dataDump.
 * Purpose: Implement the dataDump function to display the content of a file.
 * 3/14/2024.*/

#include <stdio.h>
#include "dataDump.h"

/* Function: dataDump
 * Display the content of a file to stdout similar to the octal dump od command-line utility.
 * Returns the total size in bytes read from the input file, or -1 if the file was not able to open.*/

int dataDump(char *filename)
{
    // Scan file and start array
    FILE *fp;
    fp = fopen(filename, "r");

    // If file is not found return -1
    if (fp == NULL)
    {
        return -1;
    }
    // Else scan all items in file
    else
    {
        // Number of bytes
        int counter = 0;
        // Status of file
        int status = 0;

        printf("%08d", counter);
        status = getc(fp);

        while (status != EOF)
        {
            counter++;
            printf(" %02x", status);

            // Prints a new line every 16 bytes
            if (counter % 16 == 0)
            {
                printf("\n%08d", counter);
            }

            // Scan next byte
            status = getc(fp);
        }

        // Print next line and final count if counter % 16 != 0
        if (counter % 16 != 0)
        {
            printf("\n%08d", counter);
        }

        fclose(fp);

        return counter;
    }
}