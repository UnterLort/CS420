/* Kyle Stewart.
 * File: bitTest.c
 * Project: bitTest
 * Purpose: Contains tests for the functions in bitFunctions.c
 * 4/5/2024.
 */

#include <stdio.h>
#include <assert.h>
#include "bitFunctions.h"

int main() {
    // Test circular_shift_left
    unsigned int num1 = 0x80000001;
    assert(circular_shift_left(num1, 1) == 0x00000003);

    // Test reverse_it
    unsigned int num2 = 0xc0000101;
    assert(reverse_it(num2) == 0x80800003);

    // Test every_other_bit
    unsigned int num3 = 0xc0000101;
    assert(every_other_bit(num3) == 0x8011);

    // Test date_to_binary and date_from_binary
    int day, month, year;
    unsigned short packed_date = date_to_binary(7, 12, 1980);
    date_from_binary(packed_date, &day, &month, &year);
    assert(day == 7 && month == 12 && year == 1980);

    printf("All tests passed successfully!\n");
    return 0;
}