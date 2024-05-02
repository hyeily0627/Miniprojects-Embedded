
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char ISBN[100];
    char author[100];
    char title[100];
    int price;
    struct Book* next;
} Book;

typedef struct {
    Book* head;
} Head;

Head head;

// ���� ��� �Լ�
void addBook() {
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("�޸� �Ҵ� ���� !\n");
        return;
    }
    printf("������ ISBN�� �Է��ϼ���: ");
    scanf("%s", newBook->ISBN);
    printf("������ ���ڸ� �Է��ϼ���: ");
    scanf("%s", newBook->author);
    printf("������ ������ �Է��ϼ���(��������): ");
    scanf("%s", newBook->title);
    printf("������ ������ �Է��ϼ���: ");
    scanf("%d", &newBook->price);

    newBook->next = NULL;

    // ��尡 ����ִ� ��� �� å�� ���� ����, �׷��� ������ ����Ʈ ������ �̵��Ͽ� �߰�
    if (head.head == NULL) {
        head.head = newBook;
    }
    else {
        Book* temp = head.head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    printf("������ ��ϵǾ����ϴ�!\n");
    printf("\n");
}

// ���� �˻� �Լ�
// ++ ISBN, ����, ���ڱ��� �˻��ǵ��� ���� 
void searchBook() {
    char searchentry[100];
    printf("-- ������ �˻��մϴ� -- \n");
    printf("�˻��� �׸��� �����ϼ���!\n");
    printf("1 ISBN \n");
    printf("2 �������� \n");
    printf("3 ���� \n");

    int searchchoice;
    scanf("%d", &searchchoice);

    // �˻� �׸� ���� �� �Է°� �ޱ� 
    char searchinput[100];
    printf("�˻�� �Է��ϼ���: ");
    scanf("%s", searchinput);
    printf("\n");

    Book* temp = head.head;
    int found = 0; // �˻� ����� ã�Ҵ��� ���θ� ��Ÿ���� ����

    while (temp != NULL) {
        if ((searchchoice == 1 && strcmp(temp->ISBN, searchinput) == 0) ||
            (searchchoice == 2 && strcmp(temp->title, searchinput) == 0) ||
            (searchchoice == 3 && strcmp(temp->author, searchinput) == 0))
        {
            found = 1; // �˻� ����� ã������ ǥ��
            printf("������ ã�ҽ��ϴ�!\n\n");
            printf("���� ����: %s\n", temp->title);
            printf("����: %s\n", temp->author);
            printf("ISBN: %s\n", temp->ISBN);
            printf("����: %d\n\n", temp->price);
        }
        temp = temp->next;
    }
    if (!found) { // �˻� ����� ã�� ������ ��쿡�� �ش� ���� ���
        printf("�ش� �˻���� ������ ã�� �� �����ϴ�.\n\n");
    }
}
/*
&&�� ||�� �� �����ڷ�, ���ǽ��� ���ϰ� ����� �����ϴ� �� ���˴ϴ�.
�� �� �������� ���̴� ������ �����ϴ�:

&& (�� AND ������):

�� ���� ������ ��� ���� �� ��ü ǥ������ ���� �˴ϴ�.
��, ���� A�� ���� B�� ��� ���̾�� ��ü ǥ������ ���� �˴ϴ�.
�ϳ��� ������ ���, ��ü ǥ������ ������ �˴ϴ�.
����: A && B

|| (�� OR ������):

�� ���� ���� �� �ϳ� �̻��� ���� �� ��ü ǥ������ ���� �˴ϴ�.
��, ���� A �Ǵ� ���� B �� �ϳ� �̻��� ���̸� ��ü ǥ������ ���� �˴ϴ�.
�� ������ ��� ������ ��쿡�� ��ü ǥ������ ������ �˴ϴ�.
����: A || B

���� searchChoice == 1 && strcmp(temp->title, searchString) == 0������ searchChoice�� 1�̰�,
���ÿ� temp->title�� searchString�� ������ ��쿡 ������ ���� �˴ϴ�.
�ݸ鿡 || �����ڸ� ����ϸ� ���� �� �ϳ��� ���̾ ��ü ǥ������ ���� �ǹǷ�,
�������� �ٸ� ������ �մϴ�.
*/

// ���� ���� �Լ� 
void deleteBook() {
    char delISBN[100];
    printf("������ ������ ISBN�� �Է��ϼ���: ");
    scanf("%s", delISBN);

    Book* current = head.head;
    Book* prev = NULL;

    // ���� å�� ISBN�� �Է��� ISBN�� ��ġ�ϴ� ��� �ش� å�� ����
    while (current != NULL) {
        if (strcmp(current->ISBN, delISBN) == 0) {
            if (prev == NULL) {
                head.head = current->next;		// ��带 �����Ͽ� ù ��° å�� ����
            }
            else {
                prev->next = current->next;		// ���� å�� ���� �����͸� �����Ͽ� å ����
            }
            free(current); 					// ���� å�� �޸� ����
            printf("������ �����Ǿ����ϴ�.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("�ش� ISBN���� ������ ã�� �� �����ϴ�.\n");
}

// ���� ��� �Լ� 
void printBooks() {
    if (head.head == NULL) {
        printf("��ϵ� ������ �����ϴ�.\n");
        return;
    }

    Book* temp = head.head;
    printf("��ϵ� ���� ���:\n");
    while (temp != NULL) {
        printf("���� ����: %s\n", temp->title);
        printf("����: %s\n", temp->author);
        printf("ISBN: %s\n", temp->ISBN);
        printf("����: %d\n", temp->price);
        temp = temp->next;
    }
}

// �����Լ�
int main() {
    int pick;

    // ��� �ʱ�ȭ
    head.head = NULL;

    while (1) {
        printf("***** ��ǰ ���� ���α׷��� �۵��մϴ� *****\n");
        printf("1. ���� ���\n");
        printf("2. ���� �˻�\n");
        printf("3. ���� ����\n");
        printf("4. ���� ���\n");
        printf("0. ����\n");

        printf("�޴��� �����ϼ���(*���ڸ� �Է�) : ");
        scanf("%d", &pick);
        printf("\n");

        if (pick == 1)
            addBook();
        else if (pick == 2)
            searchBook();
        else if (pick == 3)
            deleteBook();
        else if (pick == 4)
            printBooks();
        else if (pick == 0) {
            printf("***** ��ǰ ���� ���α׷��� �����մϴ� *****\n");
            return 0;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �������ּ���!\n");
        }
    }

    return 0;
}