#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// å ����ü ����
typedef struct Book {
    char ISBN[100];
    char author[100];
    char title[100];
    int price;
    int isRented;       // �뿩���θ� ��Ÿ���� ����
    struct Book* next;
} Book;

// å ����ü ��� ����
typedef struct {
    Book* head;
} Head;

Head head;

// ���� ��� �Լ�
void addBook() {
    Book* newBook = (Book*)malloc(sizeof(Book)); // ���ο� å�� ���� �޸� �Ҵ�
    if (newBook == NULL) {
        printf("�޸� �Ҵ� ���� !\n"); // �޸� �Ҵ� ���� �� ���� �޽��� ���
        return;
    }
    printf("������ ISBN�� �Է��ϼ���: ");
    scanf("%s", newBook->ISBN); // ISBN �Է� ����
    printf("������ ���ڸ� �Է��ϼ���: ");
    scanf("%s", newBook->author); // ���� �Է� ����
    printf("������ ������ �Է��ϼ���(��������): ");
    scanf("%s", newBook->title); // ���� �Է� ����
    printf("������ ������ �Է��ϼ���: ");
    scanf("%d", &newBook->price); // ���� �Է� ����

    newBook->isRented = 0; // �� å�� �̴뿩 ���·� �ʱ�ȭ
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
// ���� �˻� 
void searchAndRentBook() {
    char searchISBN[100];
    printf("�˻��� ������ ISBN�� �Է��ϼ���: ");
    scanf("%s", searchISBN);


    Book* temp = head.head;
    while (temp != NULL) {
        if (strcmp(temp->ISBN, searchISBN) == 0) {
            printf("������ ã�ҽ��ϴ�!\n");
            printf("���� ����: %s\n", temp->title);
            printf("����: %s\n", temp->author);
            printf("ISBN: %s\n", temp->ISBN);
            printf("����: %d\n", temp->price);

            if (temp->isRented == 0) { // �뿩 ������ ���
                printf("�뿩�Ͻðڽ��ϱ�? (1: ��, 0: �ƴϿ�) ");

                int rentChoice;
                scanf("%d", &rentChoice);
                if (rentChoice == 1) { // �뿩 ���� ��
                    temp->isRented = 1; // å�� �뿩 �� ���·� ����
                    printf("������ ���������� �뿩�Ǿ����ϴ�.\n");
                }
                else {
                    printf("���� �뿩�� ����մϴ�.\n");
                }
            }
            else { // �̹� �뿩 ���� ���
                printf("�˼��մϴ�. �ش� ������ �̹� �뿩 ���Դϴ�.\n");
            }
            return;
        }
        temp = temp->next;
    }

    printf("�ش� ISBN���� ������ ã�� �� �����ϴ�.\n");
}

// ���� �ݳ� �Լ�
void returnBook() {
    char returnISBN[100];
    printf("�ݳ��� ������ ISBN�� �Է��ϼ���: ");
    scanf("%s", returnISBN);

    Book* temp = head.head;
    while (temp != NULL) {
        if (strcmp(temp->ISBN, returnISBN) == 0) {
            if (temp->isRented == 1) { // �뿩 ���� ���
                temp->isRented = 0; // �뿩 �� ���¸� �ݳ� ó���� ����
                printf("������ ���������� �ݳ��Ǿ����ϴ�.\n");
            }
            else { // �̹� �ݳ��� ���
                printf("�̹� �ݳ��� �����̰ų�, �뿩�� ������ �ƴմϴ�.\n");
            }
            return;
        }
        temp = temp->next;
    }

    printf("�ش� ISBN���� ������ ã�� �� �����ϴ�.\n");
}

// ���� ���� �Լ�
void deleteBook() {
    char delISBN[100];
    printf("������ ������ ISBN�� �Է��ϼ���: ");
    scanf("%s", delISBN); // ������ ISBN �Է� ����

    Book* current = head.head;
    Book* prev = NULL;

    // ���� å�� ISBN�� �Է��� ISBN�� ��ġ�ϴ� ��� �ش� å�� ����
    while (current != NULL) {
        if (strcmp(current->ISBN, delISBN) == 0) {
            if (prev == NULL) {
                head.head = current->next; // ��带 �����Ͽ� ù ��° å�� ����
            }
            else {
                prev->next = current->next; // ���� å�� ���� �����͸� �����Ͽ� å ����
            }
            free(current); // ���� å�� �޸� ����
            printf("������ �����Ǿ����ϴ�.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("�ش� ISBN���� ������ ã�� �� �����ϴ�.\n"); // å�� ã�� ���� ��� �޽��� ���
}

// ���� ��� �Լ�
void printBooks() {
    if (head.head == NULL) {
        printf("��ϵ� ������ �����ϴ�.\n");
        return;
    }

    Book* temp = head.head;
    printf("<< ��ϵ� ���� ����Ʈ >> \n\n");
    while (temp != NULL) {
        printf("���� ����: %s\n", temp->title);
        printf("����: %s\n", temp->author);
        printf("ISBN: %s\n", temp->ISBN);
        printf("����: %d\n\n", temp->price);
        temp = temp->next;
    }
}

// ���� ��� �޸� ���� �Լ�
void freeBooks() {
    Book* current = head.head;
    Book* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head.head = NULL; // ��带 NULL�� �����Ͽ� ����Ʈ �ʱ�ȭ
}

// ���� �Լ�
int main() {
    int pick;

    // ��� �ʱ�ȭ
    head.head = NULL;

    // �޴� ��� �� ����
    while (1) {
        printf("***** ��ǰ ���� ���α׷��� �۵��մϴ� *****\n");
        printf("1. ���� ���\n");
        printf("2. ���� �˻� �� �뿩\n");
        printf("3. ���� ����\n");
        printf("4. ���� ���\n");
        printf("5. ���� �ݳ�\n");
        printf("0. ����\n\n");

        printf("�޴��� �����ϼ���(*���ڸ� �Է�):");
        scanf("%d", &pick);
        printf("\n");

        // ���õ� �޴��� ���� �ش� �Լ� ȣ��
        if (pick == 1)
            addBook();
        else if (pick == 2)
            searchAndRentBook();
        else if (pick == 3)
            deleteBook();
        else if (pick == 4)
            printBooks();
        else if (pick == 5)
            returnBook();
        else if (pick == 0) {
            printf("***** ��ǰ ���� ���α׷��� �����մϴ� *****\n");
            freeBooks(); // �޸� ���� �Լ� ȣ��
            return 0;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �������ּ���!\n");
        }
    }

    return 0;
}

