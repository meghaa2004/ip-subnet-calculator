# IP Subnet Calculator

## Description
The IP Subnet Calculator is a command-line tool written in C that allows users to calculate network and broadcast addresses based on an IP address and either CIDR notation or a subnet mask. It validates the input and provides detailed information about the network configuration.

## Features
- Convert CIDR notation to subnet mask.
- Convert subnet mask string to a 32-bit integer.
- Validate subnet masks and return equivalent CIDR.
- Calculate and display network range, network ID, broadcast ID, and default gateway.
- Determine the total number of hosts and usable hosts in a subnet.

## Usage Instructions
1. Compile the code using a C compiler (e.g., `gcc ip_subnet.c -o ip_subnet`).
2. Run the executable (`./ip_subnet` on Unix/Linux or `ip_subnet.exe` on Windows).
3. Follow the prompts to enter an IP address and either a CIDR value or a subnet mask.

## Example Input/Output
```
Enter IP address (e.g., 192.168.1.10): 192.168.1.10
Enter 'C' for CIDR or 'M' for Subnet Mask: C
Enter CIDR value (e.g., 24): 24

Subnet Calculator Results:
-------------------------
Network Range: 192.168.1.0 - 192.168.1.255
Network ID: 192.168.1.0
Broadcast ID: 192.168.1.255
Default Gateway: 192.168.1.1
Total Number of Hosts: 256
Number of Usable Hosts: 254
```
