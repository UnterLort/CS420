#ifndef GOL_H
#define GOL_H

/*
 * Author: Kyle Stewart
 * Date: 4/17/2024
 * File: gol.h
 * Project: gol
 * Purpose: This header file contains the structure definition for a cell in the Game of Life grid.
 * This header file is to provide the necessary structure and function declarations for simulating the Game of Life.
 */

// Structure definition for a cell in the Game of Life grid
typedef struct
{
    int isAlive;    // Flag indicating whether the cell is alive (1) or dead (0)
    int deaths;     // Counter of deaths that occurred in this cell
    int births;     // Counter of births that occurred in this cell
    int iterations; // Counter of iterations the cell has been alive
} GridCell;

// Constants for statistics types
#define DEATHS 1     // Constant representing deaths statistic
#define BIRTHS 2     // Constant representing births statistic
#define ITERATIONS 3 // Constant representing iterations statistic

// Function prototypes
int initializeGrid(char filename[], GridCell grid[][25], int *size);
void printGrid(GridCell grid[][25], int size, int generation, int totalOrganisms);
int computeNextGeneration(GridCell currentGen[][25], GridCell nextGen[][25], int size);
void getCellStatistics(GridCell grid[][25], int row, int col, int *deathCount, int *birthCount, int *iterationCount);
void printStatistics(GridCell grid[][25], int size, int statistic);

#endif