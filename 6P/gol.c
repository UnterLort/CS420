#include <stdio.h>
#include "gol.h"

/*
 * Author: Kyle Stewart
 * Date: 4/17/2024
 * File: gol.c
 * Project: gol
 * Purpose: This file contains the main function for simulating the Game of Life.
 * The main function reads the input filename from the command-line arguments.
 * Initializes the grid from the input file, computes and prints the initial state of the grid, performs iterations to compute.
 */
int main(int argc, char *argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 2)
    {
        printf("Usage: %s <input_filename>\n", argv[0]);
        return 1; // Return error code
    }

    // Declare variables
    GridCell grid[25][25];    // Grid array
    GridCell nextGen[25][25]; // New generation array
    int size;                 // Size of the grid
    int generation = 1;       // Current generation number
    int totalOrganisms;       // Total number of organisms alive

    // Initialize the grid from the input file
    if (initializeGrid(argv[1], grid, &size) == -1)
    {
        return 1; // Return error code if initialization fails
    }

    // Compute and print the initial state of the grid
    totalOrganisms = computeNextGeneration(grid, nextGen, size);
    printGrid(grid, size, generation, totalOrganisms);

    // Perform iterations until there are no more organisms or 5 consecutive generations have the same number of organisms
    int consecutiveSameTotal = 0;
    int prevTotalOrganisms = totalOrganisms;
    while (totalOrganisms > 0 && consecutiveSameTotal < 5)
    {
        generation++;
        totalOrganisms = computeNextGeneration(grid, nextGen, size);
        printGrid(grid, size, generation, totalOrganisms);
        // Check if the total number of organisms remains the same as the previous generation
        if (totalOrganisms == prevTotalOrganisms)
        {
            consecutiveSameTotal++;
        }
        else
        {
            consecutiveSameTotal = 0;
            prevTotalOrganisms = totalOrganisms;
        }
    }

    // Print statistics for deaths, births, and iterations
    printStatistics(grid, size, DEATHS);
    printStatistics(grid, size, BIRTHS);
    printStatistics(grid, size, ITERATIONS);

    return 0; // Return success code
}