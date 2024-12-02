#include "Sales.h"

// Constructor - Load data from files on initialization
Sales::Sales() {
    loadSales();    // Load sales from sales.dat
    loadInvoices(); // Load invoices from invoices.dat
}

// Load sales from file
void Sales::loadSales() {
    ifstream inFile("sales.dat", ios::binary);
    if (!inFile) {
        cout << "No previous sales data found.\n";
        return;
    }

    SalesInfo sale;
    while (inFile.read(reinterpret_cast<char*>(&sale), sizeof(sale))) {
        sales.push_back(sale);
        invoiceCounter = max(invoiceCounter, sale.invoice_id + 1);  // Keep track of last invoice ID
    }
    inFile.close();
}

// Save sales to file
void Sales::saveSales() {
    ofstream outFile("sales.dat", ios::binary);
    if (!outFile) {
        cout << "Error saving sales data to file.\n";
        return;
    }

    for (const auto& sale : sales) {
        outFile.write(reinterpret_cast<const char*>(&sale), sizeof(sale));
    }
    outFile.close();
}

// Load invoices from file
void Sales::loadInvoices() {
    ifstream inFile("invoices.dat", ios::binary);
    if (!inFile) {
        cout << "No previous invoice data found.\n";
        return;
    }

    InvoiceInfo invoice;
    while (inFile.read(reinterpret_cast<char*>(&invoice), sizeof(invoice))) {
        invoices.push_back(invoice);
    }
    inFile.close();
}

// Save invoices to file
void Sales::saveInvoices() {
    ofstream outFile("invoices.dat", ios::binary);
    if (!outFile) {
        cout << "Error saving invoices data to file.\n";
        return;
    }

    for (const auto& invoice : invoices) {
        outFile.write(reinterpret_cast<const char*>(&invoice), sizeof(invoice));
    }
    outFile.close();
}

// Add a sale (similar to previous version)
void Sales::add_sale(int book_id, int qty, double totalAmount, double finalPrice) {
    SalesInfo newSale;
    newSale.invoice_id = invoiceCounter++;
    newSale.book_id = book_id;
    newSale.qty = qty;
    newSale.amount = totalAmount;
    // Assuming today's date is used for the sale
    time_t now = time(0);
    tm *ltm = localtime(&now);
    newSale.date_s = {ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900};
    sales.push_back(newSale);
    
    saveSales();  // Save sales after adding
}

// Display all sales
void Sales::display_sales() {
    if (sales.empty()) {
        cout << "No sales available.\n";
        return;
    }

    cout << "=== Sales List ===\n";
    for (const auto& sale : sales) {
        cout << "Invoice ID: " << sale.invoice_id << ", Book ID: " << sale.book_id
             << ", Quantity: " << sale.qty << ", Total Amount: " << sale.amount
             << ", Date: " << sale.date_s.day << "/" << sale.date_s.month << "/" << sale.date_s.year << endl;
    }
}

// Add a new invoice and save to invoices.dat
void Sales::add_invoice(int book_id, int qty, double price) {
    InvoiceInfo newInvoice;
    newInvoice.invoice_id = invoiceCounter++;
    newInvoice.book_id = book_id;
    newInvoice.qty = qty;
    newInvoice.price = price;
    // Assuming today's date is used for the invoice
    time_t now = time(0);
    tm *ltm = localtime(&now);
    newInvoice.date_s = {ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900};
    
    invoices.push_back(newInvoice);

    saveInvoices();  // Save invoices after adding
}

// Display all invoices
void Sales::display_invoices() {
    if (invoices.empty()) {
        cout << "No invoices available.\n";
        return;
    }

    cout << "=== Invoices List ===\n";
    for (const auto& invoice : invoices) {
        cout << "Invoice ID: " << invoice.invoice_id << ", Book ID: " << invoice.book_id
             << ", Quantity: " << invoice.qty << ", Price: " << invoice.price
             << ", Date: " << invoice.date_s.day << "/" << invoice.date_s.month << "/" << invoice.date_s.year << endl;
    }
}

// Find the total sales amount
double Sales::find_total_sales() {
    double total = 0;
    for (const auto& sale : sales) {
        total += sale.amount;
    }
    // cout << "Total Sales: " << total << endl;
    return total;
}
