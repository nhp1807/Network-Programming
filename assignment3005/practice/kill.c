#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main()
{
    int cid = fork();
    printf("%d\n", cid);
    if (cid == 0)
    {
        // child process
        printf("Child process started\n");
        printf("Child id: %d\n", getpid());
        while (1)
        {
            sleep(1);
            printf("Child process running\n");
        }
        exit(EXIT_SUCCESS);
    }
    printf("Parent process\n");
    sleep(5);
    kill(cid, SIGKILL); // Nếu không có hàm này, tiến trình con vẫn tiếp tục chạy
    printf("Parent done\n");
    return 0;
}