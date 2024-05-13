#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Kyle Stewart.
 * Project: birthday.
 * 2/26/2024.*/

double birthdayGame(int numberOfTrials, int numberOfPeople, double *monthProbability)
{
    if (numberOfTrials <= 0 || numberOfPeople <= 0)
    {
        *monthProbability = -1;
        return -1;
    }

    srand((unsigned int)time(NULL));

    int sameBirthdayCount = 0;
    int sameMonthCount = 0;

    for (int i = 0; i < numberOfTrials; i++)
    {
        int birthdays[numberOfPeople];
        int birthMonths[numberOfPeople];

        for (int j = 0; j < numberOfPeople; j++)
        {
            birthdays[j] = rand() % 365;
            birthMonths[j] = rand() % 12;
        }

        int foundSameBirthday = 0;
        int foundSameMonth = 0;

        for (int j = 0; j < numberOfPeople - 1; j++)
        {
            for (int k = j + 1; k < numberOfPeople; k++)
            {
                if (birthdays[j] == birthdays[k])
                {
                    foundSameBirthday = 1;
                }
                if (birthMonths[j] == birthMonths[k])
                {
                    foundSameMonth = 1;
                }
                if (foundSameBirthday && foundSameMonth)
                {
                    break;
                }
            }
            if (foundSameBirthday && foundSameMonth)
            {
                break;
            }
        }

        if (foundSameBirthday)
        {
            sameBirthdayCount++;
        }
        if (foundSameMonth)
        {
            sameMonthCount++;
        }
    }

    *monthProbability = (double)sameMonthCount / numberOfTrials;
    return (double)sameBirthdayCount / numberOfTrials;
}

// int main()
// {
//    int trials, people;
//    double monthProb;
//
//    printf("Enter the number of trials: ");
//    scanf("%d", &trials);
//    printf("\nEnter the number of people in the room: ");
//    scanf("%d", &people);
//    printf("\nTrials: %d, People: %d\n", trials, people);
//    printf("Estimated probability for the same birthday: %.6f\n", birthdayGame(trials, people, &monthProb));
//    printf("Estimated probability for the same birth month: %.6f\n", monthProb);
//
//    return 0;
//}