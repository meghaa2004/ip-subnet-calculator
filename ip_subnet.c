#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert CIDR to subnet mask
unsigned int cidrToMask(int cidr) {
    return ~((1U << (32 - cidr)) - 1);
}

// Function to convert subnet mask string to 32-bit integer
unsigned int maskToInt(char* mask_str) {
    unsigned int octets[4];
    if (sscanf(mask_str, "%u.%u.%u.%u", 
               &octets[0], &octets[1], &octets[2], &octets[3]) != 4) {
        return 0;  // Invalid format
    }
    
    for (int i = 0; i < 4; i++) {
        if (octets[i] > 255) return 0;  // Invalid value
    }
    
    return (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
}

// Function to validate subnet mask and return equivalent CIDR
int maskToCIDR(unsigned int mask) {
    int cidr = 0;
    while (mask) {
        cidr += mask & 1;
        mask >>= 1;
    }
    return cidr;
}

// Function to print IP address
void printIP(unsigned int ip) {
    printf("%d.%d.%d.%d", 
           (ip >> 24) & 0xFF, 
           (ip >> 16) & 0xFF, 
           (ip >> 8) & 0xFF, 
           ip & 0xFF);
}

int main() {
    char ip_input[16];
    char mask_input[16];
    char choice;
    unsigned int ip, mask, network, broadcast;
    long total_hosts, usable_hosts;
    int cidr;

    // Input IP address
    printf("Enter IP address (e.g., 192.168.1.10): ");
    scanf("%15s", ip_input);

    // Ask for input type
    printf("Enter 'C' for CIDR or 'M' for Subnet Mask: ");
    scanf(" %c", &choice);

    // Parse IP address
    unsigned int octets[4];
    if (sscanf(ip_input, "%u.%u.%u.%u", 
               &octets[0], &octets[1], &octets[2], &octets[3]) != 4) {
        printf("Invalid IP address format.\n");
        return 1;
    }

    // Validate IP octets
    for (int i = 0; i < 4; i++) {
        if (octets[i] > 255) {
            printf("Invalid IP address: octet %d exceeds 255.\n", i + 1);
            return 1;
        }
    }
    ip = (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];

    // Process based on user's choice
    if (choice == 'C' || choice == 'c') {
        printf("Enter CIDR value (e.g., 24): ");
        scanf("%d", &cidr);

        if (cidr < 0 || cidr > 32) {
            printf("Invalid CIDR value. Must be between 0 and 32.\n");
            return 1;
        }
        mask = cidrToMask(cidr);
    } else if (choice == 'M' || choice == 'm') {
        printf("Enter Subnet Mask (e.g., 255.255.255.0): ");
        scanf("%15s", mask_input);

        mask = maskToInt(mask_input);
        if (mask == 0) {
            printf("Invalid subnet mask format.\n");
            return 1;
        }

        // Validate if it's a valid subnet mask
        cidr = maskToCIDR(mask);
        if (cidrToMask(cidr) != mask) {
            printf("Invalid subnet mask: must be contiguous 1s followed by 0s.\n");
            return 1;
        }
    } else {
        printf("Invalid choice. Please enter 'C' or 'M'.\n");
        return 1;
    }

    // Calculate network and broadcast addresses
    network = ip & mask;
    broadcast = network | ~mask;

    // Calculate host numbers
    total_hosts = 1U << (32 - cidr);
    usable_hosts = (total_hosts >= 2) ? total_hosts - 2 : 0;

    // Print results
    printf("\nSubnet Calculator Results:\n");
    printf("-------------------------\n");

    printf("Network Range: ");
    printIP(network);
    printf(" - ");
    printIP(broadcast);
    printf("\n");

    printf("Network ID: ");
    printIP(network);
    printf("\n");

    printf("Broadcast ID: ");
    printIP(broadcast);
    printf("\n");

    printf("Default Gateway: ");
    printIP(network + 1);
    printf("\n");

    printf("Total Number of Hosts: %ld\n", total_hosts);
    printf("Number of Usable Hosts: %ld\n", usable_hosts);

    return 0;
}