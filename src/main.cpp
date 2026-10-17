#include <iostream>
#include <string>
using namespace std;

struct Sach {
    string maSach;
    string tenSach;
    Sach* trai;
    Sach* phai;

    Sach(string ma, string ten)
        : maSach(ma), tenSach(ten),
          trai(nullptr), phai(nullptr) {}
};

int main() {
    cout << "QUAN LY THU VIEN - BST\n";
    cout << "Du an DT04_QuanLyThuVien_BST\n";

    Sach* sach = new Sach("S001", "Lap trinh C++");

    cout << "Ma sach: " << sach->maSach << '\n';
    cout << "Ten sach: " << sach->tenSach << '\n';

    delete sach;
    return 0;
}

