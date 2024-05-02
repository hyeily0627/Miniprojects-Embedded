
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

// 도서 등록 함수
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
    printf("도서가 등록되었습니다!\n");
    printf("\n");
}

// 도서 검색 함수
// ++ ISBN, 제목, 저자까지 검색되도록 구현 
void searchBook() {
    char searchentry[100];
    printf("-- 도서를 검색합니다 -- \n");
    printf("검색할 항목을 선택하세요!\n");
    printf("1 ISBN \n");
    printf("2 도서제목 \n");
    printf("3 저자 \n");

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
            printf("도서 제목: %s\n", temp->title);
            printf("저자: %s\n", temp->author);
            printf("ISBN: %s\n", temp->ISBN);
            printf("가격: %d\n\n", temp->price);
        }
        temp = temp->next;
    }
    if (!found) { // 검색 결과를 찾지 못했을 경우에만 해당 문구 출력
        printf("해당 검색어로 도서를 찾을 수 없습니다.\n\n");
    }
}
/*
&&와 ||는 논리 연산자로, 조건식을 평가하고 결과를 결정하는 데 사용됩니다.
이 두 연산자의 차이는 다음과 같습니다:

&& (논리 AND 연산자):

두 개의 조건이 모두 참일 때 전체 표현식이 참이 됩니다.
즉, 조건 A와 조건 B가 모두 참이어야 전체 표현식이 참이 됩니다.
하나라도 거짓인 경우, 전체 표현식은 거짓이 됩니다.
예시: A && B

|| (논리 OR 연산자):

두 개의 조건 중 하나 이상이 참일 때 전체 표현식이 참이 됩니다.
즉, 조건 A 또는 조건 B 중 하나 이상이 참이면 전체 표현식이 참이 됩니다.
두 조건이 모두 거짓인 경우에만 전체 표현식이 거짓이 됩니다.
예시: A || B

따라서 searchChoice == 1 && strcmp(temp->title, searchString) == 0에서는 searchChoice가 1이고,
동시에 temp->title이 searchString과 동일한 경우에 조건이 참이 됩니다.
반면에 || 연산자를 사용하면 조건 중 하나만 참이어도 전체 표현식이 참이 되므로,
논리적으로 다른 동작을 합니다.
*/

// 도서 삭제 함수 
void deleteBook() {
    char delISBN[100];
    printf("삭제할 도서의 ISBN을 입력하세요: ");
    scanf("%s", delISBN);

    Book* current = head.head;
    Book* prev = NULL;

    // 현재 책의 ISBN이 입력한 ISBN과 일치하는 경우 해당 책을 삭제
    while (current != NULL) {
        if (strcmp(current->ISBN, delISBN) == 0) {
            if (prev == NULL) {
                head.head = current->next;		// 헤드를 변경하여 첫 번째 책을 삭제
            }
            else {
                prev->next = current->next;		// 이전 책의 다음 포인터를 변경하여 책 삭제
            }
            free(current); 					// 현재 책의 메모리 해제
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
    printf("등록된 도서 목록:\n");
    while (temp != NULL) {
        printf("도서 제목: %s\n", temp->title);
        printf("저자: %s\n", temp->author);
        printf("ISBN: %s\n", temp->ISBN);
        printf("가격: %d\n", temp->price);
        temp = temp->next;
    }
}

// 메인함수
int main() {
    int pick;

    // 헤드 초기화
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
            printf("***** 상품 관리 프로그램을 종료합니다 *****\n");
            return 0;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택해주세요!\n");
        }
    }

    return 0;
}