#include <stdio.h>
#include <math.h>

/* Kyle Stewart.
 * Project: ctof.
 * 2/15/2024.*/

int main()
{
    int start_temp, end_temp;

    printf("This Program converts temperature values from Celsius to Fahrenheit\n");
    printf("and also factors in Wind Chill and Heat Index at the appropriate temperatures\n\n");

    char input_range[20];
    printf("Please enter the range of temperature values (in Celsius between -20 and 50) to be converted: \n");
    printf("Input temperature range: ");
    fgets(input_range, 20, stdin);

    sscanf(input_range, "%d to %d", &start_temp, &end_temp);

    printf("\nThe temperature range for conversion is: %d to %d\n", start_temp, end_temp);

    printf("\nCelsius to Fahrenheit with Wind Chill factor\n");
    printf("------------------------------------------------"
           "-----------------------------------------------\n");
    printf("   Celsius   Fahrenheit   5mph    10mph    15mph    "
           "20mph    25mph    30mph    35mph    40mph\n");
    printf("------------------------------------------------"
           "-----------------------------------------------\n");

    for (int celsius = start_temp; celsius <= end_temp; celsius++)
    {
        if (celsius < -20 || celsius >= 50 || celsius == 10)
        {
            printf("   %6d   %9.2f        X        X        X        X        X        "
                   "X        X        X\n",
                   celsius, (celsius * 9 / 5.0) + 32);
        }
        else
        {
            printf("   %6d   %9.2f   ", celsius, (celsius * 9 / 5.0) + 32);
            for (int wind_speed = 5; wind_speed <= 40; wind_speed += 5)
            {
                double fahrenheit = (celsius * 9 / 5.0) + 32;
                // Calculate wind chill
                if (fahrenheit <= 50)
                {
                    double wind_chill = 35.74 + 0.6215 * fahrenheit - 35.75 * pow(wind_speed, 0.16) + 0.427 * fahrenheit * pow(wind_speed, 0.16);
                    printf("%6.2f   ", wind_chill);
                }
                else
                {
                    printf("     X   ");
                }
            }
            printf("\n");
        }
        printf("----------------------------------------------"
               "-------------------------------------------------\n");
    }

    printf("\nCelsius to Fahrenheit with Heat Index factor\n");
    printf("------------------------------------------------"
           "-----------------------------------------------\n");
    printf("   Celsius   Fahrenheit    40%%      50%%      60%%      "
           "70%%      80%%      90%%     100%%\n");
    printf("------------------------------------------------"
           "-----------------------------------------------\n");

    for (int celsius = start_temp; celsius <= end_temp; celsius++)
    {
        double fahrenheit = (celsius * 9 / 5.0) + 32;
        if (celsius <= 26 || celsius > 50)
        {
            printf("   %6d   %9.2f        X        X        X        X        X        "
                   "X        X\n",
                   celsius, fahrenheit);
        }
        else
        {
            printf("   %6d   %9.2f   ", celsius, fahrenheit);
            for (int humidity = 40; humidity <= 100; humidity += 10)
            {
                double heat_index = -42.379 + 2.04901523 * fahrenheit + 10.14333127 * humidity - 0.22475541 * fahrenheit * humidity - 6.83783 * powf(10, -3) * powf(fahrenheit, 2) - 5.481717 * powf(10, -2) * powf(humidity, 2) + 1.22874 * powf(10, -3) * powf(fahrenheit, 2) * humidity + 8.5282 * powf(10, -4) * fahrenheit * powf(humidity, 2) - 1.99 * powf(10, -6) * powf(fahrenheit, 2) * powf(humidity, 2);
                printf("%6.2f   ", heat_index);
            }
            printf("\n");
        }
        printf("------------------------------------------------"
               "-----------------------------------------------\n");
    }

    return 0;
}