/*
File : Product Manager.c

Created : 2024-03-06
Auther : 오혜진
*/

#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    int id;
    int price;
    string producer;

public:
    Product(int id = 0, int price = 0, string pro = "") : id(id), price(price), producer(pro) {}
    virtual ~Product() {} // 가상 소멸자 추가

    virtual void show() = 0;

    int getId() const { return id; }
    int getPrice() const { return price; }
    string getProducer() const { return producer; }
};

class Book : public Product {
private:
    string ISBN;
    string author;
    string title;

public:
    Book(int id, int price, string pro, string ISBN, string author, string title)
        : Product(id, price, pro), ISBN(ISBN), author(author), title(title) {}

    void show() override // override 키워드 추가
    {
        cout << "--- 책 정보 ---" << endl;
        cout << "상품 ID: " << getId() << endl;
        cout << "가격: " << getPrice() << endl;
        cout << "생산자: " << getProducer() << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "저자: " << author << endl;
        cout << "제목: " << title << endl;
    }
};

class Handphone : public Product {
private:
    string model;
    int RAM;

public:
    Handphone(int id, int price, string pro, string model, int RAM)
        : Product(id, price, pro), model(model), RAM(RAM) {}

    void show() override // override 키워드 추가
    {
        cout << "--- 핸드폰 정보 ---" << endl;
        cout << "상품 ID: " << getId() << endl;
        cout << "가격: " << getPrice() << endl;
        cout << "생산자: " << getProducer() << endl;
        cout << "모델: " << model << endl;
        cout << "RAM 용량: " << RAM << "GB" << endl;
    }
};

class Computer : public Product {
private:
    string model;
    string cpu;
    int RAM;

public:
    Computer(int id, int price, string pro, string model, string cpu, int RAM)
        : Product(id, price, pro), model(model), cpu(cpu), RAM(RAM) {}

    void show() override // override 키워드 추가
    {
        cout << "--- 컴퓨터 정보 ---" << endl;
        cout << "상품 ID: " << getId() << endl;
        cout << "가격: " << getPrice() << endl;
        cout << "생산자: " << getProducer() << endl;
        cout << "모델: " << model << endl;
        cout << "CPU: " << cpu << endl;
        cout << "RAM 용량: " << RAM << "GB" << endl;
    }
};

int main() {
    Product* productArray[100];
    int numProducts = 0;

    cout << "***** 상품 관리 프로그램을 작동합니다 *****" << endl;

    int num;
    do {
        cout << "1. 상품추가, 2. 상품 출력, 3. 상품조회, 0. 종료" << endl;
        cin >> num;

        if (num == 1) {
            cout << "추가할 상품 종류를 선택하세요 <1. 책, 2. 핸드폰, 3. 컴퓨터>" << endl;
            int type;
            cin >> type;

            int id, price;
            string producer;

            cout << "상품 ID: ";
            cin >> id;

            cout << "가격: ";
            cin >> price;

            cout << "제조사: ";
            cin >> producer;

            if (type == 1) {
                string ISBN, author, title;

                cout << "ISBN: ";
                cin >> ISBN;
                cout << "저자: ";
                cin >> author;
                cout << "제목: ";
                cin >> title;

                productArray[numProducts] = new Book(id, price, producer, ISBN, author, title);
            }
            else if (type == 2) {
                string model;
                int RAM;

                cout << "모델명: ";
                cin >> model;
                cout << "램크기(GB): ";
                cin >> RAM;

                productArray[numProducts] = new Handphone(id, price, producer, model, RAM);
            }
            else if (type == 3) {
                string model, cpu;
                int RAM;

                cout << "모델: ";
                cin >> model;
                cout << "CPU: ";
                cin >> cpu;
                cout << "RAM 용량(GB): ";
                cin >> RAM;

                productArray[numProducts] = new Computer(id, price, producer, model, cpu, RAM);
            }

            numProducts++;

            cout << "상품이 추가되었습니다." << endl;
        }
        else if (num == 2) {
            cout << "등록된 상품 목록:" << endl;
            for (int i = 0; i < numProducts; ++i) {
                productArray[i]->show();
                cout << endl;
            }
        }
        else if (num == 3) {
            int productId;
            cout << "조회할 상품 ID를 입력하세요: ";
            cin >> productId;
            bool found = false;
            for (int i = 0; i < numProducts; ++i) {
                if (productArray[i]->getId() == productId) {
                    productArray[i]->show();
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "해당 상품을 찾을 수 없습니다." << endl;
        }
        else if (num == 0) {
            cout << "프로그램을 종료합니다." << endl;
            // 동적 할당된 객체들의 메모리 해제
            for (int i = 0; i < numProducts; ++i) {
                delete productArray[i];
            }
        }
        else {
            cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
        }
    } while (num != 0);

    return 0;
}
