#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <linux/ip.h>
#include <string.h>

#include "ipv4.h"

#define mxthread 5



void h_data::HtonData(iphdr* h, char buffer[8]) 
{
    uint16_t u16;
    memcpy(buffer+0, &u16, 2);
    // Convert msg buffer of IP Header in to network short.
    u16 = htons(h->tot_len - h->ihl);
}
