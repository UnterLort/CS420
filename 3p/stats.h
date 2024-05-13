#include <stdio.h>

#define MAXIMUM  82

int read_data(char *filename, char player[], int field_goals[], int three_pts[], int free_throws[]);

float compute_stats(int field_goals[], int three_pts[], int free_throws[], int size, float *avg_fg, float *avg_tpt, float *avg_ft);