#include <iostream>
#include "Supplier.h"
#include "Book.h"
#include "Purchases.h"
#include "Employees.h"
#include "Sales.h"

using namespace std;

void displayMainMenu() {
    cout << "\n=== Main Menu ===\n";
    cout << "1. Supplier Management\n";
    cout << "2. Book Management\n";
    cout << "3. Employee Management\n";
    cout << "4. Purchases Management\n";
    cout << "5. Sales Management\n";
    cout << "6. Exit\n";
}

void supplierMenu(Supplier& supplierManager) {
    int supplierChoice;
    do {
        cout << "\n=== Supplier Management ===\n";
        cout << "1. Add Supplier\n";
        cout << "2. Remove Supplier\n";
        cout << "3. Search Supplier by ID\n";
        cout << "4. Display All Suppliers\n";
        cout << "5. Back to Main Menu\n";
        supplierChoice = getValidInput<int>("Enter your choice: ");

        switch (supplierChoice) {
            case 1:
                supplierManager.add_supplier();
                break;
            case 2:
                supplierManager.remove_supplier();
                break;
            case 3:
                supplierManager.search_id();
                break;
            case 4:
                supplierManager.display_suppliers();
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (supplierChoice != 5);
}

void bookMenu(Book& bookManager, Sales& salesManager) {
    int bookChoice;
    do {
        cout << "\n=== Book Management ===\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Update Book Price\n";
        cout << "4. Search Book by ID\n";
        cout << "5. Display All Books\n";
        cout << "6. Sell Book (Generate Invoice)\n";
        cout << "7. Apply Discount to Book\n";
        cout << "8. Remove Discount from Book\n";
        cout << "9. Back to Main Menu\n";
        bookChoice = getValidInput<int>("Enter your choice: ");

        switch (bookChoice) {
            case 1:
                bookManager.add_book();
                break;
            case 2:
                bookManager.remove_book();
                break;
            case 3:
                bookManager.update_price();
                break;
            case 4:
                bookManager.search_book();
                break;
            case 5:
                bookManager.display_books();
                break;
            case 6:
                bookManager.sell_books(salesManager);
                break;
            case 7:
                bookManager.apply_discount();
                break;
            case 8:
                bookManager.remove_discount();
                break;
            case 9:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (bookChoice != 9);
}

void employeeMenu(Employee& employeeManager) {
    int choice;
    do {
        cout << "\n=== Employee Management ===\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee by ID\n";
        cout << "3. Display All Employees\n";
        cout << "4. Update Employee Salary\n";
        cout << "5. Update Employee Phone\n";
        cout << "6. Update Employee Address\n";
        cout << "7. Remove Employee\n";
        cout << "8. Back to Main Menu\n";
        choice = getValidInput<int>("Enter your choice: ");
        
        switch (choice) {
            case 1:
                employeeManager.add_emp();
                break;
            case 2:
                employeeManager.search_emp();
                break;
            case 3:
                employeeManager.display();
                break;
            case 4:
                employeeManager.update_salary();
                break;
            case 5:
                {
                    int emp_id = getValidInput<int>("Enter Employee ID to update phone: ");
                    employeeManager.update_phone(emp_id);
                }
                break;
            case 6:
                {
                    int emp_id = getValidInput<int>("Enter Employee ID to update address: ");
                    employeeManager.update_address(emp_id);
                }
                break;
            case 7:
                employeeManager.delete_emp();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

void purchasesMenu(Purchases& purchasesManager) {
    int purchasesChoice;
    do {
        cout << "\n=== Purchases Management ===\n";
        cout << "1. Add New Order\n";
        cout << "2. View All Orders\n";
        cout << "3. Mark Order as Cancelled\n";
        cout << "4. Mark Order as Received\n";
        cout << "5. Back to Main Menu\n";
        purchasesChoice = getValidInput<int>("Enter your choice: ");

        switch (purchasesChoice) {
            case 1:
                purchasesManager.new_order();
                break;
            case 2:
                purchasesManager.view();
                break;
            case 3:
                purchasesManager.mark_cancel();
                break;
            case 4:
                purchasesManager.mark_received();
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (purchasesChoice != 5);
}

void salesMenu(Sales& salesManager) {
    int salesChoice;
    do {
        cout << "\n=== Sales Management ===\n";
        cout << "1. Display All Sales\n";
        cout << "2. Find Total Sales\n";
        cout << "3. Display All Invoices\n";
        cout << "4. Back to Main Menu\n";
        salesChoice = getValidInput<int>("Enter your choice: ");

        switch (salesChoice) {
            case 1:
                salesManager.display_sales();
                break;
            case 2: {
                double total = salesManager.find_total_sales();
                cout << "Total Sales Amount: $" << total << endl;
                break;
            }
            case 3:
                salesManager.display_invoices();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (salesChoice != 4);
}

int main() {
    Supplier supplierManager;
    Book bookManager;
    Employee employeeManager;
    Purchases purchasesManager;
    Sales salesManager;

    int choice;
    do {
        displayMainMenu();
        choice = getValidInput<int>("Enter your choice: ");

        switch (choice) {
            case 1:
                supplierMenu(supplierManager);
                break;
            case 2:
                bookMenu(bookManager, salesManager);
                break;
            case 3:
                employeeMenu(employeeManager);
                break;
            case 4:
                purchasesMenu(purchasesManager);
                break;
            case 5:
                salesMenu(salesManager);
                break;
            case 6:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
