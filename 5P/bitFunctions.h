/* Kyle Stewart.
 * File: bitFunctions.h
 * Project: bitFunctions
 * Purpose: Contains function prototypes for bitwise operations such as circular shift, bit reversal, extracting every other bit, and date conversion.
 * Date: 4/5/2024
 */

#ifndef BIT_FUNCTIONS_H
#define BIT_FUNCTIONS_H

unsigned int circular_shift_left(unsigned int value, int n);

unsigned int reverse_it(unsigned int num);

unsigned short every_other_bit(unsigned int num);

unsigned short date_to_binary(int day, int month, int year);

void date_from_binary(unsigned short date, int *day, int *month, int *year);

#endif /* BIT_FUNCTIONS_H */