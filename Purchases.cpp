#include "Purchases.h"
#include "Supplier.h"
#include "Book.h"
#include <cstring>

// Constructor to load existing orders from file
Purchases::Purchases() {
    loadOrders();
}

// Load orders from the orders.dat file
void Purchases::loadOrders() {
    ifstream inFile("orders.dat", ios::binary);
    if (!inFile) {
        cout << "No previous data found for Orders. Starting fresh.\n";
        return;
    }

    OrderInfo order;
    while (inFile.read(reinterpret_cast<char*>(&order), sizeof(order))) {
        orders.push_back(order);
        orderIDCounter++;
    }
    inFile.close();
}

// Save orders to the orders.dat file
void Purchases::saveOrders() {
    ofstream outFile("orders.dat", ios::binary);
    if (!outFile) {
        cout << "Error saving data to file.\n";
        return;
    }

    for (const auto& order : orders) {
        outFile.write(reinterpret_cast<const char*>(&order), sizeof(order));
    }
    outFile.close();
}

// Check if a supplier exists in supplier.dat
bool Purchases::checkSupplierExists(const string& supplierName) {
    ifstream inFile("supplier.dat", ios::binary);
    if (!inFile) {
        cout << "Error opening supplier data.\n";
        return false;
    }

    Supplier::SupplierInfo supplier;
    while (inFile.read(reinterpret_cast<char*>(&supplier), sizeof(supplier))) {
        if (supplierName == supplier.name) {
            return true;  // Supplier found
        }
    }
    return false;  // Supplier not found
}

// Place a new order
void Purchases::new_order() {
    string bookTitle = getValidInput<string>("Enter Book Title: ");
    string supplierName = getValidInput<string>("Enter Supplier Name: ");
    int quantity = getValidInput<int>("Enter Quantity: ");
    double price = getValidInput<double>("Enter total cost of the order: ");

    // Check if supplier exists
    if (!checkSupplierExists(supplierName)) {
        cout << "Supplier not found in the system.\n";
        int choice = getValidInput<int>("Would you like to add this supplier? (1 for Yes, 0 for No): ");
        if (choice == 1) {
            Supplier supplierManager;
            supplierManager.add_supplier();
            cout << "Supplier added successfully.\n";
        } else {
            cout << "Order cancelled.\n";
            return;  // Cancel order if the supplier is not added
        }
    }

    OrderInfo newOrder;
    newOrder.orderID = orderIDCounter++;
    strncpy(newOrder.bookTitle, bookTitle.c_str(), sizeof(newOrder.bookTitle) - 1);
    newOrder.bookTitle[sizeof(newOrder.bookTitle) - 1] = '\0';
    strncpy(newOrder.supplierName, supplierName.c_str(), sizeof(newOrder.supplierName) - 1);
    newOrder.supplierName[sizeof(newOrder.supplierName) - 1] = '\0';
    newOrder.quantity = quantity;
    newOrder.total_cost = price;
    strncpy(newOrder.status, "Pending", sizeof(newOrder.status) - 1);
    newOrder.status[sizeof(newOrder.status) - 1] = '\0';

    orders.push_back(newOrder);
    cout << "Order placed successfully! Order ID: " << newOrder.orderID << endl;

    saveOrders();
}

// View all orders
void Purchases::view() {
    if (orders.empty()) {
        cout << "No orders available.\n";
        return;
    }

    cout << "=== Order List ===\n";
    for (const auto& order : orders) {
        cout << "Order ID: " << order.orderID
             << ", Book Title: " << order.bookTitle
             << ", Supplier: " << order.supplierName
             << ", Quantity: " << order.quantity
             << ",Total Cost: " << order.total_cost
             << ", Status: " << order.status << endl;
    }
}

// Mark an order as "Cancelled"
void Purchases::mark_cancel() {
    int orderID = getValidInput<int>("Enter Order ID to cancel: ");

    for (auto& order : orders) {
        if (order.orderID == orderID) {
            strncpy(order.status, "Cancelled", sizeof(order.status) - 1);
            order.status[sizeof(order.status) - 1] = '\0';
            cout << "Order ID " << orderID << " marked as Cancelled.\n";
            saveOrders();
            return;
        }
    }
    cout << "Order with ID " << orderID << " not found.\n";
}

// Mark an order as "Received"
void Purchases::mark_received() {
    int orderID = getValidInput<int>("Enter Order ID to mark as received: ");

    for (auto& order : orders) {
        if (order.orderID == orderID) {
            strncpy(order.status, "Received", sizeof(order.status) - 1);
            order.status[sizeof(order.status) - 1] = '\0';
            cout << "Order ID " << orderID << " marked as Received.\n";
            saveOrders();
            Book book_manager;
            book_manager.add_book();
            book_manager.saveBooks();
            return;
        }
    }
    cout << "Order with ID " << orderID << " not found.\n";
}
