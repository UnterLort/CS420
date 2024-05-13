/* Kyle Stewart.
 * File: bitFunctions.c
 * Project: bitFunctions
 * Purpose: Contains functions for bitwise operations such as circular shift, reversing bits, extracting every other bit, and converting date to binary and vice versa.
 * Date: 4/5/2024
 */

#include "bitFunctions.h"

unsigned int circular_shift_left(unsigned int value, int n) {
    return (value << n) | (value >> (32 - n));
}

/*
 *
 * Function: reverse_it
 * Reverses bits of the given unsigned integer.
 * num: unsigned integer to be reversed
 * returns: reversed unsigned integer
 */
unsigned int reverse_it(unsigned int num) {
    num = ((num & 0xFFFF0000) >> 16) | ((num & 0x0000FFFF) << 16);
    num = ((num & 0xFF00FF00) >> 8) | ((num & 0x00FF00FF) << 8);
    num = ((num & 0xF0F0F0F0) >> 4) | ((num & 0x0F0F0F0F) << 4);
    num = ((num & 0xCCCCCCCC) >> 2) | ((num & 0x33333333) << 2);
    num = ((num & 0xAAAAAAAA) >> 1) | ((num & 0x55555555) << 1);
    return num;
}

/*
 * Function: every_other_bit
 * Extracts every other bit from the given unsigned integer and returns the result as an unsigned short.
 * num: unsigned integer from which every other bit needs to be extracted
 * returns: result with every other bit extracted as an unsigned short
 */
unsigned short every_other_bit(unsigned int num) {
    unsigned short result = 0;
    for (int i = 0; i < 16; i++) {
        result |= ((num >> (2 * i)) & 1) << i;
    }
    return result;
}

/*
 * Function: date_to_binary
 * Converts given day, month, and year to a binary representation and returns the result as an unsigned short.
 * day: day of the date
 * month: month of the date
 * year: year of the date
 * returns: binary representation of the date as an unsigned short
 */
unsigned short date_to_binary(int day, int month, int year) {
    unsigned short binary = 0;
    binary |= (year - 1980) << 9; // Adjusting for 1980 as the base year
    binary |= month << 5;
    binary |= day;
    return binary;
}

/*
 * Function: date_from_binary
 * Converts given binary date to day, month, and year and stores results in the provided pointers.
 * date: binary representation of the date
 * day: pointer to store the day of the date
 * month: pointer to store the month of the date
 * year: pointer to store the year of the date
 */
void date_from_binary(unsigned short date, int *day, int *month, int *year) {
    *day = date & 0x1F;
    *month = (date >> 5) & 0x0F;
    *year = ((date >> 9) & 0x7F) + 1980; // Re-adjusting to the correct year
}