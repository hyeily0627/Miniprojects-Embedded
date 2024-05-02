/*
File : Product Manager.c

Created : 2024-03-13
Auther : 오혜진
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

void error_handling(char* message);

int main() {
    int fd;
    char buf[BUF_SIZE];
    char id[BUF_SIZE], pass[BUF_SIZE];
    //char str[] = "OHHYEJIN";

    printf("---------개인정보 접근---------\n");
    printf("아이디를 입력하세요 : ");
    scanf("%s", id);
    printf("비밀번호를 입력하세요 : ");
    scanf("%s", pass);

    if (strcmp(id, "a") == 0) {
        if (strcmp(pass, "b") == 0) {
            fd = open("myinfo.txt", O_RDONLY);
            if (fd == -1) {
                error_handling("open() error!");
            }

            if (read(fd, buf, sizeof(buf)) == -1) {
                error_handling("read() error");
            }
            printf("%s", buf);
            close(fd);
        }
        else {
            printf("비밀번호가 틀렸습니다\n");
        }
    }
    else {
        printf("입력된 id가 존재하지 않습니다\n");
        return 1;
    }

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
