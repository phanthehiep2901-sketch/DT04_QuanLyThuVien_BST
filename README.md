# DT04 - QUẢN LÝ THƯ VIỆN BẰNG CÂY TÌM KIẾM NHỊ PHÂN (BST)

## 1. Giới thiệu dự án

Dự án DT04 xây dựng chương trình quản lý thư viện sử dụng ngôn ngữ C++ và cấu trúc dữ liệu cây tìm kiếm nhị phân (Binary Search Tree - BST), kết hợp giao diện Web bằng HTML, CSS và JavaScript.

Dự án được thực hiện nhằm vận dụng kiến thức về cấu trúc dữ liệu, thuật toán, lập trình C++ và kỹ năng làm việc nhóm thông qua Git và GitHub.

### Mục tiêu

- Quản lý thông tin sách trong thư viện.
- Thêm sách mới vào hệ thống.
- Tìm kiếm sách theo mã sách hoặc khóa tìm kiếm đã thống nhất.
- Xóa sách khỏi hệ thống.
- Duyệt cây BST để hiển thị dữ liệu theo thứ tự.
- Xây dựng giao diện Web trực quan, dễ sử dụng.
- Rèn luyện kỹ năng quản lý mã nguồn và phát triển phần mềm theo nhóm.

## 2. Công nghệ sử dụng

- **Ngôn ngữ lập trình:** C++17 trở lên.
- **Cấu trúc dữ liệu:** Binary Search Tree (BST).
- **Trình biên dịch:** g++.
- **Công cụ xây dựng:** CMake nếu dự án sử dụng.
- **IDE:** Visual Studio hoặc Visual Studio Code.
- **Giao diện Web:** HTML5, CSS3, JavaScript.
- **Quản lý mã nguồn:** Git và GitHub.

## 3. Cấu trúc thư mục dự án

Cấu trúc thư mục đề xuất:

```text
DT04_QuanLyThuVien_BST/
├── README.md
├── .gitignore
├── CMakeLists.txt
├── include/
│   └── (các file header .h hoặc .hpp)
├── src/
│   └── main.cpp
└── web/
    ├── index.html
    ├── style.css
    └── script.js
```

### Chức năng các thư mục và file

- `README.md`: Tài liệu giới thiệu và hướng dẫn sử dụng dự án.
- `.gitignore`: Khai báo các file và thư mục không cần đưa lên Git.
- `CMakeLists.txt`: Cấu hình biên dịch bằng CMake nếu được sử dụng.
- `include/`: Chứa các file khai báo lớp, cấu trúc dữ liệu và hàm.
- `src/`: Chứa mã nguồn C++ của chương trình.
- `web/`: Chứa giao diện Web.
- `index.html`: Xây dựng cấu trúc trang Web.
- `style.css`: Định dạng giao diện.
- `script.js`: Xử lý các tương tác trên giao diện Web.

Lưu ý: Đây là cấu trúc đề xuất. Có thể điều chỉnh theo cách tổ chức mã nguồn thực tế của nhóm. Không cần tạo các thư mục hoặc file chưa sử dụng.

## 4. Cài đặt môi trường phát triển C++

### 4.1. Cài đặt Git

Tải Git tại:

https://git-scm.com/downloads

Sau khi cài đặt, mở Terminal hoặc Git Bash và kiểm tra:

```bash
git --version
```

Nếu hiển thị phiên bản Git, quá trình cài đặt đã thành công.

### 4.2. Cài đặt trình biên dịch g++

Trên Windows, có thể sử dụng MSYS2 hoặc MinGW-w64 để cài đặt g++.

Trang tải MSYS2:

https://www.msys2.org/

Sau khi cài đặt, cần cấu hình môi trường để Terminal có thể nhận diện lệnh `g++`.

Kiểm tra bằng lệnh:

```bash
g++ --version
```

Nếu hiển thị thông tin phiên bản, trình biên dịch đã sẵn sàng sử dụng.

### 4.3. Biên dịch chương trình bằng g++

Mở Terminal tại thư mục gốc của dự án.

Nếu chương trình chỉ có file `src/main.cpp`, sử dụng:

```bash
g++ -std=c++17 -Wall -Wextra src/main.cpp -o library.exe
```

Nếu có nhiều file `.cpp` nằm trực tiếp trong thư mục `src/`, có thể sử dụng:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o library.exe
```

Chạy chương trình trên Windows:

```bash
./library.exe
```

Trên Linux hoặc macOS, có thể biên dịch thành file `library` và chạy bằng:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o library
./library
```

Lưu ý: Lệnh biên dịch phải phù hợp với cấu trúc mã nguồn thực tế. Nếu có các thư mục con hoặc nhiều file nguồn phụ thuộc lẫn nhau, cần điều chỉnh danh sách file hoặc sử dụng CMake.

### 4.4. Biên dịch bằng CMake

Nếu dự án có file `CMakeLists.txt`, cần cài đặt CMake và một trình biên dịch C++ tương thích.

Trang tải CMake:

https://cmake.org/download/

Kiểm tra cài đặt:

```bash
cmake --version
```

Từ thư mục gốc dự án, chạy:

```bash
cmake -S . -B build
cmake --build build
```

Tên và vị trí file thực thi sau khi biên dịch phụ thuộc vào cấu hình CMake, hệ điều hành và cấu hình Build.

### 4.5. Sử dụng Visual Studio

1. Tải Visual Studio tại https://visualstudio.microsoft.com/.
2. Cài workload **Desktop development with C++**.
3. Mở dự án C++ hoặc thư mục có `CMakeLists.txt`.
4. Chọn cấu hình Debug hoặc Release.
5. Build dự án.
6. Chạy chương trình bằng công cụ chạy và gỡ lỗi của Visual Studio.

Nếu sử dụng Visual Studio Code, cần cài thêm trình biên dịch C++ và các tiện ích phù hợp. VS Code là trình soạn thảo mã nguồn, không tự cung cấp trình biên dịch g++.

## 5. Hướng dẫn mở giao diện Web

### 5.1. Mở trực tiếp bằng trình duyệt

1. Mở thư mục `web/`.
2. Tìm file `index.html`.
3. Nhấp đúp vào file để mở bằng trình duyệt.
4. Kiểm tra giao diện và các chức năng phía trình duyệt.

### 5.2. Sử dụng Visual Studio Code và Live Server

1. Cài Visual Studio Code tại https://code.visualstudio.com/.
2. Mở thư mục dự án.
3. Cài tiện ích Live Server nếu cần.
4. Nhấp chuột phải vào `web/index.html`.
5. Chọn **Open with Live Server**.

Trình duyệt sẽ mở trang Web thông qua máy chủ cục bộ.

### Lưu ý về kết nối giữa Web và C++

Việc mở `index.html` chỉ chạy phần giao diện HTML, CSS và JavaScript. Giao diện không tự động kết nối với chương trình C++ đã biên dịch.

Nếu cần giao diện Web thao tác trực tiếp với dữ liệu BST trong C++, nhóm phải xây dựng cơ chế giao tiếp phù hợp, chẳng hạn một máy chủ API viết bằng C++ hoặc một phương án tích hợp khác.

Nhóm cần thống nhất kiến trúc này trước khi triển khai chức năng tích hợp.

## 6. Quy tắc quản lý nhánh Git

Dự án sử dụng bốn nhánh chính:

### 6.1. Nhánh `main`

- Chứa phiên bản ổn định của dự án.
- Chỉ cập nhật khi các chức năng đã được kiểm thử.
- Là phiên bản dùng để trình bày hoặc bàn giao.

### 6.2. Nhánh `dev`

- Chứa các chức năng đang được tích hợp.
- Dùng để kiểm thử sự tương thích giữa các phần của dự án.
- Là nhánh nhận Pull Request từ các nhánh phát triển.

### 6.3. Nhánh `feature/bst-core`

- Phát triển các chức năng BST bằng C++.
- Cài đặt các thao tác thêm, tìm kiếm, xóa và duyệt cây.
- Kiểm thử thuật toán và xử lý các trường hợp đặc biệt.

### 6.4. Nhánh `feature/web-ui`

- Phát triển giao diện Web.
- Xây dựng bố cục bằng HTML và CSS.
- Xử lý tương tác bằng JavaScript.
- Chuẩn bị giao diện để tích hợp với phần xử lý dữ liệu khi kiến trúc kết nối đã được thống nhất.

## 7. Quy trình làm việc với Git và GitHub

### 7.1. Sao chép dự án về máy

Thay `TEN_TAI_KHOAN` bằng tên tài khoản GitHub sở hữu repository.

```bash
git clone https://github.com/TEN_TAI_KHOAN/DT04_QuanLyThuVien_BST.git
cd DT04_QuanLyThuVien_BST
```

### 7.2. Cập nhật nhánh phát triển

```bash
git switch dev
git pull origin dev
```

### 7.3. Tạo nhánh cho một chức năng mới

Ví dụ, tạo nhánh phát triển chức năng tìm kiếm sách từ nhánh BST:

```bash
git switch feature/bst-core
git pull origin feature/bst-core
git switch -c feature/bst-search
```

### 7.4. Lưu thay đổi

Sau khi viết và kiểm thử mã nguồn:

```bash
git status
git add .
git commit -m "feat: them chuc nang tim kiem sach"
git push -u origin feature/bst-search
```

Nên kiểm tra `git status` trước khi dùng `git add .` để tránh đưa nhầm file vào commit.

### 7.5. Tạo Pull Request

1. Đẩy nhánh tính năng lên GitHub.
2. Mở repository trên trình duyệt.
3. Chọn tạo Pull Request.
4. Chọn nhánh nguồn và nhánh đích phù hợp.
5. Mô tả chức năng, các thay đổi và kết quả kiểm thử.
6. Nhờ thành viên hoặc trưởng nhóm review.
7. Hợp nhất khi mã nguồn đạt yêu cầu.

Quy trình đề xuất:

- `feature/bst-search` → `feature/bst-core`.
- `feature/bst-core` → `dev`.
- `feature/web-ui` → `dev`.
- `dev` → `main` sau khi tích hợp và kiểm thử.

Các nhánh tính năng nhỏ có thể được tạo khi cần. Không bắt buộc phải giữ tất cả các nhánh phụ sau khi chức năng đã được hợp nhất.

### 7.6. Quy tắc commit

Nên đặt tên commit ngắn gọn, thể hiện rõ nội dung thay đổi.

Ví dụ:

```text
feat: them chuc nang them sach
feat: them chuc nang tim kiem sach
fix: sua loi xoa nut la trong BST
style: cai thien giao dien trang chu
docs: cap nhat README
refactor: tach lop quan ly sach
```

Không commit thư mục build, file thực thi hoặc thông tin bí mật vào repository.

## 8. Thành viên và phân công công việc

- **Trưởng nhóm:** Huỳnh Văn Lĩnh.
  - Quản lý repository và quyền truy cập.
  - Phân chia công việc.
  - Review Pull Request.
  - Theo dõi tiến độ tích hợp và bàn giao.

- **Thành viên phát triển C++/BST:**
  - Xây dựng cấu trúc dữ liệu.
  - Cài đặt các thao tác quản lý sách.
  - Kiểm thử thuật toán.

- **Thành viên phát triển giao diện Web:**
  - Thiết kế HTML, CSS và JavaScript.
  - Xây dựng các thành phần giao diện.
  - Kiểm thử tương tác trên trình duyệt.

- **Thành viên kiểm thử và tài liệu:**
  - Kiểm thử chức năng.
  - Ghi nhận lỗi và kết quả kiểm thử.
  - Cập nhật tài liệu hướng dẫn.

Danh sách thành viên cụ thể sẽ được bổ sung theo phân công thực tế của nhóm.

## 9. Kiểm thử và tiêu chí hoàn thành

Một chức năng chỉ được xem là hoàn thành khi đã được kiểm tra và đáp ứng yêu cầu.

Các nội dung cần kiểm thử:

- Thêm sách với dữ liệu hợp lệ.
- Xử lý trường hợp mã sách bị trùng.
- Tìm kiếm sách có tồn tại và không tồn tại.
- Xóa nút lá, nút có một con và nút có hai con trong BST.
- Duyệt cây và kiểm tra thứ tự dữ liệu.
- Kiểm tra giao diện trên trình duyệt.
- Kiểm tra kết nối giữa giao diện Web và phần xử lý C++ nếu đã triển khai.
- Biên dịch thành công và không còn lỗi nghiêm trọng.
- README và cấu trúc dự án được cập nhật.

## 10. Trạng thái dự án

Dự án được phát triển theo từng giai đoạn:

1. Khởi tạo repository và thống nhất cấu trúc thư mục.
2. Xây dựng các chức năng BST bằng C++.
3. Phát triển giao diện Web.
4. Tích hợp các thành phần.
5. Kiểm thử, sửa lỗi và hoàn thiện tài liệu.
6. Đưa phiên bản ổn định lên nhánh `main`.

Trạng thái hoàn thành của từng chức năng sẽ được cập nhật trong quá trình thực hiện.

---

**Repository:** `DT04_QuanLyThuVien_BST`  
**Trưởng nhóm:** Huỳnh Văn Lĩnh  
**Mục tiêu:** Xây dựng chương trình quản lý thư viện bằng C++ với cấu trúc dữ liệu BST và giao diện Web.
