#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <sys/ioctl.h>
#include <errno.h>

int main(int argc, char *argv[]){
    int sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(atoi(argv[2]));

    int receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in raddr;
    raddr.sin_family = AF_INET;
    raddr.sin_addr.s_addr = INADDR_ANY;
    raddr.sin_port = htons(atoi(argv[3]));

    bind(receiver, (struct sockaddr *)&raddr, sizeof(raddr));

    fd_set fdread, fdtest;
    FD_ZERO(&fdread);
    FD_SET(STDIN_FILENO, &fdread);
    FD_SET(receiver, &fdread);

    char buf[256];

    while (1)
    {
        fdtest = fdread;
        int ret = select(receiver + 1, )
    }
    
}