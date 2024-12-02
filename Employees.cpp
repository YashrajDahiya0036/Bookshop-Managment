#include "Employees.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Constructor to load employee data from file
Employee::Employee() {
    loadEmployees();
}

// Load employees from the employee.dat file
void Employee::loadEmployees() {
    ifstream inFile("employee.dat", ios::binary);
    if (!inFile) {
        cout << "No previous data found for employees. Starting fresh.\n";
        return;
    }

    EmployeeInfo employee;
    while (inFile.read(reinterpret_cast<char*>(&employee), sizeof(employee))) {
        employees.push_back(employee);
        employeeIDCounter++;
    }
    inFile.close();
}

// Save employee data to the employee.dat file
void Employee::saveEmployees() {
    ofstream outFile("employee.dat", ios::binary);
    if (!outFile) {
        cout << "Error saving data to file.\n";
        return;
    }

    for (const auto& employee : employees) {
        outFile.write(reinterpret_cast<const char*>(&employee), sizeof(employee));
    }
    outFile.close();
}

// Add a new employee
void Employee::add_emp() {
    string name = getValidInput<string>("Enter Employee Name: ");
    string phone = getValidInput<string>("Enter Employee Phone Number: ");
    string address = getValidInput<string>("Enter Employee Address: ");
    double salary = getValidInput<double>("Enter Employee Salary: ");

    EmployeeInfo newEmployee;
    newEmployee.id = employeeIDCounter++;
    strncpy(newEmployee.name, name.c_str(), sizeof(newEmployee.name) - 1);
    newEmployee.name[sizeof(newEmployee.name) - 1] = '\0';
    strncpy(newEmployee.phone, phone.c_str(), sizeof(newEmployee.phone) - 1);
    newEmployee.phone[sizeof(newEmployee.phone) - 1] = '\0';
    strncpy(newEmployee.address, address.c_str(), sizeof(newEmployee.address) - 1);
    newEmployee.address[sizeof(newEmployee.address) - 1] = '\0';
    newEmployee.salary = salary;

    employees.push_back(newEmployee);
    cout << "Employee added successfully! ID: " << newEmployee.id << endl;

    saveEmployees();  // Save to file after adding
}

// Search for an employee by ID
void Employee::search_emp() {
    int id = getValidInput<int>("Enter Employee ID to search: ");

    for (const auto& employee : employees) {
        if (employee.id == id) {
            cout << "Employee Found:\n";
            cout << "ID: " << employee.id << "\nName: " << employee.name
                 << "\nPhone: " << employee.phone << "\nAddress: " << employee.address
                 << "\nSalary: " << employee.salary << endl;
            return;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
}

// Display all employees
void Employee::display() {
    if (employees.empty()) {
        cout << "No employees available.\n";
        return;
    }

    cout << "=== Employee List ===\n";
    for (const auto& employee : employees) {
        cout << "ID: " << employee.id << ", Name: " << employee.name
             << ", Phone: " << employee.phone << ", Address: " << employee.address
             << ", Salary: " << employee.salary << endl;
    }
}

// Update employee salary
void Employee::update_salary() {
    int id = getValidInput<int>("Enter Employee ID to update salary: ");

    for (auto& employee : employees) {
        if (employee.id == id) {
            double newSalary = getValidInput<double>("Enter new salary: ");
            employee.salary = newSalary;
            cout << "Salary updated successfully for Employee ID: " << id << endl;
            saveEmployees();  // Save to file after updating
            return;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
}

// Update phone number
void Employee::update_phone(int id) {
    for (auto& employee : employees) {
        if (employee.id == id) {
            string newPhone = getValidInput<string>("Enter new phone number: ");
            strncpy(employee.phone, newPhone.c_str(), sizeof(employee.phone) - 1);
            employee.phone[sizeof(employee.phone) - 1] = '\0';
            cout << "Phone number updated successfully for Employee ID: " << id << endl;
            saveEmployees();  // Save to file after updating
            return;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
}

// Update address
void Employee::update_address(int id) {
    for (auto& employee : employees) {
        if (employee.id == id) {
            string newAddress = getValidInput<string>("Enter new address: ");
            strncpy(employee.address, newAddress.c_str(), sizeof(employee.address) - 1);
            employee.address[sizeof(employee.address) - 1] = '\0';
            cout << "Address updated successfully for Employee ID: " << id << endl;
            saveEmployees();  // Save to file after updating
            return;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
}

// Remove employee
void Employee::delete_emp(){
    int id = getValidInput<int>("Enter Employee ID to delete: ");
    for (auto it = employees.begin(); it != employees.end(); ++it)
    {
        if (it->id == id)
        {
            employees.erase(it);
            cout << "Employee removed successfully!\n";
            saveEmployees();; // Save to file after removal
            return;
        }
    }
    cout << "Employee with ID " << id << " not found.\n";
}