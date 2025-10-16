// =======================================================
// File: Customer.h
// Description: Class representing a registered customer
// =======================================================

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <sstream>   // for std::stringstream

#include <iomanip>
#include <string>
using namespace std;

class Customer {
    int id;
    string name;
    string licenseNo;
    string phone;
    double walletBalance;

public:
    // ---------- Constructor ----------
    Customer(int id = 0, string name = "", string licenseNo = "",
             string phone = "", double walletBalance = 0.0)
        : id(id), name(name), licenseNo(licenseNo),
          phone(phone), walletBalance(walletBalance) {}

    // ---------- Getters ----------
    int getId() const { return id; }
    string getName() const { return name; }
    string getLicenseNo() const { return licenseNo; }
    string getPhone() const { return phone; }
    double getWalletBalance() const { return walletBalance; }

    // ---------- Setters ----------
    void setWalletBalance(double balance) { walletBalance = balance; }

    // ---------- Methods ----------
    void updateBalance(double amount) { walletBalance += amount; }

    void displayInfo() const {
        cout << left << setw(6) << id
             << setw(15) << name
             << setw(15) << licenseNo
             << setw(15) << phone
             << "Rs. " << fixed << setprecision(2) << walletBalance << endl;
    }

    // ---------- Convert to CSV for file storage ----------
    string toCSV() const {
        return to_string(id) + "," + name + "," + licenseNo + "," +
               phone + "," + to_string(walletBalance);
    }

    // ---------- Operator Overloading for easy output ----------
    friend ostream &operator<<(ostream &os, const Customer &c) {
        os << left << setw(6) << c.id
           << setw(15) << c.name
           << setw(15) << c.licenseNo
           << setw(15) << c.phone
           << "Rs. " << fixed << setprecision(2) << c.walletBalance;
        return os;
    }


        // ---------- Convert from CSV ----------
    static Customer fromCSV(const std::string &line) {
        Customer c;
        std::stringstream ss(line);
        std::string item;

        std::getline(ss, item, ',');
        c.id = std::stoi(item);

        std::getline(ss, c.name, ',');
        std::getline(ss, c.licenseNo, ',');
        std::getline(ss, c.phone, ',');

        std::getline(ss, item, ',');
        c.walletBalance = std::stod(item);

        return c;
    }

};

#endif
