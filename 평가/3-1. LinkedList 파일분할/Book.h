/*
File : LinkedList.c

Created : 2024-03-27
Auther : 오혜진
*/

#ifndef BOOK_H
#define BOOK_H

// 책 구조체 정의
typedef struct Book {
    char ISBN[100];
    char author[100];
    char title[100];
    int price;
    int isRented;       
    struct Book* next;
} Book;

// 책 구조체 헤드 정의
typedef struct {
    Book* head;
} Head;

Head head;

void addBook();
void searchAndRentBook();
void returnBook();
void deleteBook();
void printBooks();
void freeBooks();

#endif