#ifndef SALES_H
#define SALES_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <limits>
#include "ValidInput.h" 

using namespace std;

// Date structure to handle date information
struct Date {
    int day, month, year;
};

// Sales Class Definition
class Sales {
private:
    // Sales information
    struct SalesInfo {
        int invoice_id;
        int member_id;
        int book_id;
        int qty;
        int amount;
        Date date_s;
    };

    // Invoice information (separate from sales)
    struct InvoiceInfo {
        int invoice_id;
        int book_id;
        int qty;
        double price;
        Date date_s;
    };

    vector<SalesInfo> sales;
    vector<InvoiceInfo> invoices;
    int invoiceCounter = 1;

    // Load sales data from file
    void loadSales();  

    // Save sales data to file
    void saveSales();  

    // Load invoices data from file
    void loadInvoices();

    // Save invoices data to file
    void saveInvoices();

public:
    Sales();

    // Add new sale (keep it as before)
    void add_sale(int book_id, int qty, double totalAmount, double finalPrice);

    // Display all sales
    void display_sales();  

    // Add invoice and save to invoices file
    void add_invoice(int book_id, int qty, double price);

    // Display all invoices
    void display_invoices();

    // Find total sales (sum of all sales amounts)
    double find_total_sales();
};

#endif
