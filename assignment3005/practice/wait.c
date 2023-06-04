#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    if (fork() == 0)
    {
        // tiến trình con
        printf("Child process started\n");
        printf("Child id: %d\n", getpid());
        sleep(5);
        printf("Child process done\n");
        exit(EXIT_SUCCESS);
    }
    // tiến trình cha
    printf("Waiting for the child process\n");
    int status;
    int pid = wait(&status); // dừng và đợi cho đến khi tiến trình con kết thúc
    printf("Child process %d terminated with status %d\n", pid, status);
    return 0;
}