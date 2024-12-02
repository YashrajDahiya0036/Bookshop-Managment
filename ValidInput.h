#ifndef VALIDINPUT_H
#define VALIDINPUT_H

#include <iostream>
#include <limits>
#include <string>
#include <cstring>

using namespace std;

// Template function to get valid input of any type
template <typename T>
inline T getValidInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            return value;
        }

        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        cout << "Invalid input. Please try again.\n";
    }
}

// Specialization for string input
template <>
inline string getValidInput<string>(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);

        if (!value.empty()) {
            return value;
        }
        cout << "Invalid input. Please enter a non-empty value.\n";
    }
}

#endif
