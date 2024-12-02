#ifndef PURCHASES_H
#define PURCHASES_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "ValidInput.h"

using namespace std;

class Purchases {
private:
    struct OrderInfo {
        int orderID;
        char bookTitle[100];
        char supplierName[100];
        int quantity;
        double total_cost;
        char status[20]; // "Pending", "Cancelled", or "Received"
    };

    vector<OrderInfo> orders;
    int orderIDCounter = 1;

    void loadOrders();  // Load orders from file
    void saveOrders();  // Save orders to file

    bool checkSupplierExists(const string& supplierName);  // Check if supplier exists

public:
    Purchases();

    void new_order();       // Place a new order
    void view();            // View all orders
    void mark_cancel();     // Mark an order as "Cancelled"
    void mark_received();   // Mark an order as "Received"
};

#endif
