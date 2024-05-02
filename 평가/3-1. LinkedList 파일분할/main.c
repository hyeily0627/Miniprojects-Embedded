/*
File : LinkedList.c

Created : 2024-03-27
Auther : 오혜진
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Book.h"

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