#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int i = 1;
    printf("Before\n");
    int pid = getpid();
    printf("Main process, pid: %d\n", pid);

    int ret = fork();

    if(ret == 0){
        pid = getpid();
        printf("pid: %d\n", pid);
        printf("%d Child process\n", ret);

        exit(0);
    }
    else{
        pid = getpid();
        printf("pid: %d\n", pid);
        printf("%d Main process\n", ret);

        exit(0);
    }

    return 0;
}