#include "equake.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Author: Kyle Stewart
 * File: equakeFunctions.c
 * Project: Earthquake Data Analysis
 * Purpose: Contains functions for reading earthquake data, calculating statistics, cleaning up memory.
 * Version: 5/5/2024
 */

/* Function: readData
 * Reads earthquake data files, create linked list nodes for each region, populates them with
 * earthquake data.
 *
 * filename: name of the file containing region data.
 * region: pointer to an integer to store the number of regions read.
 *
 * returns: pointer to the head of the linked list of region header.
 */
region_header_t *readData(char *filename, int *regions)
{
    FILE *fp;
    fp = fopen(filename, "r");

    region_header_t *header = NULL;
    region_header_t *prev_node;
    equake_data_t *prev_equake = NULL;
    int regions_counter = 0;

    char time_of_quake[30];
    char location[120];
    int year;
    int month;
    int day;
    float latitude;
    float longitude;
    float magnitude;
    float depth;

    char current_file[20];
    int status = fscanf(fp, "%s", current_file);

    while (status != EOF)
    {
        region_header_t *current_node = (region_header_t *)(malloc(sizeof(struct region_header)));
        current_node->region_name = (char *)(malloc((strlen(current_file) + 1) * sizeof(char)));
        strcpy(current_node->region_name, current_file);
        current_node->next = NULL;
        current_node->data = NULL;

        if (header == NULL)
        {
            header = current_node;
        }
        else
        {
            prev_node->next = current_node;
        }

        FILE *equake_fp;
        equake_fp = fopen(current_node->region_name, "r");

        while (fscanf(equake_fp, "%d %d %d %s %f %f %f %f %s\n", &year, &month, &day, time_of_quake, &latitude, &longitude, &magnitude, &depth, location) != EOF)
        {

            equake_data_t *current_equake = (equake_data_t *)malloc(sizeof(struct equake_data));
            current_equake->timeOfQuake = (char *)(malloc((strlen(time_of_quake) + 1) * sizeof(char)));
            current_equake->location = (char *)(malloc((strlen(location) + 1) * (sizeof(char))));
            strcpy(current_equake->timeOfQuake, time_of_quake);
            strcpy(current_equake->location, location);

            current_equake->year = year;
            current_equake->month = month;
            current_equake->day = day;
            current_equake->latitude = latitude;
            current_equake->longitude = longitude;
            current_equake->magnitude = magnitude;
            current_equake->depth = depth;
            current_equake->next = NULL;

            if (current_node->data == NULL)
            {
                current_node->data = current_equake;
                prev_equake = current_equake;
            }
            if (prev_equake != NULL)
            {
                prev_equake->next = current_equake;
                prev_equake = current_equake;
            }
        }
        fclose(equake_fp);

        prev_node = current_node;
        regions_counter++;
        status = fscanf(fp, "%s", current_file);
    }

    *regions = regions_counter;
    fclose(fp);
    return header;
}

/* Function: printSummary
 * Print summary information about earthquake data for each region to a file.
 *
 * header: Pointer to the head of the linked list of region header.
 * output: name of the output file.
 *
 * return: 1 if successful, 0 otherwise.
 */
int printSummary(region_header_t *header, char *output)
{
    FILE *fp;
    fp = fopen(output, "a");
    if (fp == NULL)
    {
        return 0;
    }

    region_header_t *current = header;
    equake_data_t *current_equake = header->data;
    float min_lat;
    float max_lat;
    float min_long;
    float max_long;
    int num_equakes;
    float min_depth;
    float max_depth;
    float min_magnitude;
    float max_magnitude;
    int max_magnitude_day;
    int max_magnitude_month;
    int max_magnitude_year;
    char time_of_quake[30];
    char location[120];
    while (current != NULL)
    {
        num_equakes = 0;
        current_equake = current->data;
        min_lat = current->data->latitude;
        max_lat = current->data->latitude;
        min_long = current->data->longitude;
        max_long = current->data->longitude;
        min_depth = current->data->depth;
        max_depth = current->data->depth;
        min_magnitude = current->data->magnitude;
        max_magnitude = current->data->magnitude;
        max_magnitude_day = current->data->day;
        max_magnitude_month = current->data->month;
        max_magnitude_year = current->data->year;
        strcpy(time_of_quake, current->data->timeOfQuake);
        strcpy(location, current->data->location);

        while (current_equake != NULL)
        {
            // checking latitude range
            if (current_equake->latitude < min_lat)
            {
                min_lat = current_equake->latitude;
            }
            else if (current_equake->latitude > max_lat)
            {
                max_lat = current_equake->latitude;
            }
            // checking longitude range
            if (current_equake->longitude < min_long)
            {
                min_long = current_equake->longitude;
            }
            else if (current_equake->longitude > min_long)
            {
                max_long = current_equake->longitude;
            }
            // checking depth range
            if (current_equake->depth < min_depth)
            {
                min_depth = current_equake->depth;
            }
            else if (current_equake->depth > max_depth)
            {
                max_depth = current_equake->depth;
            }
            // checking magnitude range
            if (current_equake->magnitude < min_magnitude)
            {
                min_magnitude = current_equake->magnitude;
            }
            else if (current_equake->magnitude > max_magnitude)
            {
                max_magnitude = current_equake->magnitude;
                max_magnitude_day = current_equake->day;
                max_magnitude_month = current_equake->month;
                max_magnitude_year = current_equake->year;
                strcpy(time_of_quake, current_equake->timeOfQuake);
                strcpy(location, current_equake->location);
            }
            num_equakes++;
            current_equake = current_equake->next;
        }

        fprintf(fp, "*************************************************************************************\n");
        fprintf(fp, "EARTHQUAKE SUMMARY FROM DATA FILE: %s\nGeographical Range: Latitudes %f to %f, Longitudes %f to %f\n", current->region_name, min_lat, max_lat, min_long, max_long);
        fprintf(fp, "Total Number of Earthquakes recorded: %d\nDepth Range (Kilometers): %f to %f\n", num_equakes, min_depth, max_depth);
        fprintf(fp, "Magnitude Range: %3.1f to %3.1f\nLargest magnitude of %3.1f occurred on %d/%d/%d %s at: %s\n\n", min_magnitude, max_magnitude, max_magnitude, max_magnitude_month, max_magnitude_day, max_magnitude_year, time_of_quake, location);

        current = current->next;
    }

    fclose(fp);
    return 1;
}

/* Function: buildDailyTotalsArray
 * Build array to store daily earthquake totals for each region.
 *
 * header: Pointer to head of linked list of region header.
 * arr: 2D array to store daily earthquake total.
 */
void buildDailyTotalsArray(region_header_t *header, int arr[][MAX_DAYS])
{
    region_header_t *current = header;
    equake_data_t *current_equake;
    int region_counter = 0;

    while (current != NULL)
    {
        current_equake = current->data;
        while (current_equake != NULL)
        {
            arr[region_counter][(current_equake->day) - 1]++;
            current_equake = current_equake->next;
        }

        current = current->next;
        region_counter++;
    }
}

/* Function: printDailyTotals
 * Print daily earthquake total for each region.
 *
 * arr: 2D array storing daily earthquake total.
 * header: Pointer to head of linked list of region header.
 * region: Number of region.
 */
void printDailyTotals(int arr[][MAX_DAYS], region_header_t *header, int regions)
{
    region_header_t *current = header;
    printf("\n*****************************************************EARTHQUAKE TOTALS FOR THE MONTH BY REGION*****************************************************\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31\n");
    for (int i = 0; i < regions; i++)
    {
        printf("---------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("%20s|", current->region_name);
        for (int j = 0; j < MAX_DAYS; j++)
        {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("***************************************************************************************************************************************************\n");
}

/* Function: buildMagnitudeTotalsArray
 * Build array to store earthquake total by magnitude for each region.
 *
 * header: Pointer to head of linked list of region header.
 * arr: 2D array to store earthquake total by magnitude.
 */
void buildMagnitudeTotalsArray(region_header_t *header, int arr[][MAX_COLS])
{
    int magnitude;
    region_header_t *current = header;
    equake_data_t *current_equake;
    int counter = 0;

    while (current != NULL)
    {
        current_equake = current->data;

        while (current_equake != NULL)
        {
            magnitude = (int)current_equake->magnitude;
            arr[counter][magnitude]++;
            current_equake = current_equake->next;
        }
        counter++;
        current = current->next;
    }
}

/* Function: printMagnitudeTotals
 * Print earthquake totals by magnitude for each region.
 *
 * arr: 2D array storing earthquake totals by magnitude.
 * header: Pointer to head of linked list of region header.
 * region: Number of region.
 */
void printMagnitudeTotals(int arr[][MAX_COLS], region_header_t *header, int regions)
{
    region_header_t *current = header;
    printf("\n**************EARTHQUAKE TOTALS BY MAGNITUDE BY REGION**************\n");
    printf("                    |Magnitude Range: 0 to 10 (increments of 1)\n");
    printf("--------------------------------------------------------------------\n");
    printf("                    |   0   1   2   3   4   5   6   7   8   9\n");
    for (int i = 0; i < regions; i++)
    {
        printf("--------------------------------------------------------------------\n");
        printf("%20s|", current->region_name);
        for (int j = 0; j < MAX_COLS; j++)
        {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
        current = current->next;
    }
    printf("--------------------------------------------------------------------\n");
    printf("********************************************************************\n");
}

/* Function: buildDepthTotalsArray
 * Build an array to store earthquake totals by depth for each region.
 *
 * header: Pointer to head of linked list of region header.
 * arr: 2D array to store earthquake totals by depth.
 */
void buildDepthTotalsArray(region_header_t *header, int arr[][MAX_COLS + 1])
{
    region_header_t *current = header;
    equake_data_t *current_equake;
    int depth;
    int counter = 0;

    while (current != NULL)
    {
        current_equake = current->data;

        while (current_equake != NULL)
        {
            depth = (int)current_equake->depth;
            if (depth < 10)
            {
                arr[counter][0]++;
            }
            else if (depth < 20)
            {
                arr[counter][1]++;
            }
            else if (depth < 30)
            {
                arr[counter][2]++;
            }
            else if (depth < 40)
            {
                arr[counter][3]++;
            }
            else if (depth < 50)
            {
                arr[counter][4]++;
            }
            else if (depth < 60)
            {
                arr[counter][5]++;
            }
            else if (depth < 70)
            {
                arr[counter][6]++;
            }
            else if (depth < 80)
            {
                arr[counter][7]++;
            }
            else if (depth < 90)
            {
                arr[counter][8]++;
            }
            else if (depth < 100)
            {
                arr[counter][9]++;
            }
            else
            {
                arr[counter][10]++;
            }
            current_equake = current_equake->next;
        }
        counter++;
        current = current->next;
    }
}

/* Function: printDepthTotals
 * Print earthquake total by depth for each region.
 *
 * arr: 2D array storing earthquake totals by depth.
 * header: Pointer to head of linked list of region header.
 * region: Number of region.
 */
void printDepthTotals(int arr[][MAX_COLS + 1], region_header_t *header, int regions)
{
    region_header_t *current = header;
    printf("\n***************EARTHQUAKE TOTALS BY DEPTH BY REGION***************\n");
    printf("                    |Depth Range in KM (increments of 10)\n");
    printf("------------------------------------------------------------------\n");
    printf("                    |   0  10  20  30  40  50  60  70  80  90 100+\n");
    for (int i = 0; i < regions; i++)
    {
        printf("------------------------------------------------------------------\n");
        printf("%20s|", current->region_name);
        for (int j = 0; j < MAX_COLS + 1; j++)
        {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
        current = current->next;
    }
    printf("------------------------------------------------------------------\n");
    printf("******************************************************************\n");
}

/* Function: cleanUp
 * Frees memory allocated for region and earthquake data.
 *
 * header: Pointer to head of linked list of region header.
 */
void cleanUp(region_header_t *header, int *dailyTotals, int *magnitudeTotals, int *depthTotals)
{
    region_header_t *region = header;
    region_header_t *temp_region = NULL;
    equake_data_t *equake;
    equake_data_t *temp_equake = NULL;

    while (region != NULL)
    {
        equake = region->data;
        while (equake != NULL)
        {
            free(equake->location);
            free(equake->timeOfQuake);
            temp_equake = equake;
            equake = equake->next;
            free(temp_equake);
        }
        free(region->region_name);
        temp_region = region;
        region = region->next;
        free(temp_region);
    }

    free(dailyTotals);
    free(magnitudeTotals);
    free(depthTotals);
}