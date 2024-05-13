#include <stdio.h>
#include "gol.h"

/*
 * Author: Kyle Stewart
 * Date: 4/17/2024
 * File: golFunctions.c
 * Project: golFunctions
 * Purpose: This file contains functions for simulating the Game of Life.
 * The functions include initializing the grid from a file, printing the current state of the grid,
 * computing the next generation of organisms based on the rules of the game, retrieving statistics of a specific cell in the grid,
 * and printing statistics of the grid. The functions are designed to facilitate the simulation and analysis of the Game of Life.
 */
int initializeGrid(char filename[], GridCell grid[][25], int *size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file.\n");
        return -1;
    }

    // Read the size of the grid from the file
    fscanf(file, "%d", size);

    // Populate the grid with data from the file
    int organismCount = 0; // Initialize organism count
    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            fscanf(file, "%d", &grid[i][j].isAlive);
            grid[i][j].deaths = 0;               // Initialize deaths count
            grid[i][j].births = 0;               // Initialize births count
            grid[i][j].iterations = 0;           // Initialize iterations count
            organismCount += grid[i][j].isAlive; // Count organisms
        }
    }

    fclose(file);

    return organismCount; // Return organism count
}

/* Function to print the current state of the grid
 * 2D array representing the grid
 * Size of the grid (both rows and columns)
 * Current generation number
 * Total number of organisms alive in the grid
 */
void printGrid(GridCell grid[][25], int size, int generation, int totalOrganisms)
{
    printf("Generation %d\n", generation);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", grid[i][j].isAlive);
        }
        printf("\n");
    }
    printf("Total organisms alive: %d\n", totalOrganisms);
}

/* Function to compute the next generation of organisms based on the rules of the game
 * 2D array representing the current generation of the grid
 * 2D array representing the next generation of the grid
 * Size of the grid (both rows and columns)
 * Returns total number of organisms alive in the next generation
 */
int computeNextGeneration(GridCell currentGen[][25], GridCell nextGen[][25], int size)
{
    int totalOrganisms = 0;

    // Iterate over the entire grid, excluding border cells
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 1; j < size - 1; j++)
        {
            // Count the number of alive neighbors
            int neighbors = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    // Skip the current cell
                    if (x == i && y == j)
                        continue;

                    // Count alive neighbors
                    neighbors += currentGen[x][y].isAlive;
                }
            }

            // Apply rules to determine the next state of the cell
            if (currentGen[i][j].isAlive)
            {
                if (neighbors < 2 || neighbors > 3)
                {
                    nextGen[i][j].isAlive = 0;
                    nextGen[i][j].deaths++;
                }
                else
                {
                    nextGen[i][j].isAlive = 1;
                    nextGen[i][j].iterations++;
                    totalOrganisms++;
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    nextGen[i][j].isAlive = 1;
                    nextGen[i][j].births++;
                    nextGen[i][j].iterations++;
                    totalOrganisms++;
                }
                else
                {
                    nextGen[i][j].isAlive = 0;
                }
            }
        }
    }

    // Copy new generation into current generation
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 1; j < size - 1; j++)
        {
            currentGen[i][j] = nextGen[i][j];
        }
    }

    return totalOrganisms;
}

/* Function to retrieve statistics of a specific cell in the grid
 * 2D array representing the grid
 * Row index of the cell
 * Column index of the cell
 * Pointer to an integer storing the death count of the cell
 * Pointer to an integer storing the birth count of the cell
 * Pointer to an integer storing the iteration count of the cell
 */
void getCellStatistics(GridCell grid[][25], int row, int col, int *deathCount, int *birthCount, int *iterationCount)
{
    *deathCount = grid[row][col].deaths;
    *birthCount = grid[row][col].births;
    *iterationCount = grid[row][col].iterations;

    // Adjust birth count only if the cell is alive
    if (grid[row][col].isAlive)
    {
        *birthCount -= 1;
    }
}

/* Function to print statistics of the grid
 * 2D array representing the grid
 * Size of the grid (both rows and columns)
 * Type of statistic to print (DEATHS, BIRTHS, or ITERATIONS)
 */
void printStatistics(GridCell grid[][25], int size, int statistic)
{
    printf("Statistics:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int count;
            switch (statistic)
            {
            case DEATHS:
                count = grid[i][j].deaths;
                break;
            case BIRTHS:
                // Adjust birth count only if the cell is alive
                count = (grid[i][j].isAlive) ? (grid[i][j].births - 1) : grid[i][j].births;
                break;
            case ITERATIONS:
                count = grid[i][j].iterations;
                break;
            }
            printf("(%d,%d)-->deaths=%d,births=%d,iterations=%d\n", i, j, grid[i][j].deaths, count, grid[i][j].iterations);
        }
    }
}