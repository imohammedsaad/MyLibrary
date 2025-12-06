# 📚 Library Management System (C++ | OOP | Console-Based)

A modular and efficient **console-based Library Management System** built using **C++** and **Object-Oriented Programming** principles.  
Designed with clean class separation—`Book`, `User`, and `LibrarySystem`—and optimized using STL containers like `unordered_map` and `vector`.

---

## 🚀 Features

### 📘 Book Management
- Add books  
- List all books  
- Search books (title/author)  
- Remove books (only if available)

### 👤 User Management
- Register new users  
- List all users  
- Track user-borrowed books  

### 🔄 Borrow / Return System
- Borrow books with availability validation  
- Return books  
- View user borrowing history  

---

## 🛠️ Tech Stack

| Component        | Choice        |
|------------------|---------------|
| Language         | C++17         |
| Data Structures  | `unordered_map`, `vector` |
| Paradigm         | Object-Oriented Programming |
| I/O              | Console-based |

---

## 📂 Project Structure

📦 library-management-system
├── library_system.cpp # Main implementation
└── README.md # Documentation

yaml
Copy code

---

## 🧠 Class Architecture Overview

### **Book**
Manages:
- ID, title, author, year  
- Availability status  
- Borrower user ID  

### **User**
Manages:
- User profile  
- List of borrowed book IDs  

### **LibrarySystem**
Responsible for:
- Coordinating book/user operations  
- Borrow/return logic  
- Input handling and menu system  

---

## 🔧 Build & Run Instructions

### **Compile**
```bash
g++ -std=c++17 library_system.cpp -o library_system
Run
bash
Copy code
./library_system
Windows users:

bash
Copy code
library_system.exe
🖥️ Console Preview
markdown
Copy code
============================
  Library Management System
============================
1. Add Book
2. List All Books
3. Search Books
4. Remove Book
5. Add User
6. List All Users
7. Borrow Book
8. Return Book
9. View User Borrowed Books
0. Exit
