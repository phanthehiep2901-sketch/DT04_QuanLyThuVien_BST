
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

// ==================== 1. THONG TIN SACH ====================
struct Book {
    int id;
    string title;
    string author;
    int year;
};

// ==================== 2. NUT CUA CAY BST ====================
struct Node {
    Book data;
    Node* left;
    Node* right;

    Node(Book book) {
        data = book;
        left = nullptr;
        right = nullptr;
    }
};

// ==================== 3. NHAP SO NGUYEN AN TOAN ====================
int readInt(string message) {
    string input;
    int value;

    while (true) {
        cout << message;
        getline(cin, input);

        stringstream ss(input);
        char extra;

        if (ss >> value && !(ss >> extra)) {
            return value;
        }

        cout << "Du lieu khong hop le! Vui long nhap so nguyen.\n";
    }
}

// ==================== 4. THEM SACH ====================
Node* insert(Node* root, Book book) {
    if (root == nullptr) {
        return new Node(book);
    }

    if (book.id < root->data.id) {
        root->left = insert(root->left, book);
    }
    else if (book.id > root->data.id) {
        root->right = insert(root->right, book);
    }

    return root;
}

// ==================== 5. TIM KIEM SACH ====================
Node* search(Node* root, int id) {
    if (root == nullptr || root->data.id == id) {
        return root;
    }

    if (id < root->data.id) {
        return search(root->left, id);
    }

    return search(root->right, id);
}

// ==================== 6. TIM NUT NHO NHAT ====================
Node* findMin(Node* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }

    return root;
}

// ==================== 7. XOA SACH ====================
Node* deleteBook(Node* root, int id) {
    if (root == nullptr) {
        return nullptr;
    }

    if (id < root->data.id) {
        root->left = deleteBook(root->left, id);
    }
    else if (id > root->data.id) {
        root->right = deleteBook(root->right, id);
    }
    else {
        // Truong hop 1: Nut la
        // Truong hop 2: Nut co mot con
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        // Truong hop 3: Nut co hai con
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteBook(root->right, temp->data.id);
    }

    return root;
}

// ==================== 8. HIEN THI THONG TIN SACH ====================
void printBook(Book book) {
    cout << "Ma sach: " << book.id
         << " | Ten: " << book.title
         << " | Tac gia: " << book.author
         << " | Nam: " << book.year << '\n';
}

// ==================== 9. DUYET INORDER ====================
// Trai - Goc - Phai: Ma sach tang dan
void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    printBook(root->data);
    inorder(root->right);
}

// ==================== 10. DUYET PREORDER ====================
// Goc - Trai - Phai
void preorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << root->data.id << " ";
    preorder(root->left);
    preorder(root->right);
}

// ==================== 11. DUYET POSTORDER ====================
// Trai - Phai - Goc
void postorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data.id << " ";
}

// ==================== 12. LUU DU LIEU VAO FILE ====================
void saveBooksRecursive(Node* root, ofstream& file) {
    if (root == nullptr) {
        return;
    }

    saveBooksRecursive(root->left, file);

    file << root->data.id << "|"
         << root->data.title << "|"
         << root->data.author << "|"
         << root->data.year << '\n';

    saveBooksRecursive(root->right, file);
}

bool saveBooks(Node* root) {
    ofstream file("data/books.txt");

    if (!file.is_open()) {
        cout << "Loi: Khong mo duoc file data/books.txt!\n";
        cout << "Hay kiem tra thu muc data va duong dan chay.\n";
        return false;
    }

    saveBooksRecursive(root, file);
    file.close();

    if (file.fail()) {
        cout << "Loi khi ghi du lieu vao file!\n";
        return false;
    }

    cout << "Da luu du lieu sach vao file.\n";
    return true;
}

// ==================== 13. DOC DU LIEU TU FILE ====================
bool parseInt(const string& text, int& value) {
    stringstream ss(text);
    char extra;

    if (!(ss >> value)) {
        return false;
    }

    return !(ss >> extra);
}

void loadBooks(Node*& root) {
    ifstream file("data/books.txt");

    if (!file.is_open()) {
        cout << "Chua mo duoc file du lieu.\n";
        cout << "Chuong trinh bat dau voi thu vien rong.\n";
        cout << "Du lieu se duoc luu khi them hoac xoa sach.\n";
        return;
    }

    string line;
    int loaded = 0;
    int skipped = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string idText, title, author, yearText;

        if (!getline(ss, idText, '|') ||
            !getline(ss, title, '|') ||
            !getline(ss, author, '|') ||
            !getline(ss, yearText) ||
            title.empty() || author.empty()) {
            skipped++;
            continue;
        }

        Book book;

        if (!parseInt(idText, book.id) ||
            !parseInt(yearText, book.year)) {
            skipped++;
            continue;
        }

        // Khong nap sach co ma trung
        if (search(root, book.id) != nullptr) {
            skipped++;
            continue;
        }

        book.title = title;
        book.author = author;
        root = insert(root, book);
        loaded++;
    }

    file.close();

    cout << "Da nap " << loaded << " sach tu file.\n";

    if (skipped > 0) {
        cout << "Da bo qua " << skipped
             << " dong du lieu khong hop le hoac trung ma.\n";
    }
}

// ==================== 14. NHAP THONG TIN SACH ====================
Book inputBook() {
    Book book;

    book.id = readInt("Nhap ma sach: ");

    do {
        cout << "Nhap ten sach (khong dung ky tu |): ";
        getline(cin, book.title);

        if (book.title.empty() ||
            book.title.find('|') != string::npos) {
            cout << "Ten sach khong duoc rong hoac chua ky tu |.\n";
        }
    } while (book.title.empty() ||
             book.title.find('|') != string::npos);

    do {
        cout << "Nhap tac gia (khong dung ky tu |): ";
        getline(cin, book.author);

        if (book.author.empty() ||
            book.author.find('|') != string::npos) {
            cout << "Tac gia khong duoc rong hoac chua ky tu |.\n";
        }
    } while (book.author.empty() ||
             book.author.find('|') != string::npos);

    do {
        book.year = readInt("Nhap nam xuat ban: ");

        if (book.year <= 0) {
            cout << "Nam xuat ban phai lon hon 0.\n";
        }
    } while (book.year <= 0);

    return book;
}

// ==================== 15. GIAI PHONG BO NHO ====================
void destroyTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

// ==================== 16. MENU CHUONG TRINH ====================
int main() {
    Node* root = nullptr;

    // Tu dong doc du lieu khi khoi dong
    loadBooks(root);

    int choice;

    do {
        cout << "\n========== QUAN LY THU VIEN BST ==========\n";
        cout << "1. Them sach\n";
        cout << "2. Tim kiem sach\n";
        cout << "3. Xoa sach\n";
        cout << "4. Hien thi sach theo ma tang dan\n";
        cout << "5. Duyet Preorder\n";
        cout << "6. Duyet Postorder\n";
        cout << "7. Luu du lieu vao file\n";
        cout << "0. Thoat chuong trinh\n";

        choice = readInt("Nhap lua chon: ");

        switch (choice) {
            case 1: {
                Book book = inputBook();

                if (search(root, book.id) != nullptr) {
                    cout << "Ma sach da ton tai! Khong the them.\n";
                }
                else {
                    root = insert(root, book);
                    cout << "Them sach thanh cong!\n";
                    saveBooks(root);
                }

                break;
            }

            case 2: {
                int id = readInt("Nhap ma sach can tim: ");
                Node* result = search(root, id);

                if (result != nullptr) {
                    cout << "\nTim thay sach!\n";
                    printBook(result->data);
                }
                else {
                    cout << "Khong tim thay sach!\n";
                }

                break;
            }

            case 3: {
                int id = readInt("Nhap ma sach can xoa: ");

                if (search(root, id) == nullptr) {
                    cout << "Khong tim thay ma sach can xoa!\n";
                }
                else {
                    root = deleteBook(root, id);
                    cout << "Xoa sach thanh cong!\n";
                    saveBooks(root);
                }

                break;
            }

            case 4: {
                if (root == nullptr) {
                    cout << "Thu vien chua co sach!\n";
                }
                else {
                    cout << "\nDanh sach sach theo ma tang dan:\n";
                    inorder(root);
                }

                break;
            }

            case 5: {
                if (root == nullptr) {
                    cout << "Thu vien chua co sach!\n";
                }
                else {
                    cout << "Preorder: ";
                    preorder(root);
                    cout << '\n';
                }

                break;
            }

            case 6: {
                if (root == nullptr) {
                    cout << "Thu vien chua co sach!\n";
                }
                else {
                    cout << "Postorder: ";
                    postorder(root);
                    cout << '\n';
                }

                break;
            }

            case 7:
                saveBooks(root);
                break;

            case 0:
                cout << "Da thoat chuong trinh.\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    destroyTree(root);
    return 0;
}
