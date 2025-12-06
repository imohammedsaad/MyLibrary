#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>


void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


class Book
{
private:
    int id;
    std::string title;
    std::string author;
    int year;
    bool available;
    int borrowedByUserId; 

public:
    Book() : id(0), year(0), available(true), borrowedByUserId(-1) {}

    Book(int id, const std::string &title, const std::string &author, int year)
        : id(id), title(title), author(author), year(year), available(true), borrowedByUserId(-1) {}

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }
    bool isAvailable() const { return available; }
    int getBorrowedByUserId() const { return borrowedByUserId; }

    void borrow(int userId)
    {
        available = false;
        borrowedByUserId = userId;
    }

    void giveBack()
    {
        available = true;
        borrowedByUserId = -1;
    }

    void print() const
    {
        std::cout << "[Book ID: " << id << "] "
                  << title << " by " << author
                  << " (" << year << ")";
        if (available)
        {
            std::cout << " | Status: Available";
        }
        else
        {
            std::cout << " | Status: Borrowed (User ID: " << borrowedByUserId << ")";
        }
        std::cout << '\n';
    }
};

// ---- User Class ----------------------

class User
{
private:
    int id;
    std::string name;
    std::vector<int> borrowedBooks;

public:
    User() : id(0) {}
    User(int id, const std::string &name) : id(id), name(name) {}

    int getId() const { return id; }
    std::string getName() const { return name; }

    const std::vector<int> &getBorrowedBooks() const { return borrowedBooks; }

    void borrowBook(int bookId)
    {
        borrowedBooks.push_back(bookId);
    }

    void returnBook(int bookId)
    {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        if (it != borrowedBooks.end())
        {
            borrowedBooks.erase(it);
        }
    }

    void print() const
    {
        std::cout << "[User ID: " << id << "] " << name;
        if (borrowedBooks.empty())
        {
            std::cout << " | No borrowed books";
        }
        else
        {
            std::cout << " | Borrowed books: ";
            for (size_t i = 0; i < borrowedBooks.size(); ++i)
            {
                std::cout << borrowedBooks[i];
                if (i + 1 < borrowedBooks.size())
                    std::cout << ", ";
            }
        }
        std::cout << '\n';
    }
};

//  Library System Class ----------------------

class LibrarySystem
{
private:
    std::unordered_map<int, Book> books;
    std::unordered_map<int, User> users;
    int nextBookId;
    int nextUserId;

public:
    LibrarySystem() : nextBookId(1), nextUserId(1) {}

    //  Book Management ---------

    void addBook()
    {
        std::string title, author;
        int year;

        std::cout << "\nEnter book title: ";
        std::getline(std::cin >> std::ws, title);
        std::cout << "Enter author name: ";
        std::getline(std::cin >> std::ws, author);
        std::cout << "Enter publication year: ";

        while (!(std::cin >> year))
        {
            std::cout << "Invalid input. Enter a valid year: ";
            clearInput();
        }
        clearInput();

        Book b(nextBookId, title, author, year);
        books[nextBookId] = b;

        std::cout << "Book added with ID: " << nextBookId << "\n";
        nextBookId++;
    }

    void listAllBooks() const
    {
        if (books.empty())
        {
            std::cout << "\nNo books in the library yet.\n";
            return;
        }
        std::cout << "\n--- All Books ---\n";
        for (const auto &pair : books)
        {
            pair.second.print();
        }
    }

    void searchBooks() const
    {
        if (books.empty())
        {
            std::cout << "\nNo books in the library yet.\n";
            return;
        }

        std::cout << "\nSearch by: 1) Title  2) Author: ";
        int choice;
        std::cin >> choice;
        clearInput();

        std::string query;
        std::cout << "Enter search text: ";
        std::getline(std::cin >> std::ws, query);

        // convert query to lowercase for case-insensitive search
        std::string qLower = query;
        std::transform(qLower.begin(), qLower.end(), qLower.begin(), ::tolower);

        bool found = false;
        std::cout << "\n--- Search Results ---\n";
        for (const auto &pair : books)
        {
            std::string field;
            if (choice == 1)
            {
                field = pair.second.getTitle();
            }
            else
            {
                field = pair.second.getAuthor();
            }

            std::string fLower = field;
            std::transform(fLower.begin(), fLower.end(), fLower.begin(), ::tolower);

            if (fLower.find(qLower) != std::string::npos)
            {
                pair.second.print();
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "No matching books found.\n";
        }
    }

    void removeBook()
    {
        if (books.empty())
        {
            std::cout << "\nNo books to remove.\n";
            return;
        }

        int id;
        std::cout << "Enter Book ID to remove: ";
        std::cin >> id;
        clearInput();

        auto it = books.find(id);
        if (it == books.end())
        {
            std::cout << "Book not found.\n";
            return;
        }

        if (!it->second.isAvailable())
        {
            std::cout << "Cannot remove a borrowed book.\n";
            return;
        }

        books.erase(it);
        std::cout << "Book removed successfully.\n";
    }

    // --------- User Management ---------

    void addUser()
    {
        std::string name;
        std::cout << "\nEnter user name: ";
        std::getline(std::cin >> std::ws, name);

        User u(nextUserId, name);
        users[nextUserId] = u;

        std::cout << "User added with ID: " << nextUserId << "\n";
        nextUserId++;
    }

    void listAllUsers() const
    {
        if (users.empty())
        {
            std::cout << "\nNo users registered yet.\n";
            return;
        }
        std::cout << "\n--- All Users ---\n";
        for (const auto &pair : users)
        {
            pair.second.print();
        }
    }

    // --------- Borrow / Return ---------

    void borrowBook()
    {
        if (books.empty() || users.empty())
        {
            std::cout << "\nNeed at least one book and one user in the system.\n";
            return;
        }

        int userId, bookId;
        std::cout << "Enter User ID: ";
        std::cin >> userId;
        std::cout << "Enter Book ID: ";
        std::cin >> bookId;
        clearInput();

        auto userIt = users.find(userId);
        if (userIt == users.end())
        {
            std::cout << "User not found.\n";
            return;
        }

        auto bookIt = books.find(bookId);
        if (bookIt == books.end())
        {
            std::cout << "Book not found.\n";
            return;
        }

        Book &book = bookIt->second;
        User &user = userIt->second;

        if (!book.isAvailable())
        {
            std::cout << "Book is already borrowed by another user.\n";
            return;
        }

        book.borrow(userId);
        user.borrowBook(bookId);
        std::cout << "Book borrowed successfully.\n";
    }

    void returnBook()
    {
        if (books.empty() || users.empty())
        {
            std::cout << "\nNeed at least one book and one user in the system.\n";
            return;
        }

        int userId, bookId;
        std::cout << "Enter User ID: ";
        std::cin >> userId;
        std::cout << "Enter Book ID: ";
        std::cin >> bookId;
        clearInput();

        auto userIt = users.find(userId);
        if (userIt == users.end())
        {
            std::cout << "User not found.\n";
            return;
        }

        auto bookIt = books.find(bookId);
        if (bookIt == books.end())
        {
            std::cout << "Book not found.\n";
            return;
        }

        Book &book = bookIt->second;
        User &user = userIt->second;

        if (book.isAvailable())
        {
            std::cout << "This book is not currently marked as borrowed.\n";
            return;
        }

        if (book.getBorrowedByUserId() != userId)
        {
            std::cout << "This book is not borrowed by this user.\n";
            return;
        }

        book.giveBack();
        user.returnBook(bookId);
        std::cout << "Book returned successfully.\n";
    }

    void viewUserBorrowedBooks() const
    {
        if (users.empty())
        {
            std::cout << "\nNo users registered yet.\n";
            return;
        }

        int userId;
        std::cout << "Enter User ID: ";
        std::cin >> userId;
        clearInput();

        auto userIt = users.find(userId);
        if (userIt == users.end())
        {
            std::cout << "User not found.\n";
            return;
        }

        const User &user = userIt->second;
        const auto &borrowed = user.getBorrowedBooks();

        std::cout << "\nBooks borrowed by " << user.getName()
                  << " (User ID: " << user.getId() << "):\n";
        if (borrowed.empty())
        {
            std::cout << "No books borrowed.\n";
            return;
        }

        for (int bookId : borrowed)
        {
            auto bookIt = books.find(bookId);
            if (bookIt != books.end())
            {
                bookIt->second.print();
            }
        }
    }

    // --------- Main Menu ---------

    void showMenu()
    {
        int choice = -1;
        while (choice != 0)
        {
            std::cout << "\n============================\n";
            std::cout << "  Library Management System\n";
            std::cout << "============================\n";
            std::cout << "1. Add Book\n";
            std::cout << "2. List All Books\n";
            std::cout << "3. Search Books\n";
            std::cout << "4. Remove Book\n";
            std::cout << "5. Add User\n";
            std::cout << "6. List All Users\n";
            std::cout << "7. Borrow Book\n";
            std::cout << "8. Return Book\n";
            std::cout << "9. View User Borrowed Books\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter choice: ";

            if (!(std::cin >> choice))
            {
                std::cout << "Invalid input. Please enter a number.\n";
                clearInput();
                choice = -1;
                continue;
            }
            clearInput();

            switch (choice)
            {
            case 1:
                addBook();
                break;
            case 2:
                listAllBooks();
                break;
            case 3:
                searchBooks();
                break;
            case 4:
                removeBook();
                break;
            case 5:
                addUser();
                break;
            case 6:
                listAllUsers();
                break;
            case 7:
                borrowBook();
                break;
            case 8:
                returnBook();
                break;
            case 9:
                viewUserBorrowedBooks();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }
};

// ---------------------- main ----------------------

int main()
{
    LibrarySystem system;
    system.showMenu();
    return 0;
}
