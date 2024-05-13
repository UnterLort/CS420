/* Kyle Stewart.
 * Project: calSpan.
 * Purpose: Implement calSpan function to compute spans based on user.
 * 3/14/2024.*/

#include <stddef.h>
#include <stdarg.h>
#include "calSpan.h"

/* Function: calSpan
 * Reads sensor data from file and compute spans based on user queries.
 * Returns the number of data items processed, or -1 if file couldn't be opened.*/
int calSpan(int maxSize, char *filename, double data[])
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
        int status = 0;
        int counter = 0;
        char test[10] = "";
        double test_double = 0;
        status = fscanf(fp, "%s", test);

        while (status != EOF && counter < maxSize)
        {
            // Have a pointer, and if the pointers next letter isn't NULL there were letters
            test_double = strtod(test, NULL);

            // Make sure test_double is within value boundaries
            if (test_double < -100 || test_double > 100)
            {
                test_double = 0.0;
            }
            data[counter] = test_double;

            counter++;
            status = fscanf(fp, "%s", test);
        }

        fclose(fp);
        // Take User input
        char input[5] = "";
        int input_num;
        double input_double_num;
        printf("Which minute to query? ");
        scanf("%s", input);
        // While loop will repeat until user types "exit"
        while (strcmp("exit", input) != 0)
        {

            // Special case for query for index 0
            if (strcmp(input, "0") != 0)
            {

                // Convert input to int value
                input_num = strtol(input, NULL, 10);
                // checking if number is a double
                input_double_num = strtod(input, NULL);
                if (input_double_num != (double)input_num)
                {
                    input_num = 0;
                }

                // if input index is the designated corrupt number
                if (input_num == 0)
                {
                    printf("Wrong query input\n");
                }
                // if input index is out of range
                else if (input_num < 0 || input_num >= counter)
                {
                    printf("Query minute out of range\n");
                }
                // if data at index is designated corrupt number
                else if (data[input_num] == 0)
                {
                    printf("Data at minute %d is corrupted\n", input_num);
                }

                else
                {
                    // Iterate back until it finds a higher number
                    int i = input_num;
                    char check = '1';
                    while (check == '1' && i > 0)
                    {
                        i--;
                        if (data[i] != 0)
                        {
                            if (data[i] > data[input_num])
                            {
                                check = '0';
                            }
                            else if (i == 0)
                            {
                                i--;
                            }
                        }
                        else if (i == 0)
                        {
                            i--;
                        }
                    }

                    printf("Data at minute %d is a %d-minute(s) high\n", input_num, input_num - i);
                }
            }
            else
            {
                printf("Data at minute 0 is at a 1 minute high\n");
            }

            printf("Which minute to query? ");
            scanf("%s", input);
        }

        // Return total number of nums
        return counter;
    }
}