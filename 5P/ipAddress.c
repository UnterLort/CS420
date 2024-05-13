/* Kyle Stewart.
 * File: ipAddress.c
 * Project: ipAddress
 * Purpose: Contains functions for IP address manipulation and calculation.
 * 4/5/2024.
 */

#include "ipAddress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function: ipDotToNum
 * Converts IP address from dotted decimal notation to a 32-bit unsigned integer.
 * ipDot: IP address in dotted decimal notation
 * returns: 32-bit unsigned integer representation of the IP address
 */
unsigned int ipDotToNum(const char ipDot[]) {
    char ipCopy[16];
    strcpy(ipCopy, ipDot);
    unsigned int num = 0;
    int i = 0;
    char *token = strtok(ipCopy, ".");
    while (token != NULL) {
        num |= atoi(token) << (24 - i * 8);
        token = strtok(NULL, ".");
        i++;
    }
    return num;
}

/*
 * Function: calculateSubnetsAndHosts
 * Calculates total number of subnets and hosts based on the given subnet mask.
 * info: pointer to the ipInfo_t structure containing the subnet mask
 */
void calculateSubnetsAndHosts(ipInfo_t *info) {
    unsigned int subnetBits = 0;
    unsigned int subnetMask = info->subnetMask;
    while (subnetMask & 1) {
        subnetBits++;
        subnetMask >>= 1;
    }
    info->totalSubnets = 1 << subnetBits;
    info->totalHosts = (1 << (32 - subnetBits)) - 2;
}

/*
 * Function: readData
 * Reads IP address and subnet mask data from a file, converts them to numeric format, and stores them in the ipArray.
 * filename: name of the file to be read
 * ipArray: array of ipInfo_t structures to store the IP address and subnet mask data
 * returns: number of records read
 */
int readData(char filename[], ipInfo_t ipArray[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%15s %15s", ipArray[count].ipAddressDot, ipArray[count].subnetMaskDot) != EOF) {
        ipArray[count].ipAddress = ipDotToNum(ipArray[count].ipAddressDot);
        ipArray[count].subnetMask = ipDotToNum(ipArray[count].subnetMaskDot);
        count++;
        if (count >= MAX_RECORDS) {
            printf("Maximum records reached\n");
            break;
        }
    }
    fclose(file);
    return count;
}

/*
 * Function: computeValues
 * Computes network class, total subnets, and total hosts for each IP address in the ipArray.
 * ipArray: array of ipInfo_t structures containing the IP address and subnet mask data
 * size: number of records in the ipArray
 */
void computeValues(ipInfo_t ipArray[], int size) {
    for (int i = 0; i < size; i++) {
        unsigned int firstByte = ipArray[i].ipAddress >> 24;
        if (firstByte >= 1 && firstByte <= 126) {
            ipArray[i].networkClass = 'A';
        } else if (firstByte >= 128 && firstByte <= 191) {
            ipArray[i].networkClass = 'B';
        } else {
            ipArray[i].networkClass = 'C';
        }
        calculateSubnetsAndHosts(&ipArray[i]);
    }
}

/*
 * Function: printResults
 * Prints results of IP address manipulation and calculation to a file.
 * filename: name of the file to be written
 * ipArray: array of ipInfo_t structures containing the IP address, subnet mask, network class, total subnets, and total hosts
 * size: number of records in the ipArray
 */
void printResults(char filename[], ipInfo_t ipArray[], int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %s %u %u %c %u %u\n", ipArray[i].ipAddressDot, ipArray[i].subnetMaskDot,
                ipArray[i].ipAddress, ipArray[i].subnetMask, ipArray[i].networkClass,
                ipArray[i].totalSubnets, ipArray[i].totalHosts);
    }
    fclose(file);
}