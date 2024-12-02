#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include "ValidInput.h" // Assuming you're using the ValidInput template function

using namespace std;

class Employee {
private:
    struct EmployeeInfo {
        int id;
        char name[100];
        char phone[20];      // New variable for phone number
        char address[200];   // New variable for address
        double salary;
    };

    vector<EmployeeInfo> employees;
    int employeeIDCounter = 1;

    void loadEmployees();
    void saveEmployees();

public:
    Employee();
    
    void add_emp();
    void search_emp();
    void display();
    void delete_emp();
    void update_salary();
    void update_phone(int id);
    void update_address(int id);
};

#endif
