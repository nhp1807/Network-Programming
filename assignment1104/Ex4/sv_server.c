#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define MSSV_LENGTH 10
#define NAME_LENGTH 50
#define DATE_LENGTH 20
#define GPA_LENGTH 4

struct student_info {
    char mssv[MSSV_LENGTH + 1];
    char name[NAME_LENGTH + 1];
    char date[DATE_LENGTH + 1];
    float gpa;
};

int main(int argc, char *argv[])
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == -1)
    {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(atoi(argv[1]));

    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)))
    {
        perror("bind() failed");
        return 1;        
    }

    if (listen(listener, 5))
    {
        perror("listen() failed");
        return 1;
    }

    printf("Khoi tao server thanh cong!\n");

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    int client = accept(listener, 
        (struct sockaddr *)&client_addr, 
        &client_addr_len);

    printf("Accepted socket %d from IP: %s:%d\n", 
        client,
        inet_ntoa(client_addr.sin_addr),
        ntohs(client_addr.sin_port));


    // Khai bao ten file
    char *log_file = argv[2];

    // Khai bao student
    struct student_info student;

    // Mo file de ghi thong tin client gui
    FILE *f = fopen(log_file,"a");

    // Tao string luu thong tin client gui
    char buf[BUFFER_SIZE];    
    memset(buf,0,BUFFER_SIZE);

    // Tao bien lay thoi gian
    time_t current_time;
    struct tm *time_info;
    
    int ret;

    while (1){
        ret = recv(client, buf, BUFFER_SIZE, 0);
        if (ret <= 0){
            break;
        }
        
        if (ret < sizeof(buf)){
            buf[ret] = 0;
        }

        memset(&student, 0, sizeof(student));
        strncpy(student.mssv, buf, MSSV_LENGTH);
        strncpy(student.name, buf + MSSV_LENGTH, NAME_LENGTH);
        strncpy(student.date, buf + MSSV_LENGTH + NAME_LENGTH, DATE_LENGTH);
        student.gpa = atof(buf + MSSV_LENGTH + NAME_LENGTH + DATE_LENGTH);

        time(&current_time);
        time_info = localtime(&current_time);

        // Thong tin client gui
        // Hien thi ra man hinh
        fflush(stdin);
        printf("Received data at %04d-%02d-%02d %02d:%02d:%02d:\n",
           time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday,
           time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
        printf("  MSSV: %s\n", student.mssv);
        printf("  Name: %s\n", student.name);
        printf("  Date of birth: %s\n", student.date);
        printf("  GPA: %.2f\n", student.gpa);
        
        // Ghi vao log_file
        fprintf(f, "%04d-%02d-%02d %02d:%02d:%02d %s %s %s %.2f\n",
            time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday,
            time_info->tm_hour, time_info->tm_min, time_info->tm_sec,
            student.mssv, student.name, student.date, student.gpa);
        fflush(f);
        
        printf("Saved");
    }
    
    fclose(f);

    close(client);
    close(listener);
}