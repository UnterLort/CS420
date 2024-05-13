#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Kyle Stewart */

int main()
{
    int rolls;
    printf("How many times do you want to roll the dice? ");
    scanf("%d", &rolls);

    int dice[rolls];

    srand(time(NULL));

    printf("Numbers: ");
    for (int i = 0; i < rolls; i++)
    {
        dice[i] = (rand() % 6) + 1;
        printf("%d", dice[i]);

        if (i != rolls - 1)
        {
            printf(", ");
        }
    }
    printf("\n\nConsecutive Count\n");

    for (int i = 1; i <= 6; i++)
    {
        printf("%-8s: ", i == 1 ? "Ones" : i == 2 ? "Twos"
                                       : i == 3   ? "Threes"
                                       : i == 4   ? "Fours"
                                       : i == 5   ? "Fives"
                                                  : "Sixes");
        int max_c = 0;
        int count = 0;

        for (int j = 0; j < rolls; j++)
        {
            if (dice[j] == i)
            {
                count++;
                if (count > max_c)
                {
                    max_c = count;
                }
            }
            else
            {
                count = 0;
            }
        }
        printf("%d\n", max_c);
    }

    return 0;
}