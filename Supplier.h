#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include "ValidInput.h" 

using namespace std;

class Supplier {
public:
    struct SupplierInfo {
        int id;
        char name[100];
        char contact[50];
        char email[100];
    };

private:
    vector<SupplierInfo> suppliers;
    int supplierIDCounter = 1;

    void loadSuppliers();
    void saveSuppliers();

public:
    Supplier();
    
    void add_supplier();
    void remove_supplier();
    void search_id();
    void display_suppliers();

    // Provide a getter to access suppliers list
    const vector<SupplierInfo>& getSuppliers() const { return suppliers; }
};

#endif
