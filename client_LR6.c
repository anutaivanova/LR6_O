#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <string.h>
#include <ctime>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0)
    {
        perror("socket eror");
        exit(1);
    }
    else
    {
        perror("socket create");
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(sock, (struct sockaddr*) & addr, sizeof(addr)) < 0)
    {
        perror("bind eror");
	exit(2);
    }
    else
    {
        perror("bind create");
    }
    close(sock);
    return 0;
}


/*

./test
make
./clientLR6 5555
gcc client_LR6.c -o clientLR6
*/
