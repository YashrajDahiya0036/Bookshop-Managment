#include "Book.h"
#include "Sales.h"
#include <cstring>
#include <limits>
#include <iomanip>

// Constructor to load books from file
Book::Book()
{
    loadBooks();
}

// Load books from the book.dat file
void Book::loadBooks()
{
    ifstream inFile("book.dat", ios::binary);
    if (!inFile)
    {
        cout << "No previous data found for books. Starting fresh.\n";
        return;
    }

    BookInfo book;
    while (inFile.read(reinterpret_cast<char *>(&book), sizeof(book)))
    {
        books.push_back(book);
        bookIDCounter++;
    }
    inFile.close();
}

// Save books to the book.dat file
void Book::saveBooks()
{
    ofstream outFile("book.dat", ios::binary);
    if (!outFile)
    {
        cout << "Error saving data to file.\n";
        return;
    }

    for (const auto &book : books)
    {
        outFile.write(reinterpret_cast<const char *>(&book), sizeof(book));
    }
    outFile.close();
}

// Add a new book
void Book::add_book()
{
    string title = getValidInput<string>("Enter Book Title: ");
    string author = getValidInput<string>("Enter Book Author: ");
    double price = getValidInput<double>("Enter Book Price: ");
    int quantity = getValidInput<int>("Enter Book Quantity: ");

    BookInfo newBook;
    newBook.id = bookIDCounter++;
    strncpy(newBook.title, title.c_str(), sizeof(newBook.title) - 1);
    newBook.title[sizeof(newBook.title) - 1] = '\0';
    strncpy(newBook.author, author.c_str(), sizeof(newBook.author) - 1);
    newBook.author[sizeof(newBook.author) - 1] = '\0';
    newBook.price = price;
    newBook.quantity = quantity;

    // Input the book's publish date
    newBook.publish_date.input_date();

    // Update dynamic discount based on book age
    update_dynamic_discount(newBook);

    books.push_back(newBook);
    cout << "Book added successfully! ID: " << newBook.id << endl;

    saveBooks(); // Save to file after adding
}

// Remove a book by ID
void Book::remove_book()
{
    int id = getValidInput<int>("Enter Book ID to remove: ");

    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it->id == id)
        {
            books.erase(it);
            cout << "Book removed successfully!\n";
            saveBooks(); // Save to file after removal
            return;
        }
    }
    cout << "Book with ID " << id << " not found.\n";
}

// Update the price of a book by ID
void Book::update_price()
{
    int id = getValidInput<int>("Enter Book ID to update price: ");

    for (auto &book : books)
    {
        if (book.id == id)
        {
            double newPrice = getValidInput<double>("Enter new price: ");
            book.price = newPrice;
            cout << "Price updated successfully for Book ID: " << id << endl;
            saveBooks(); // Save to file after updating
            return;
        }
    }
    cout << "Book with ID " << id << " not found.\n";
}

// Search for a book by ID
void Book::search_book()
{
    int id = getValidInput<int>("Enter Book ID to search: ");

    for (const auto &book : books)
    {
        if (book.id == id)
        {
            cout << "Book Found:\n";
            cout << "ID: " << book.id << "\nTitle: " << book.title
                 << "\nAuthor: " << book.author << "\nPrice: " << book.price
                 << "\nQuantity: " << book.quantity << endl;
            return;
        }
    }
    cout << "Book with ID " << id << " not found.\n";
}

// Apply dynamic discount based on book age
void Book::update_dynamic_discount(BookInfo& book) {
    int age = book.publish_date.calculate_age();
    double discount = 0.0;

    if (age >= 2) {
        discount = 5.0 * (age - 1); // Increase discount by 5% per year after 2 years
    }
    if (discount > 60.0) {
        discount = 60.0; // Max discount of 60%
    }

    book.discount = discount;
    cout << "Discount for Book ID " << book.id << " is now " << discount << "%\n";
}

// Apply discount to a book
void Book::apply_discount() {
    int id = getValidInput<int>("Enter Book ID to apply discount: ");
    double discountPercentage = getValidInput<double>("Enter discount percentage (0-100): ");

    for (auto& book : books) {
        if (book.id == id) {
            if (discountPercentage < 0 || discountPercentage > 100) {
                cout << "Invalid discount percentage. Please enter a value between 0 and 100.\n";
                return;
            }
            book.discount = discountPercentage;
            cout << "Discount of " << discountPercentage << "% applied to Book ID: " << id << endl;
            saveBooks();
            return;
        }
    }
    cout << "Book with ID " << id << " not found.\n";
}

// Remove discount from a book
void Book::remove_discount() {
    int id = getValidInput<int>("Enter Book ID to remove discount: ");

    for (auto& book : books) {
        if (book.id == id) {
            book.discount = 0.0;
            cout << "Discount removed for Book ID: " << id << endl;
            saveBooks();
            return;
        }
    }
    cout << "Book with ID " << id << " not found.\n";
}

// Display all books
void Book::display_books() {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "=== Book List ===\n";
    for (const auto& book : books) {
        double finalPrice = book.price * (1 - book.discount / 100.0);
        cout << "ID: " << book.id << ", Title: " << book.title
             << ", Author: " << book.author << ", Price: " << book.price
             << ", Discount: " << book.discount << "%, Final Price: " << finalPrice
             << ", Quantity: " << book.quantity << ", Age: " << book.publish_date.calculate_age() << " years\n";
    }
}

// Sell books and generate invoices
void Book::sell_books(Sales& salesManager) {
    cout << "=== Book List ===\n";
    display_books();  // Display all available books

    int bookID = getValidInput<int>("Enter the Book ID to buy: ");
    int quantityToBuy = getValidInput<int>("Enter the quantity to buy: ");

    for (auto& book : books) {
        if (book.id == bookID) {
            if (book.quantity < quantityToBuy) {
                cout << "Insufficient stock!\n";
                return;
            }

            double finalPrice = book.price * (1 - book.discount / 100.0);
            double totalAmount = finalPrice * quantityToBuy;

            // Create invoice and save it
            salesManager.add_invoice(book.id, quantityToBuy, finalPrice);

            // Update book quantity
            book.quantity -= quantityToBuy;
            saveBooks();  // Update books in file

            // Create the sale entry
            salesManager.add_sale(book.id, quantityToBuy, totalAmount, finalPrice);

            cout << "Purchase successful! Invoice created.\n";
            return;
        }
    }

    cout << "Book with ID " << bookID << " not found.\n";
}

// // Function to handle book sales
// void Book::sold_books(Sales& salesManager) {
//     int bookID = getValidInput<int>("Enter Book ID to sell: ");
//     int quantity = getValidInput<int>("Enter Quantity to sell: ");

//     for (auto& book : books) {
//         if (book.id == bookID) {
//             if (quantity > book.quantity) {
//                 cout << "Insufficient stock! Available quantity: " << book.quantity << endl;
//                 return;
//             }

//             // Update the book's quantity
//             book.quantity -= quantity;

//             // Calculate total amount
//             double totalAmount = quantity * book.price;

//             // Generate invoice and add the sale to Sales class
//             cout << "Sale completed! Generating invoice...\n";
//             salesManager.add_sale(bookID, quantity, totalAmount);

//             // Save the updated books
//             saveBooks();

//             cout << "Book sold successfully! Updated stock: " << book.quantity << endl;
//             return;
//         }
//     }

//     cout << "Book with ID " << bookID << " not found.\n";
// }  
