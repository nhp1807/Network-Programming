#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signalHandler(int signo)
{ // Xử lý sự kiện tiến trình con kết thúc
    int stat;
    printf("signo = %d\n", signo);
    int pid = wait(&stat);
    printf("child %d terminated.\n", pid);
    return;
}

int main()
{
    // Thiết lập thông tin địa chỉ cho socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9000);

    // Tao socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == -1)
    {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }

    // Gan dia chi cho socket
    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }

    // Lang nghe ket noi
    if (listen(server, 5) == -1)
    {
        perror("listen() failed");
        exit(EXIT_FAILURE);
    }

    // Chap nhan ket noi cuar client
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);
    int client = accept(server, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client == -1)
    {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }

    signal(SIGCHLD, signalHandler);
    while (1)
    {
        printf("Waiting for new client\n");
        int client = accept(server, NULL, NULL);
        printf("New client accepted: %d\n", client);
        if (fork() == 0)
        {
            // in child process
            close(server);
            char buf[256];
            while (1)
            {
                int ret = recv(client, buf, sizeof(buf), 0);
                if (ret <= 0)
                    break;
                buf[ret] = 0;
                printf("Received from client %d: %s\n", client, buf);
                send(client, buf, strlen(buf), 0);
            }
            close(client);
            exit(0);
        }
        close(client);
    }
}