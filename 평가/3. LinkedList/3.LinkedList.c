/*
File : LinkedList.c

Created : 2024-03-27
Auther : 오혜진
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 책 구조체 정의
typedef struct Book {
    char ISBN[100];
    char author[100];
    char title[100];
    int price;
    int isRented;       // 대여여부를 나타내는 변수
    struct Book* next;
} Book;

// 책 구조체 헤드 정의
typedef struct {
    Book* head;
} Head;

Head head;

// 도서 등록 함수
void addBook() {
    Book* newBook = (Book*)malloc(sizeof(Book)); // 새로운 책을 위한 메모리 할당
    if (newBook == NULL) {
        printf("메모리 할당 실패 !\n"); 
        return;
    }
    printf("--- 도서를 등록합니다 --- \n");

    printf("도서의 ISBN을 입력하세요: ");
    scanf("%s", newBook->ISBN); 

    // 이미 등록된 도서들의 ISBN과 비교하여 중복 여부 확인
    Book* temp = head.head;
    while (temp != NULL) {
        if (strcmp(temp->ISBN, newBook->ISBN) == 0) {
            printf("이미 등록된 도서입니다. 중복된 ISBN은 등록할 수 없습니다.\n");
            free(newBook); // 중복된 ISBN의 경우 메모리를 해제하고 함수 종료
            return;
        }
        temp = temp->next;
    }

    printf("도서의 저자를 입력하세요: ");
    scanf("%s", newBook->author); 
    printf("도서의 제목을 입력하세요(공백제외): ");
    scanf("%s", newBook->title); 
    printf("도서의 가격을 입력하세요: ");
    scanf("%d", &newBook->price); 

    newBook->isRented = 0; // 새 책은 미대여 상태로 초기화
    newBook->next = NULL;

    // 헤드가 비어있는 경우 새 책을 헤드로 설정, 그렇지 않으면 리스트 끝까지 이동하여 추가
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
    printf("\nLoading… \n\n");
    printf("도서가 등록되었습니다!\n");
    printf("\n");
}
// 도서 검색 함수
void searchAndRentBook() {
    char searchentry[100];
    printf("-- 도서를 검색합니다 -- \n");
    printf("검색할 항목을 선택하세요!\n");
    printf("1 ISBN / 2 도서제목 / 3 저자 : ");
    
    int searchchoice;
    scanf("%d", &searchchoice);

    // 검색 항목 선택 후 입력값 받기 
    char searchinput[100];
    printf("검색어를 입력하세요: ");
    scanf("%s", searchinput);
    printf("\n");

    Book* temp = head.head;
    int found = 0; // 검색 결과를 찾았는지 여부를 나타내는 변수

    while (temp != NULL) {
        if ((searchchoice == 1 && strcmp(temp->ISBN, searchinput) == 0) ||
            (searchchoice == 2 && strcmp(temp->title, searchinput) == 0) ||
            (searchchoice == 3 && strcmp(temp->author, searchinput) == 0))
        {
            found = 1; // 검색 결과를 찾았음을 표시
            printf("도서를 찾았습니다!\n\n");
            printf("ISBN: %s\n", temp->ISBN);
            printf("도서 제목: %s\n", temp->title);
            printf("저자: %s\n", temp->author);
            printf("가격: %d\n", temp->price);
            printf("대여 가능 여부: %s\n\n", (temp->isRented == 0) ? "가능" : "불가능");       
        }
        temp = temp->next;
    }
    if (!found) { 
        printf("해당 검색어로 도서를 찾을 수 없습니다.\n");
    }
    else {
        char rentISBN[100];
        printf("대여할 도서의 ISBN을 입력하세요: ");
        scanf("%s", rentISBN);

        temp = head.head;
        while (temp != NULL) {
            if (strcmp(temp->ISBN, rentISBN) == 0) {
                if (temp->isRented == 0) { // 대여 가능한 경우
                    temp->isRented = 1; // 책을 대여 중 상태로 변경
                    printf("\nLoading… \n\n");
                    printf("도서가 성공적으로 대여되었습니다.\n\n");
                }
                else { // 이미 대여 중인 경우
                    printf("죄송합니다. 해당 도서는 이미 대여 중입니다.\n\n");
                }
                return;
            }
            temp = temp->next;
        }

        printf("해당 ISBN으로 도서를 찾을 수 없습니다.\n\n"); // 책을 찾지 못한 경우 메시지 출력
    }
}

// 도서 반납 함수
void returnBook() {
    char returnISBN[100];
    printf("반납할 도서의 ISBN을 입력하세요: ");
    scanf("%s", returnISBN);
    printf("\n");

    Book* temp = head.head;
    while (temp != NULL) {
        if (strcmp(temp->ISBN, returnISBN) == 0) {
            if (temp->isRented == 1) { // 대여 중인 경우
                temp->isRented = 0; // 대여 중 상태를 반납 처리로 변경
                printf("도서가 성공적으로 반납되었습니다.\n\n");
            }
            else { // 이미 반납된 경우
                printf("이미 반납된 도서이거나, 대여한 도서가 아닙니다.\n\n");
            }
            return;
        }
        temp = temp->next;
    }

    printf("해당 ISBN으로 도서를 찾을 수 없습니다.\n\n");
}

// 도서 삭제 함수
void deleteBook() {
    char delISBN[100];
    printf("삭제할 도서의 ISBN을 입력하세요: ");
    scanf("%s", delISBN); // 삭제할 ISBN 입력 받음

    Book* current = head.head;
    Book* prev = NULL;

    // 현재 책의 ISBN이 입력한 ISBN과 일치하는 경우 해당 책을 삭제
    while (current != NULL) {
        if (strcmp(current->ISBN, delISBN) == 0) {
            if (prev == NULL) {
                head.head = current->next; // 헤드를 변경하여 첫 번째 책을 삭제
            }
            else {
                prev->next = current->next; // 이전 책의 다음 포인터를 변경하여 책 삭제
            }
            free(current); // 현재 책의 메모리 해제
            printf("도서가 삭제되었습니다.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("해당 ISBN으로 도서를 찾을 수 없습니다.\n"); 
}

// 도서 출력 함수
void printBooks() {
    if (head.head == NULL) {
        printf("등록된 도서가 없습니다.\n");
        return;
    }

    Book* temp = head.head;
    printf("<< 등록된 도서 리스트 >> \n\n");
    while (temp != NULL) {
        printf("ISBN: %s\n", temp->ISBN);
        printf("도서 제목: %s\n", temp->title);
        printf("저자: %s\n", temp->author);
        printf("가격: %d\n\n", temp->price);
        temp = temp->next;
    }
}

// 도서 목록 메모리 해제 함수
void freeBooks() {
    Book* current = head.head;
    Book* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head.head = NULL; // 헤드를 NULL로 설정하여 리스트 초기화
}

// 메인 함수
int main() {
    int pick;

    // 헤드 초기화
    head.head = NULL;

    // 메뉴 출력 및 선택
    while (1) {
        printf("***** 상품 관리 프로그램을 작동합니다 *****\n");
        printf("1. 도서 등록\n");
        printf("2. 도서 검색 및 대여\n");
        printf("3. 도서 삭제\n");
        printf("4. 도서 출력\n");
        printf("5. 도서 반납\n");
        printf("0. 종료\n\n");

        printf("메뉴를 선택하세요(*숫자만 입력): ");
        scanf("%d", &pick);
        printf("\n");
       
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
            printf("***** 상품 관리 프로그램을 종료합니다 *****\n");
            freeBooks(); // 메모리 해제 함수 호출
            return 0;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택해주세요!\n");
        }
    }

    return 0;
}


