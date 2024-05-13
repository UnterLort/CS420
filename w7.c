#include <stdio.h>

/* Kyle Stewart.
 * Project: stats_functions.
 * 2/26/2024.*/

#define MAX_VALUES 10000

typedef struct
{
    int positive;
    int negative;
    int zero;
    float average;
} Statistics;

Statistics calculateStatistics(float values[], int numValues)
{
    Statistics stats = {0, 0, 0, 0.0};

    for (int i = 0; i < numValues; i++)
    {
        if (values[i] > 0)
        {
            stats.positive++;
        }
        else if (values[i] < 0)
        {
            stats.negative++;
        }
        else
        {
            stats.zero++;
        }
        stats.average += values[i];
    }

    stats.average /= numValues;

    return stats;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    float values[MAX_VALUES];
    int numValues = 0;

    while (fscanf(file, "%f", &values[numValues]) == 1 && numValues < MAX_VALUES)
    {
        numValues++;
    }

    fclose(file);

    Statistics stats = calculateStatistics(values, numValues);

    printf("Number of positive values: %d\n", stats.positive);
    printf("Number of negative values: %d\n", stats.negative);
    printf("Number of zero values: %d\n", stats.zero);
    printf("Average value: %f\n", stats.average);

    return 0;
}