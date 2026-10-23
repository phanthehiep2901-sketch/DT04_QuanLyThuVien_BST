
document.addEventListener("DOMContentLoaded", function () {
    // ==============================
    // 1. KHAI BAO API VA CAC PHAN TU
    // ==============================
    const API_URL = "http://127.0.0.1:8080/api/books";

    let books = [];
    let isLoading = false;

    const bookForm = document.getElementById("bookForm");
    const bookId = document.getElementById("bookId");
    const bookTitle = document.getElementById("bookTitle");
    const bookAuthor = document.getElementById("bookAuthor");
    const bookYear = document.getElementById("bookYear");

    const bookTable = document.getElementById("bookTable");
    const totalBooks = document.getElementById("totalBooks");
    const searchInput = document.getElementById("searchInput");
    const searchButton = document.getElementById("searchButton");
    const showAllButton = document.getElementById("showAllButton");
    const message = document.getElementById("message");

    // Kiem tra HTML co day du cac phan tu can thiet khong
    if (
        !bookForm || !bookId || !bookTitle || !bookAuthor ||
        !bookYear || !bookTable || !totalBooks ||
        !searchInput || !searchButton || !showAllButton || !message
    ) {
        console.error("Thieu phan tu HTML. Hay kiem tra index.html.");
        return;
    }

    // ==============================
    // 2. THONG BAO
    // ==============================
    function showMessage(text, type = "info") {
        message.textContent = text;

        // Ho tro ca kieu goi cu: showMessage(text, true/false)
        if (typeof type === "boolean") {
            type = type ? "error" : "success";
        }

        const colors = {
            success: "#16845b",
            error: "#dc2626",
            info: "#2563eb"
        };

        message.style.color = colors[type] || colors.info;
        message.className = "message " + type;
        message.setAttribute(
            "role",
            type === "error" ? "alert" : "status"
        );
        message.setAttribute("aria-live", "polite");
    }

    // ==============================
    // 3. CAC HAM HO TRO
    // ==============================
    function createCell(text) {
        const cell = document.createElement("td");
        cell.textContent = String(text ?? "");
        return cell;
    }

    function setFormBusy(busy) {
        const submitButton = bookForm.querySelector(
            'button[type="submit"], input[type="submit"]'
        );

        if (submitButton) {
            submitButton.disabled = busy;
        }
    }

    function getErrorMessage(data, fallback) {
        return data && typeof data.message === "string"
            ? data.message
            : fallback;
    }

    async function readResponse(response) {
        try {
            return await response.json();
        } catch {
            throw new Error("Server tra ve du lieu khong hop le.");
        }
    }

    // ==============================
    // 4. TAI DANH SACH SACH TU C++
    // ==============================
    async function loadBooks(showStatus = true) {
        if (isLoading) return false;

        isLoading = true;

        if (showStatus) {
            showMessage("Dang tai danh sach sach...", "info");
        }

        try {
            const response = await fetch(API_URL);
            const data = await readResponse(response);

            if (!response.ok || !data.success) {
                throw new Error(
                    getErrorMessage(data, "Khong tai duoc danh sach sach.")
                );
            }

            if (!Array.isArray(data.books)) {
                throw new Error("Danh sach sach tu server khong hop le.");
            }

            books = data.books;
            renderBooks(getVisibleBooks());

            if (showStatus) {
                showMessage(
                    "Da tai " + books.length + " sach tu C++ BST.",
                    "success"
                );
            }

            return true;
        } catch (error) {
            console.error("Loi tai danh sach sach:", error);

            showMessage(
                "Khong ket noi duoc C++ Server. Hay kiem tra server.exe.",
                "error"
            );

            return false;
        } finally {
            isLoading = false;
        }
    }

    // ==============================
    // 5. HIEN THI DANH SACH SACH
    // ==============================
    function renderBooks(list) {
        bookTable.replaceChildren();
        totalBooks.textContent = String(books.length);

        if (list.length === 0) {
            const row = document.createElement("tr");
            const cell = document.createElement("td");

            cell.colSpan = 5;
            cell.className = "empty";

            cell.textContent = searchInput.value.trim()
                ? "Khong tim thay sach phu hop."
                : "Chua co sach nao trong thu vien.";

            row.appendChild(cell);
            bookTable.appendChild(row);
            return;
        }

        [...list]
            .sort((a, b) => Number(a.id) - Number(b.id))
            .forEach(function (book) {
                const row = document.createElement("tr");

                row.appendChild(createCell(book.id));
                row.appendChild(createCell(book.title));
                row.appendChild(createCell(book.author));
                row.appendChild(createCell(book.year));

                const actionCell = document.createElement("td");
                const deleteButton = document.createElement("button");

                deleteButton.type = "button";
                deleteButton.textContent = "Xoa";
                deleteButton.className = "btn btn-primary";
                deleteButton.style.backgroundColor = "#dc2626";
                deleteButton.setAttribute(
                    "aria-label",
                    "Xoa sach ma " + book.id
                );

                deleteButton.addEventListener("click", function () {
                    deleteBook(book.id, deleteButton);
                });

                actionCell.appendChild(deleteButton);
                row.appendChild(actionCell);
                bookTable.appendChild(row);
            });
    }

    // ==============================
    // 6. TIM KIEM SACH
    // ==============================
    function getVisibleBooks() {
        const keyword = searchInput.value.trim().toLowerCase();

        if (keyword === "") {
            return books;
        }

        return books.filter(function (book) {
            return String(book.id).includes(keyword) ||
                String(book.title).toLowerCase().includes(keyword) ||
                String(book.author).toLowerCase().includes(keyword);
        });
    }

    function searchBooks() {
        const results = getVisibleBooks();
        renderBooks(results);

        const keyword = searchInput.value.trim();

        if (keyword === "") {
            showMessage("Dang hien thi tat ca sach.", "info");
        } else if (results.length > 0) {
            showMessage(
                "Tim thay " + results.length + " sach phu hop.",
                "success"
            );
        } else {
            showMessage("Khong tim thay sach phu hop.", "error");
        }
    }

    searchButton.addEventListener("click", searchBooks);

    searchInput.addEventListener("keydown", function (event) {
        if (event.key === "Enter") {
            event.preventDefault();
            searchBooks();
        }
    });

    showAllButton.addEventListener("click", function () {
        searchInput.value = "";
        renderBooks(books);
        showMessage("Dang hien thi tat ca sach.", "info");
    });

    // ==============================
    // 7. THEM SACH
    // ==============================
    bookForm.addEventListener("submit", async function (event) {
        event.preventDefault();

        const idText = bookId.value.trim();
        const title = bookTitle.value.trim();
        const author = bookAuthor.value.trim();
        const yearText = bookYear.value.trim();

        // Chi chap nhan chuoi so nguyen, khong chap nhan 1.5 hoac 1e3
        if (!/^\d+$/.test(idText)) {
            showMessage("Ma sach phai la so nguyen duong!", "error");
            bookId.focus();
            return;
        }

        const id = Number(idText);

        if (!Number.isSafeInteger(id) || id <= 0) {
            showMessage("Ma sach phai lon hon 0!", "error");
            bookId.focus();
            return;
        }

        if (!title || !author) {
            showMessage("Ten sach va tac gia khong duoc de trong!", "error");
            return;
        }

        if (title.includes("|") || author.includes("|")) {
            showMessage(
                "Ten sach va tac gia khong duoc chua ky tu |!",
                "error"
            );
            return;
        }

        if (!/^\d+$/.test(yearText)) {
            showMessage("Nam xuat ban phai la so nguyen!", "error");
            bookYear.focus();
            return;
        }

        const year = Number(yearText);
        const currentYear = new Date().getFullYear();

        if (
            !Number.isSafeInteger(year) ||
            year <= 0 ||
            year > currentYear
        ) {
            showMessage("Nam xuat ban khong hop le!", "error");
            bookYear.focus();
            return;
        }

        // Kiem tra trung ma ngay tren giao dien
        if (books.some(book => Number(book.id) === id)) {
            showMessage("Ma sach da ton tai!", "error");
            bookId.focus();
            return;
        }

        setFormBusy(true);
        showMessage("Dang them sach...", "info");

        try {
            const response = await fetch(API_URL, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify({ id, title, author, year })
            });

            const data = await readResponse(response);

            if (!response.ok || !data.success) {
                showMessage(
                    getErrorMessage(data, "Them sach that bai."),
                    "error"
                );
                return;
            }

            bookForm.reset();
            searchInput.value = "";

            const refreshed = await loadBooks(false);

            if (refreshed) {
                showMessage(
                    "Them sach thanh cong va da luu vao file!",
                    "success"
                );
            }
        } catch (error) {
            console.error("Loi them sach:", error);
            showMessage("Khong ket noi duoc C++ Server.", "error");
        } finally {
            setFormBusy(false);
        }
    });

    // ==============================
    // 8. XOA SACH
    // ==============================
    async function deleteBook(id, button) {
        if (!confirm("Ban co chac muon xoa sach ma " + id + "?")) {
            return;
        }

        if (button) {
            button.disabled = true;
            button.textContent = "Dang xoa...";
        }

        try {
            const response = await fetch(API_URL + "/" + id, {
                method: "DELETE"
            });

            const data = await readResponse(response);

            if (!response.ok || !data.success) {
                showMessage(
                    getErrorMessage(data, "Xoa sach that bai."),
                    "error"
                );
                return;
            }

            const refreshed = await loadBooks(false);

            if (refreshed) {
                showMessage(
                    "Da xoa sach ma " + id + " va cap nhat file.",
                    "success"
                );
            }
        } catch (error) {
            console.error("Loi xoa sach:", error);
            showMessage("Khong ket noi duoc C++ Server.", "error");
        } finally {
            if (button) {
                button.disabled = false;
                button.textContent = "Xoa";
            }
        }
    }

    // ==============================
    // 9. KHOI DONG
    // ==============================
    loadBooks();
});
