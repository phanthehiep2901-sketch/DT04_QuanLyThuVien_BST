# DT04 - QUẢN LÝ THƯ VIỆN BẰNG CÂY TÌM KIẾM NHỊ PHÂN (BST)

## 1. Giới thiệu

Dự án xây dựng chương trình quản lý sách thư viện bằng ngôn ngữ C++, sử dụng cây tìm kiếm nhị phân (Binary Search Tree - BST) để tổ chức và xử lý dữ liệu. Dự án có giao diện Web giúp người dùng thao tác với danh sách sách thông qua C++ HTTP Server.

## 2. Chức năng chính

- Thêm sách mới.
- Tìm kiếm sách theo mã, tên sách hoặc tác giả trên giao diện Web.
- Xóa sách theo mã.
- Duyệt cây BST trong chương trình C++.
- Lưu và tải dữ liệu sách từ file.
- Kết nối giao diện Web với C++ Server thông qua API.
- Kiểm tra dữ liệu đầu vào và hiển thị thông báo trạng thái.

## 3. Công nghệ sử dụng

- **C++17:** xây dựng thuật toán BST và HTTP Server.
- **g++ / MinGW-w64:** biên dịch chương trình C++ trên Windows.
- **cpp-httplib:** xây dựng HTTP Server.
- **nlohmann/json:** xử lý dữ liệu JSON.
- **HTML, CSS, JavaScript:** xây dựng giao diện Web.
- **Git và GitHub:** quản lý mã nguồn và phối hợp nhóm.

## 4. Cấu trúc thư mục

```text
DT04_QuanLyThuVien_BST/
├── src/
│   ├── main.cpp
│   └── server.cpp
├── web/
│   ├── index.html
│   ├── style.css
│   └── script.js
├── lib/
│   ├── httplib_test.h
│   └── nlohmann/
│       └── json.hpp
├── data/
│   └── books.txt
├── .gitignore
└── README.md
```

Cấu trúc trên mô tả các file chính của dự án; tên hoặc số lượng file có thể được cập nhật theo phiên bản thực tế.

## 5. Yêu cầu môi trường

- Windows.
- MinGW-w64 hoặc môi trường có trình biên dịch `g++` hỗ trợ C++17.
- Trình duyệt Web hiện đại.
- Các file thư viện header trong thư mục `lib/`.

## 6. Biên dịch chương trình C++ độc lập

Mở PowerShell tại thư mục gốc của dự án và chạy:

```powershell
& "C:\mingw64\bin\g++.exe" src/main.cpp -o main.exe -std=c++17
```

Chạy chương trình:

```powershell
.\main.exe
```

Chức năng của chương trình độc lập được thực hiện qua menu trong Terminal.

## 7. Chạy C++ HTTP Server và giao diện Web

### Bước 1: Biên dịch Server

```powershell
& "C:\mingw64\bin\g++.exe" src/server.cpp -o server.exe -std=c++17 -lws2_32 -lwsock32
```

### Bước 2: Khởi động Server

```powershell
.\server.exe
```

Server mặc định chạy tại:

- Địa chỉ: `http://127.0.0.1:8080`
- API danh sách sách: `http://127.0.0.1:8080/api/books`

Giữ Terminal đang chạy Server mở trong khi sử dụng giao diện Web.

### Bước 3: Mở giao diện Web

Mở file `web/index.html` bằng trình duyệt. Có thể sử dụng tiện ích Live Server trong VS Code nếu đã cài đặt.

Giao diện Web gọi API tại `http://127.0.0.1:8080/api/books`, vì vậy C++ Server cần được khởi động trước.

## 8. Lưu trữ dữ liệu

Dữ liệu sách được lưu trong file `data/books.txt` theo định dạng:

```text
id|title|author|year
```

Mỗi dòng tương ứng với một cuốn sách. C++ Server đọc dữ liệu khi khởi động và cập nhật file khi thêm hoặc xóa sách thành công.

Đảm bảo chạy chương trình từ thư mục gốc của dự án để đường dẫn dữ liệu tương đối hoạt động đúng.

## 9. Kiểm thử

Các chức năng đã được kiểm tra trong quá trình phát triển:

- Thêm sách và kiểm tra mã trùng.
- Tìm kiếm sách.
- Xóa sách.
- Kiểm tra API trả về JSON.
- Kiểm tra dữ liệu trong file.
- Tải lại trang Web.
- Khởi động lại Server và kiểm tra dữ liệu được đọc lại.

## 10. Quản lý mã nguồn

Các nhánh dự kiến sử dụng trong nhóm:

- `main`: phiên bản ổn định.
- `dev`: tích hợp và kiểm thử.
- `feature/bst-core`: phát triển thuật toán BST.
- `feature/web-ui`: phát triển giao diện Web.

Thành viên cần làm việc trên nhánh được phân công và kiểm tra thay đổi trước khi tích hợp vào nhánh chung.

## 11. Thành viên

Bổ sung họ tên, vai trò và phần việc thực tế của từng thành viên nhóm tại đây.

## 12. Hướng phát triển

- Cải thiện giao diện và trải nghiệm người dùng.
- Bổ sung kiểm thử tự động.
- Hoàn thiện xử lý lỗi và kiểm tra dữ liệu.
- Mở rộng chức năng quản lý thông tin sách theo yêu cầu của đề tài.
