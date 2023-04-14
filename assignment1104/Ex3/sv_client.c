#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define ID_LENGTH sizeof(int)
#define NAME_LENGTH 50
#define DOB_LENGTH 20
#define GPA_LENGTH sizeof(float)

struct student_info {
    int id;
    char name[NAME_LENGTH];
    char dob[DOB_LENGTH];
    float gpa;
};

int main(int argc, char *argv[]){
    // Khai bao cau truc
    struct student_info student;

    // Khai bao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    // Ket noi den server
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1){
        printf("Khong ket noi duoc den server!");
        return 1;
    }

    // Gui tin nhan den server
    char buf[ID_LENGTH + NAME_LENGTH + DOB_LENGTH + GPA_LENGTH];
    while(1){
        printf("Nhap du lieu sinh vien: \n");

        printf("ID: ");
        scanf("%d", &student.id);
        fflush(stdin);
        printf("Name: ");
        scanf("%s", student.name);
        fflush(stdin);
        printf("Date of birth: ");
        scanf("%s", student.dob);
        fflush(stdin);
        printf("GPA: ");
        scanf("%f", &student.gpa);
        fflush(stdin);

        int offset = 0;
        memcpy(buf + offset, &student.id, ID_LENGTH);
        offset += ID_LENGTH;
        memcpy(buf + offset, student.name, NAME_LENGTH);
        offset += NAME_LENGTH;
        memcpy(buf + offset, student.dob, DOB_LENGTH);
        offset += DOB_LENGTH;
        memcpy(buf + offset, &student.gpa, GPA_LENGTH);

        printf("Tiep tuc? (Y/N): ");
        scanf("%s", buf);
        fflush(stdin);
        if(strncmp(buf, "N", 1) == 0){
            break;
        }
        send(client, buf, sizeof(buf), 0);
    }

    close(client);
    return 0;
}