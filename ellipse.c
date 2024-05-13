#include <math.h>
#include <stdio.h>
/* Kyle Stewart */

int main()
{
    const float pi = 3.14159f; // Define the constant value of pi
    float a;                  // Declare a variable to store the first input value
    float b;                  // Declare a variable to store the second input value

    scanf("%f", &a);            // Read the first input value from the user
    printf("The number %.2f\n", a); // Display the first input value to the user
    scanf("%f", &b);            // Read the second input value from the user
    printf("The number %.2f\n", b); // Display the second input value to the user

    float ramanujan = pi * 3 * (a + b) - sqrtf((3 * a + b) * (a + 3 * b)); // Calculate the Ramanujan expression
    printf("The number %.2f\n", ramanujan);                                   // Display the result of the Ramanujan expression

    const float h = powf((a - b), 2) / powf((a + b), 2);                            // Calculate the value of h
    float ramanujan1 = pi * (a + b) * 1 + 3 * h / (10 + sqrtf(4 - 3 * h)); // Calculate another Ramanujan expression
    printf("The number %.2f\n", ramanujan1);                                          // Display the result of the second Ramanujan expression

    float s = 1.5f;                                                   // Define the value of s
    float muir = 2 * pi * powf(powf(a, s) / 2 + powf(b, s) / 2, 1 / s); // Calculate the Muir expression
    printf("The number %.2f\n", muir);                                   // Display the result of the Muir expression

    float hudson = 0.25f * pi * (a + b) * 3 * (1 + h / 4) + 1 / (1 - h / 4); // Calculate the Hudson expression
    printf("The number %.2f\n", hudson);                                        // Display the result of the Hudson expression

    float s1 = logf(2) / logf(pi / 2);                         // Calculate the value of s1
    float holder = 4 * powf(powf(a, s1) + powf(b, s1), 1 / s1); // Calculate the Holder expression
    printf("The number %.2f\n", holder);                         // Display the result of the Holder expression

    float s2 = 0.825056f;                                                                             // Define the value of s2
    float david = 4 * (a + b) - 2 * (4 - pi) * a * b / powf(powf(a, s2) / 2 + powf(b, s2) / 2, 1 / s2); // Calculate the David expression
    printf("The number %.2f\n", david);                                                                  // Display the result of the David expression

    return 0;
}