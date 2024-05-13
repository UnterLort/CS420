#include "stats.h"

/* Kyle Stewart.
 * Project: stats_functions.
 * 2/26/2024.*/

int read_data(char filename[], char player[], int field_goals[], int three_pts[], int free_throws[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return -1;
    }

    fgets(player, 50, file); // Read player information
    int games_played = 0;
    while (fscanf(file, "%d %d %d", &field_goals[games_played], &three_pts[games_played], &free_throws[games_played]) == 3)
    {
        games_played++;
        if (games_played >= MAXIMUM)
        {
            break;
        }
    }

    fclose(file);
    return games_played;
}

float compute_stats(int field_goals[], int three_pts[], int free_throws[], int size, float *avg_fg, float *avg_tpt, float *avg_ft)
{
    int total_points = 0;
    float avg_pts;

    for (int i = 0; i < size; i++)
    {
        total_points += (field_goals[i] * 2 + three_pts[i] * 3 + free_throws[i]);
    }

    *avg_fg = (float)total_points / size;
    *avg_tpt = (float)total_points / size;
    *avg_ft = (float)total_points / size;
    avg_pts = (float)total_points / size;

    return avg_pts;
}