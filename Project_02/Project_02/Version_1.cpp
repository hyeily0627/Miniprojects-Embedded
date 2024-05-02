#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 책구조체 정의 
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

// 도서 등록
void addBook() {
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("메모리 할당 실패 !\n");
        return;
    }
    printf("도서의 ISBN을 입력하세요: ");
    scanf("%s", newBook->ISBN);
    printf("도서의 저자를 입력하세요: ");
    scanf("%s", newBook->author);
    printf("도서의 제목을 입력하세요(공백제외): ");
    scanf("%s", newBook->title);
    printf("도서의 가격을 입력하세요: ");
    scanf("%d", &newBook->price);

    newBook->next = NULL;

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
}

// 도서검색 
// (ISBM말고도 검색할 수 있도록 구현해보기)
void searchBook() {
    char searchISBN[100];
    printf("검색할 도서의 ISBN을 입력하세요: ");
    scanf("%s", searchISBN);

    Book* temp = head.head;
    while (temp != NULL) {
        if (strcmp(temp->ISBN, searchISBN) == 0) {
            printf("도서를 찾았습니다!\n");
            return;
        }
        temp = temp->next;
    }

    printf("해당 ISBN으로 도서를 찾을 수 없습니다.\n");
}

// 도서삭제함수 
void deleteBook() {
    char delISBN[100];
    printf("삭제할 도서의 ISBN을 입력하세요: ");
    scanf("%s", delISBN);

    Book* current = head.head;
    Book* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->ISBN, delISBN) == 0) {
            if (prev == NULL) {
                head.head = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("도서가 삭제되었습니다.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("해당 ISBN으로 도서를 찾을 수 없습니다.\n");
}

// 도서출력함수 
void printBooks() {
    if (head.head == NULL) {
        printf("등록된 도서가 없습니다.\n");
        return;
    }

    Book* temp = head.head;
    printf("등록된 도서 목록:\n");
    while (temp != NULL) {
        printf("도서 제목: %s\n", temp->title);
        printf("저자: %s\n", temp->author);
        printf("ISBN: %s\n", temp->ISBN);
        printf("가격: %d\n", temp->price);
        temp = temp->next;
    }
}

int main() {
    int pick;

    head.head = NULL;

    while (1) {
        printf("***** 상품 관리 프로그램을 작동합니다 *****\n");
        printf("1. 도서 등록\n");
        printf("2. 도서 검색\n");
        printf("3. 도서 삭제\n");
        printf("4. 도서 출력\n");
        printf("0. 종료\n");

        printf("메뉴를 선택하세요(*숫자만 입력) : ");
        scanf("%d", &pick);

        if (pick == 1)
            addBook();
        else if (pick == 2)
            searchBook();
        else if (pick == 3)
            deleteBook();
        else if (pick == 4)
            printBooks();
        else if (pick == 0) {
            printf("***** 상품 관리 프로그램을 종료합니다 *****\n");
            return 0;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택해주세요!\n");
        }
    }

    return 0;
}