#include "Supplier.h"
#include <cstring>

// Constructor to load suppliers from file
Supplier::Supplier() {
    loadSuppliers();
}

// Load suppliers from the supplier.dat file
void Supplier::loadSuppliers() {
    ifstream inFile("supplier.dat", ios::binary);
    if (!inFile) {
        cout << "No previous data found for Suppliers. Starting fresh.\n";
        return;
    }

    SupplierInfo supplier;
    while (inFile.read(reinterpret_cast<char*>(&supplier), sizeof(supplier))) {
        suppliers.push_back(supplier);
        supplierIDCounter++;
    }
    inFile.close();
}

// Save suppliers to the supplier.dat file
void Supplier::saveSuppliers() {
    ofstream outFile("supplier.dat", ios::binary);
    if (!outFile) {
        cout << "Error saving data to file.\n";
        return;
    }

    for (const auto& supplier : suppliers) {
        outFile.write(reinterpret_cast<const char*>(&supplier), sizeof(supplier));
    }
    outFile.close();
}

// Add a new supplier
void Supplier::add_supplier() {
    string name = getValidInput<string>("Enter Supplier Name: ");
    string contact = getValidInput<string>("Enter Supplier Contact: ");
    string email = getValidInput<string>("Enter Supplier Email: ");

    SupplierInfo newSupplier;
    newSupplier.id = supplierIDCounter++;
    strncpy(newSupplier.name, name.c_str(), sizeof(newSupplier.name) - 1);
    newSupplier.name[sizeof(newSupplier.name) - 1] = '\0';
    strncpy(newSupplier.contact, contact.c_str(), sizeof(newSupplier.contact) - 1);
    newSupplier.contact[sizeof(newSupplier.contact) - 1] = '\0';
    strncpy(newSupplier.email, email.c_str(), sizeof(newSupplier.email) - 1);
    newSupplier.email[sizeof(newSupplier.email) - 1] = '\0';

    suppliers.push_back(newSupplier);
    cout << "Supplier added successfully! ID: " << newSupplier.id << endl;

    saveSuppliers();  // Save to file after adding
}

// Remove a supplier by ID
void Supplier::remove_supplier() {
    int id = getValidInput<int>("Enter Supplier ID to remove: ");

    for (auto it = suppliers.begin(); it != suppliers.end(); ++it) {
        if (it->id == id) {
            suppliers.erase(it);
            cout << "Supplier removed successfully!\n";
            saveSuppliers();  // Save to file after removal
            return;
        }
    }
    cout << "Supplier with ID " << id << " not found.\n";
}

// Search for a supplier by ID
void Supplier::search_id() {
    int id = getValidInput<int>("Enter Supplier ID to search: ");

    for (const auto& supplier : suppliers) {
        if (supplier.id == id) {
            cout << "Supplier Found:\n";
            cout << "ID: " << supplier.id << "\nName: " << supplier.name
                 << "\nContact: " << supplier.contact << "\nEmail: " << supplier.email << endl;
            return;
        }
    }
    cout << "Supplier with ID " << id << " not found.\n";
}

// Display all suppliers
void Supplier::display_suppliers() {
    if (suppliers.empty()) {
        cout << "No suppliers available.\n";
        return;
    }

    cout << "=== Supplier List ===\n";
    for (const auto& supplier : suppliers) {
        cout << "ID: " << supplier.id << ", Name: " << supplier.name
             << ", Contact: " << supplier.contact << ", Email: " << supplier.email << endl;
    }
}

