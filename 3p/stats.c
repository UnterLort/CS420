#include <stdio.h>
#include "stats.h"

/* Kyle Stewart.
 * Project: stats.
 * 2/26/2024.*/

int read_data(char filename[], char player[], int field_goals[], int three_pts[], int free_throws[]);
float compute_stats(int field_goals[], int three_pts[], int free_throws[], int size, float *avg_fg, float *avg_tpt, float *avg_ft);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./stats <filename1> [<filename2> ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        char player[50];
        int field_goals[MAXIMUM], three_pts[MAXIMUM], free_throws[MAXIMUM];
        int games_played = read_data(argv[i], player, field_goals, three_pts, free_throws);

        if (games_played > 0)
        {
            float avg_fg, avg_tpt, avg_ft, avg_pts;
            avg_pts = compute_stats(field_goals, three_pts, free_throws, games_played, &avg_fg, &avg_tpt, &avg_ft);

            printf("Statistics for: %s\n", player);
            printf("Total games played: %d\n", games_played);
            printf("Season Averages: Field Goals: %.2f    3 Points: %.2f    Free Throws: %.2f    Points per game: %.2f\n\n", avg_fg, avg_tpt, avg_ft, avg_pts);
        }
        else
        {
            printf("Error reading data from file: %s\n", argv[i]);
        }
    }

    return 0;
}