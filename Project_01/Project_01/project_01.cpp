// �����۵�Ȯ��

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

    printf("---------�������� ����---------\n");
    printf("���̵� �Է��ϼ��� : ");
    scanf("%s", id);
    printf("��й�ȣ�� �Է��ϼ��� : ");
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
            printf("��й�ȣ�� Ʋ�Ƚ��ϴ�\n");
        }
    }
    else {
        printf("�Էµ� id�� �������� �ʽ��ϴ�\n");
        return 1;
    }

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
