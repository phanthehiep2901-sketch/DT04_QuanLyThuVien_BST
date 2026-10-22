#include <iostream>
#include <string>
using namespace std;


#include <iostream>
#include <string>
using namespace std;

struct Book {
    string ISBN;
    string title;
    string author;
    int year;
};

int main() {
    Book b;

    b.ISBN = "978001";
    b.title = "Lap trinh C++";
    b.author = "Nguyen Van A";
    b.year = 2025;

    cout << "ISBN: " << b.ISBN << endl;
    cout << "Ten sach: " << b.title << endl;
    cout << "Tac gia: " << b.author << endl;
    cout << "Nam xuat ban: " << b.year << endl;

    return 0;
}


