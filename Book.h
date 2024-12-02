#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include <ctime>
#include "ValidInput.h"
#include "Sales.h"

using namespace std;

class Book
{
private:
    struct Date
    {
        int day;
        int month;
        int year;

        // Default constructor to set date to today
        Date()
        {
            time_t t = time(0);
            struct tm *now = localtime(&t);
            year = now->tm_year + 1900; // tm_year is years since 1900
            month = now->tm_mon + 1;    // tm_mon is months since January (0-11)
            day = now->tm_mday;         // day of the month
        }

        // Method to input date
        void input_date()
        {
            cout << "Enter purchase date (dd mm yyyy) or press Enter to use today's date: ";
            string input;
            getline(cin, input);
            if (input.empty())
            {
                // Today's date is used if no input
                return;
            }

            stringstream ss(input);
            ss >> day >> month >> year;
        }

        // Calculate age in years
        int calculate_age() const
        {
            time_t t = time(0);
            struct tm *now = localtime(&t);
            int current_year = now->tm_year + 1900;
            int current_month = now->tm_mon + 1;
            int current_day = now->tm_mday;

            int age = current_year - year;

            if (current_month < month || (current_month == month && current_day < day))
            {
                age--;
            }

            return age;
        }
    };

    struct BookInfo
    {
        int id;
        char title[100];
        char author[50];
        double price;
        int quantity;
        double discount = 0.0; // Discount as a percentage
        Date publish_date;     // Date the book was published
    };

    vector<BookInfo> books;
    int bookIDCounter = 1;

    void loadBooks();

public:
    void saveBooks();
    Book();

    void add_book();
    void remove_book();
    void update_price();
    void search_book();
    void display_books();
    void sell_books(Sales &salesManager);
    void sold_books(Sales &salesManager);
    void apply_discount();
    void remove_discount();
    void update_dynamic_discount(BookInfo &book);
};

#endif
