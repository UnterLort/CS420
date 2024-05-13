/* Kyle Stewart.
 * File: ipAddress.h
 * Project: ipAddress
 * Purpose: Contains declarations for functions and structures related to IP address manipulation and calculation.
 * Date: 4/5/2024
 */

#ifndef IPADDRESS_H
#define IPADDRESS_H

#define MAX_RECORDS 100

typedef struct {
    char ipAddressDot[16];   // For IPv4, maximum 15 characters are required
    char subnetMaskDot[16];  // For IPv4, maximum 15 characters are required
    unsigned int ipAddress;  // 32-bit container for numeric IP address
    unsigned int subnetMask; // 32-bit container for numeric subnet mask
    char networkClass;       // Character indicating network class ('A', 'B', or 'C')
    unsigned int totalSubnets; // Total number of subnets
    unsigned int totalHosts;   // Total number of hosts per subnet
} ipInfo_t;

unsigned int ipDotToNum(const char ipDot[]);
void calculateSubnetsAndHosts(ipInfo_t *info);
int readData(char filename[], ipInfo_t ipArray[]);
void computeValues(ipInfo_t ipArray[], int size);
void printResults(char filename[], ipInfo_t ipArray[], int size);

#endif // IPADDRESS_H