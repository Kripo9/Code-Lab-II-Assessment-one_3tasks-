
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Class to store information about a book
class Book {
public:
    string title;
    string author;
    int pages;
    string id;
    bool borrowed;
};

// Load books from the text file
bool loadBooks(vector<Book>& books) {
    ifstream file("books.txt");

    if (!file.is_open()) {
        cout << "Error: Cannot open books.txt!" << endl;
        return false;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string title, author, pagesText, id, status;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, pagesText, ',');
        getline(ss, id, ',');
        getline(ss, status, ',');

        try {
            Book book;
            book.title = title;
            book.author = author;
            book.pages = stoi(pagesText);
            book.id = id;
            book.borrowed = (status == "true");

            books.push_back(book);
        }
        catch (...) {
            cout << "Skipping invalid book data." << endl;
        }
    }

    file.close();
    return true;
}

// Save all books to the text file
void saveBooks(const vector<Book>& books) {
    ofstream file("books.txt");

    if (!file.is_open()) {
        cout << "Error: Cannot save books!" << endl;
        return;
    }

    for (const Book& book : books) {
        file << book.title << ","
             << book.author << ","
             << book.pages << ","
             << book.id << ","
             << (book.borrowed ? "true" : "false")
             << endl;
    }

    file.close();
}

// Display information about one book
void displayBook(const Book& book) {
    cout << "\nBook ID: " << book.id << endl;
    cout << "Title: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "Pages: " << book.pages << endl;
    cout << "Status: "
         << (book.borrowed ? "Borrowed" : "Available")
         << endl;
}

// Display all books
void viewBooks(const vector<Book>& books) {
    cout << "\n===== Library Books =====\n";

    for (const Book& book : books) {
        displayBook(book);
        cout << "------------------------\n";
    }
}

// Find a book by its ID
Book* findBook(vector<Book>& books, const string& id) {
    for (Book& book : books) {
        if (book.id == id) {
            return &book;
        }
    }

    return nullptr;
}

// View details of a specific book
void viewDetails(vector<Book>& books) {
    string id;

    cout << "\nEnter Book ID: ";
    cin >> id;

    Book* book = findBook(books, id);

    if (book != nullptr) {
        displayBook(*book);
    } else {
        cout << "Book not found!" << endl;
    }
}

// Borrow a book
void borrowBook(vector<Book>& books) {
    string id;

    cout << "\nEnter Book ID to borrow: ";
    cin >> id;

    Book* book = findBook(books, id);

    if (book == nullptr) {
        cout << "Book not found!" << endl;
    } else if (book->borrowed) {
        cout << "This book is already borrowed!" << endl;
    } else {
        book->borrowed = true;
        saveBooks(books);
        cout << "Book successfully borrowed!" << endl;
    }
}

// Return a book
void returnBook(vector<Book>& books) {
    string id;

    cout << "\nEnter Book ID to return: ";
    cin >> id;

    Book* book = findBook(books, id);

    if (book == nullptr) {
        cout << "Book not found!" << endl;
    } else if (!book->borrowed) {
        cout << "This book is already available!" << endl;
    } else {
        book->borrowed = false;
        saveBooks(books);
        cout << "Book successfully returned!" << endl;
    }
}

int main() {
    vector<Book> books;

    if (!loadBooks(books)) {
        return 1;
    }

    cout << "Welcome to Book Manager!" << endl;

    int choice;

    do {
        cout << "\n===== BOOK MANAGER =====" << endl;
        cout << "1. View All Books" << endl;
        cout << "2. View Book Details" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                viewBooks(books);
                break;

            case 2:
                viewDetails(books);
                break;

            case 3:
                borrowBook(books);
                break;

            case 4:
                returnBook(books);
                break;

            case 5:
                saveBooks(books);
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid option! Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}

