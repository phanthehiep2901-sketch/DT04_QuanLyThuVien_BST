
#include "../lib/httplib_test.h"
#include "../lib/nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <mutex>
#include <cstdlib>

using namespace std;
using json = nlohmann::json;

// ==================== CAU TRUC BST ====================

struct Book {
    int id;
    string title;
    string author;
    int year;
};

struct Node {
    Book data;
    Node* left;
    Node* right;

    Node(Book book) : data(book), left(nullptr), right(nullptr) {}
};

Node* root = nullptr;
mutex treeMutex;

// ==================== CAC HAM BST ====================

Node* search(Node* node, int id) {
    if (node == nullptr || node->data.id == id) {
        return node;
    }

    if (id < node->data.id) {
        return search(node->left, id);
    }

    return search(node->right, id);
}

Node* insert(Node* node, Book book) {
    if (node == nullptr) {
        return new Node(book);
    }

    if (book.id < node->data.id) {
        node->left = insert(node->left, book);
    } else if (book.id > node->data.id) {
        node->right = insert(node->right, book);
    }

    return node;
}

Node* findMin(Node* node) {
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* deleteBook(Node* node, int id) {
    if (node == nullptr) return nullptr;

    if (id < node->data.id) {
        node->left = deleteBook(node->left, id);
    } else if (id > node->data.id) {
        node->right = deleteBook(node->right, id);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteBook(node->right, temp->data.id);
    }

    return node;
}

void collectBooks(Node* node, vector<Book>& books) {
    if (node == nullptr) return;

    collectBooks(node->left, books);
    books.push_back(node->data);
    collectBooks(node->right, books);
}

void destroyTree(Node* node) {
    if (node == nullptr) return;

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// ==================== DOC VA LUU FILE ====================

bool parseInt(const string& text, int& value) {
    stringstream ss(text);
    char extra;

    if (!(ss >> value)) return false;
    return !(ss >> extra);
}

bool saveBooks(Node* node) {
    ofstream file("data/books.txt");

    if (!file.is_open()) return false;

    vector<Book> books;
    collectBooks(node, books);

    for (const Book& book : books) {
        file << book.id << "|"
             << book.title << "|"
             << book.author << "|"
             << book.year << '\n';
    }

    file.close();
    return !file.fail();
}

void loadBooks() {
    ifstream file("data/books.txt");
    if (!file.is_open()) {
        cout << "Chua co file du lieu; bat dau voi thu vien rong.\n";
        return;
    }

    string line;
    int loaded = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string idText, title, author, yearText;
        Book book;

        if (!getline(ss, idText, '|') ||
            !getline(ss, title, '|') ||
            !getline(ss, author, '|') ||
            !getline(ss, yearText)) {
            continue;
        }

        if (!parseInt(idText, book.id) ||
            !parseInt(yearText, book.year) ||
            book.id <= 0 || book.year <= 0 ||
            title.empty() || author.empty() ||
            title.find('|') != string::npos ||
            author.find('|') != string::npos) {
            continue;
        }

        if (search(root, book.id) != nullptr) continue;

        book.title = title;
        book.author = author;
        root = insert(root, book);
        loaded++;
    }

    cout << "Da nap " << loaded << " sach tu file.\n";
}

// ==================== JSON VA HTTP ====================

json bookToJson(const Book& book) {
    return {
        {"id", book.id},
        {"title", book.title},
        {"author", book.author},
        {"year", book.year}
    };
}

void setCors(httplib::Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods",
                   "GET, POST, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers",
                   "Content-Type");
}

void sendJson(httplib::Response& res, int status, const json& body) {
    setCors(res);
    res.status = status;
    res.set_content(body.dump(4), "application/json; charset=utf-8");
}

int main() {
    loadBooks();

    httplib::Server server;

    // Xu ly yeu cau kiem tra CORS tu trinh duyet
    server.Options(R"(/api/.*)",
        [](const httplib::Request&, httplib::Response& res) {
            setCors(res);
            res.status = 204;
        });

    // GET /api/books: lay tat ca sach
    server.Get("/api/books",
        [](const httplib::Request&, httplib::Response& res) {
            lock_guard<mutex> lock(treeMutex);

            vector<Book> books;
            collectBooks(root, books);

            json result = json::array();
            for (const Book& book : books) {
                result.push_back(bookToJson(book));
            }

            sendJson(res, 200, {
                {"success", true},
                {"books", result},
                {"total", books.size()}
            });
        });

    // GET /api/books/123: tim sach theo ma
    server.Get(R"(/api/books/([0-9]+))",
        [](const httplib::Request& req, httplib::Response& res) {
            int id;

            try {
                size_t used = 0;
                string textId = req.matches[1].str();
                id = stoi(textId, &used);

                if (used != textId.size() || id <= 0) {
                    sendJson(res, 400, {
                        {"success", false},
                        {"message", "Ma sach khong hop le."}
                    });
                    return;
                }
            } catch (...) {
                sendJson(res, 400, {
                    {"success", false},
                    {"message", "Ma sach khong hop le."}
                });
                return;
            }

            lock_guard<mutex> lock(treeMutex);
            Node* found = search(root, id);

            if (found == nullptr) {
                sendJson(res, 404, {
                    {"success", false},
                    {"message", "Khong tim thay sach."}
                });
                return;
            }

            sendJson(res, 200, {
                {"success", true},
                {"book", bookToJson(found->data)}
            });
        });

    // POST /api/books: them sach
    server.Post("/api/books",
        [](const httplib::Request& req, httplib::Response& res) {
            json body;

            try {
                body = json::parse(req.body);
            } catch (...) {
                sendJson(res, 400, {
                    {"success", false},
                    {"message", "JSON khong hop le."}
                });
                return;
            }

            if (!body.is_object() ||
                !body.contains("id") ||
                !body.contains("title") ||
                !body.contains("author") ||
                !body.contains("year") ||
                !body["id"].is_number_integer() ||
                !body["year"].is_number_integer() ||
                !body["title"].is_string() ||
                !body["author"].is_string()) {
                sendJson(res, 400, {
                    {"success", false},
                    {"message", "Thieu hoac sai kieu du lieu."}
                });
                return;
            }

            Book book;
            try {
                book.id = body["id"].get<int>();
                book.year = body["year"].get<int>();
                book.title = body["title"].get<string>();
                book.author = body["author"].get<string>();
            } catch (...) {
                sendJson(res, 400, {
                    {"success", false},
                    {"message", "Du lieu sach khong hop le."}
                });
                return;
            }

            if (book.id <= 0 || book.year <= 0 ||
                book.title.empty() || book.author.empty() ||
                book.title.find('|') != string::npos ||
                book.author.find('|') != string::npos) {
                sendJson(res, 400, {
                    {"success", false},
                    {"message", "Ma, nam, ten sach hoac tac gia khong hop le."}
                });
                return;
            }

            lock_guard<mutex> lock(treeMutex);

            if (search(root, book.id) != nullptr) {
                sendJson(res, 409, {
                    {"success", false},
                    {"message", "Ma sach da ton tai."}
                });
                return;
            }

            root = insert(root, book);

            if (!saveBooks(root)) {
                // Hoan tac neu khong luu duoc file
                root = deleteBook(root, book.id);

                sendJson(res, 500, {
                    {"success", false},
                    {"message", "Khong luu duoc data/books.txt."}
                });
                return;
            }

            sendJson(res, 201, {
                {"success", true},
                {"message", "Them sach thanh cong."},
                {"book", bookToJson(book)}
            });
        });

    // DELETE /api/books/123: xoa sach
    server.Delete(R"(/api/books/([0-9]+))",
        [](const httplib::Request& req, httplib::Response& res) {
            int id;

            try {
                size_t used = 0;
                string textId = req.matches[1].str();
                id = stoi(textId, &used);

                if (used != textId.size() || id <= 0) {
                    sendJson(res, 400, {
                        {"success", false},
                        {"message", "Ma sach khong hop le."}
                    });
                    return;
                }
            } catch (...) {
                sendJson(res, 400, {
                    {"success", false},
                    {"message", "Ma sach khong hop le."}
                });
                return;
            }

            lock_guard<mutex> lock(treeMutex);

            Node* found = search(root, id);
            if (found == nullptr) {
                sendJson(res, 404, {
                    {"success", false},
                    {"message", "Khong tim thay sach."}
                });
                return;
            }

            Book oldBook = found->data;
            root = deleteBook(root, id);

            if (!saveBooks(root)) {
                // Khoi phuc sach neu khong luu duoc file
                root = insert(root, oldBook);

                sendJson(res, 500, {
                    {"success", false},
                    {"message", "Khong luu duoc data/books.txt."}
                });
                return;
            }

            sendJson(res, 200, {
                {"success", true},
                {"message", "Xoa sach thanh cong."}
            });
        });

    // API kiem tra server
    server.Get("/api/hello",
        [](const httplib::Request&, httplib::Response& res) {
            sendJson(res, 200, {
                {"success", true},
                {"message", "C++ HTTP Server dang hoat dong!"}
            });
        });

    cout << "Da nap du lieu BST.\n";
    cout << "Server: http://127.0.0.1:8080\n";
    cout << "API sach: http://127.0.0.1:8080/api/books\n";

    if (!server.listen("127.0.0.1", 8080)) {
        cerr << "Khong khoi dong duoc server tren cong 8080.\n";
        destroyTree(root);
        return 1;
    }

    destroyTree(root);
    return 0;
}
