// =====================================================================
// File: main.cpp
// Project: Smart Vehicle Rental & Management System
// Author: Ram Niwas
// =====================================================================

#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "Car.h"
#include "Bike.h"
#include "Truck.h"
#include "Customer.h"
#include "RentalTransaction.h"
#include "RentalManager.h"
#include "Repository.h"
#include "Exceptions.h"

using namespace std;

// ---------- Utility function for date input ----------
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
       << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}

// ---------- Main Program ----------
int main() {
    system("cls"); // clear screen (use "clear" on Linux/Mac)

    cout << "=========================================================\n";
    cout << "   SMART VEHICLE RENTAL & MANAGEMENT SYSTEM (C++)\n";
    cout << "=========================================================\n";

    // ---------- Initialize Data Repositories ----------
    Repository<Customer> customers("data/customers.csv");
    Repository<RentalTransaction> transactions("data/transactions.csv");

    // ---------- Load vehicles manually for now ----------
    vector<Vehicle *> vehicles;
    vehicles.push_back(new Car(101, "Toyota", "Glanza", 2023, 1200, true, 5, "Petrol"));
    vehicles.push_back(new Bike(102, "Honda", "Shine", 2022, 500, true, 125, true));
    vehicles.push_back(new Truck(103, "Ashok Leyland", "MiniTruck", 2021, 3000, true, 6.5, true));

    RentalManager manager(customers, transactions, vehicles);

    int mainChoice = 0;
    do {
        cout << "\n================= MAIN MENU =================\n";
        cout << "1. Admin Menu\n";
        cout << "2. Customer Menu\n";
        cout << "3. View Reports\n";
        cout << "4. Exit\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            int adminChoice = 0;
            do {
                cout << "\n----------------- ADMIN MENU -----------------\n";
                cout << "1. Show All Vehicles\n";
                cout << "2. Show All Customers\n";
                cout << "3. Show Transactions\n";
                cout << "4. Back to Main Menu\n";
                cout << "----------------------------------------------\n";
                cout << "Enter choice: ";
                cin >> adminChoice;

                switch (adminChoice) {
                case 1: manager.showAllVehicles(); break;
                case 2: manager.showAllCustomers(); break;
                case 3: manager.showAllTransactions(); break;
                case 4: break;
                default: cout << "❌ Invalid choice!\n"; break;
                }
            } while (adminChoice != 4);
            break;
        }

        case 2: {
            int custChoice = 0;
            do {
                cout << "\n---------------- CUSTOMER MENU ----------------\n";
                cout << "1. Register New Customer\n";
                cout << "2. Rent Vehicle\n";
                cout << "3. Return Vehicle\n";
                cout << "4. Back to Main Menu\n";
                cout << "-----------------------------------------------\n";
                cout << "Enter choice: ";
                cin >> custChoice;

                if (custChoice == 1) {
                    int id; string name, license, phone; double bal;
                    cout << "Enter Customer ID: "; cin >> id;
                    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                    cout << "Enter License No: "; getline(cin, license);
                    cout << "Enter Phone No: "; getline(cin, phone);
                    cout << "Enter Wallet Balance: "; cin >> bal;

                    customers.add(Customer(id, name, license, phone, bal));
                    cout << "✅ Customer Registered Successfully!\n";
                }
                else if (custChoice == 2) {
                    int cid, vid, days;
                    cout << "Enter Customer ID: "; cin >> cid;
                    cout << "Enter Vehicle ID: "; cin >> vid;
                    cout << "Enter Number of Days: "; cin >> days;
                    string today = getCurrentDate();

                    stringstream ss;
                    ss << "2025-10-" << stoi(today.substr(8,2)) + days; // fake due date
                    string dueDate = ss.str();

                    manager.rentVehicle(cid, vid, days, today, dueDate);
                }
                else if (custChoice == 3) {
                    string txnId, returnDate;
                    cout << "Enter Transaction ID: "; cin >> txnId;
                    cout << "Enter Return Date (YYYY-MM-DD): "; cin >> returnDate;
                    manager.returnVehicle(txnId, returnDate);
                }
                else if (custChoice == 4) break;
                else cout << "❌ Invalid choice!\n";

            } while (custChoice != 4);
            break;
        }

        case 3:
            manager.showAllTransactions();
            break;

        case 4:
            cout << "\n💾 Saving data and exiting safely...\n";
            customers.save();
            transactions.save();
            cout << "✅ All data saved successfully.\n";
            break;

        default:
            cout << "❌ Invalid main menu choice!\n";
        }

    } while (mainChoice != 4);

    // ---------- Cleanup memory ----------
    for (auto v : vehicles)
        delete v;

    cout << "\nThank you for using Smart Vehicle Rental System!\n";
    cout << "------------------------------------------------\n";
    return 0;
}
