#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

uint32_t convert_ip(char * ip);
int is_getway(uint32_t mask, uint32_t ip1, uint32_t ip2);
uint32_t random_ip(const uint32_t ip, int count);
void str_ip(uint32_t ip, char* ipAddress);


int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("./main <ip> <mask> <N>\n");
        printf("Example:\n");
        printf("./main 192.168.0.1 255.255.255.0 100\n");
        printf("       ^           ^             ^  \n");
        printf("       ip          mask          N  \n");
        return -1;
    }
    printf("IP-address:\t%s\n", argv[1]);
    printf("mask:\t\t%s\n", argv[2]);
    printf("N:\t\t%s\n", argv[3]);
    char ip_str[20], subnet_str[20];
    uint32_t ip = convert_ip(argv[1]);
    uint32_t mask = convert_ip(argv[2]);
    uint32_t subnet = ip & mask;
    str_ip(subnet, subnet_str);
    printf("subnet:\t\t%s\n", subnet_str);
    const int n = atoi(argv[3]); 
    int i = 0;
    uint32_t new_ip;
    srand(time(NULL));
    printf("\n\n%d new IP-addresses:\n", 20);
    for (i; i < n; i++) {
        new_ip = random_ip(ip, 32);
        str_ip(new_ip, ip_str);
        printf("\t%d)new IP:\t%s\n", i + 1, ip_str);
        if(is_getway(mask, ip, new_ip)) {
            printf("\tThis ip is gateway of subnet: %s\n\n", subnet_str);
        } else {
            printf("\tThis ip isn't gateway of subnet: %s\n\n", subnet_str);
        }
    }
    return 0;
}

uint32_t convert_ip(char *ip) {
    char buf[20];
    uint8_t block;
    uint32_t result = 0;
    strcpy(buf, ip);
    char *pch = strtok(buf, ".");
    while (pch != NULL)
    {
        result <<= 8;
        block = (uint8_t) atoi(pch);
        result = result | block;
        pch = strtok(NULL, ".");
    }
    return result;
}

void str_ip(uint32_t ip, char* ipAddress) {
    uint8_t bytes[4];
    bytes[0] = (ip >> 24) & 0xFF;
    bytes[1] = (ip >> 16) & 0xFF;
    bytes[2] = (ip >> 8) & 0xFF;
    bytes[3] = ip & 0xFF;
    sprintf(ipAddress, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
}

int is_getway(uint32_t mask, uint32_t ip1, uint32_t ip2) {
    return (mask & ip1) == (mask & ip2);
}

uint32_t random_ip(uint32_t ip, int count) {
    int left = rand() % 32;
    uint32_t bit = 1 << left;
    if ((bit & ip) == 0) {
        return ip | bit;
    } else {
        return ip & (~bit);
    }
}