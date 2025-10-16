// ============================================================================
// File: RentalManager.h
// Description: Core management class connecting Vehicles, Customers & Rentals
// ============================================================================

#ifndef RENTALMANAGER_H
#define RENTALMANAGER_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <vector>
#include "Car.h"
#include "Bike.h"
#include "Truck.h"
#include "Customer.h"
#include "RentalTransaction.h"
#include "Repository.h"

using namespace std;

class RentalManager {
    Repository<Customer> &customers;
    Repository<RentalTransaction> &transactions;
    vector<Vehicle *> &vehicles; // vector of pointers to polymorphic Vehicle objects

public:
    // ---------- Constructor ----------
    RentalManager(Repository<Customer> &c, Repository<RentalTransaction> &t, vector<Vehicle *> &v)
        : customers(c), transactions(t), vehicles(v) {}

    // ---------- Generate unique transaction ID ----------
    string generateTxnId() {
        string prefix = "TXN";
        string id = to_string(transactions.size() + 1);
        while (id.size() < 3) id = "0" + id;
        return prefix + id;
    }

    // ---------- Rent a Vehicle ----------
    void rentVehicle(int customerId, int vehicleId, int days, string rentDate, string dueDate) {
        Customer *cust = nullptr;
        for (auto &c : customers.getAll()) {
            if (c.getId() == customerId) {
                cust = &c;
                break;
            }
        }
        if (!cust) {
            cout << "❌ Customer not found!\n";
            return;
        }

        Vehicle *veh = nullptr;
        for (auto &v : vehicles) {
            if (v->getId() == vehicleId && v->available()) {
                veh = v;
                break;
            }
        }
        if (!veh) {
            cout << "❌ Vehicle not available or not found!\n";
            return;
        }

        double fare = veh->calculateFare(days);
        if (cust->getWalletBalance() < fare) {
            cout << "❌ Insufficient wallet balance!\n";
            return;
        }

        // Deduct amount & mark vehicle unavailable
        cust->updateBalance(-fare);
        veh->setAvailable(false);

        // Create transaction
        string txnId = generateTxnId();
        RentalTransaction txn(txnId, customerId, vehicleId, rentDate, dueDate, "", fare, "Rented");
        transactions.add(txn);

        cout << "✅ Vehicle rented successfully!\n";
        cout << "Transaction ID: " << txnId << "\n";
        cout << "Total Fare: Rs. " << fare << "\n";
    }

    // ---------- Return a Vehicle ----------
    void returnVehicle(string txnId, string returnDate) {
        RentalTransaction *txn = nullptr;
        for (auto &t : transactions.getAll()) {
            if (t.getTxnId() == txnId && t.getStatus() == "Rented") {
                txn = &t;
                break;
            }
        }
        if (!txn) {
            cout << "❌ Transaction not found or already returned!\n";
            return;
        }

        // Find Vehicle
        Vehicle *veh = nullptr;
        for (auto &v : vehicles) {
            if (v->getId() == txn->getVehicleId()) {
                veh = v;
                break;
            }
        }

        if (!veh) {
            cout << "❌ Vehicle not found!\n";
            return;
        }

        // Mark returned
        txn->setReturnDate(returnDate);
        txn->setStatus("Returned");
        veh->setAvailable(true);
        transactions.save(); // persist change

        cout << "✅ Vehicle returned successfully!\n";
    }

    // ---------- Display All Vehicles ----------
    void showAllVehicles() const {
        cout << "\n-------------------------------- VEHICLE LIST --------------------------------\n";
        cout << left << setw(6) << "ID" << setw(10) << "Type" << setw(12) << "Make"
             << setw(12) << "Model" << setw(8) << "Year" << setw(10)
             << "Rate" << setw(10) << "Extra" << setw(10) << "Detail"
             << "Status" << endl;
        cout << "-----------------------------------------------------------------------------\n";
        for (auto &v : vehicles)
            v->displayInfo();
    }

    // ---------- Display All Customers ----------
    void showAllCustomers() const {
        cout << "\n-------------------------- CUSTOMER LIST --------------------------\n";
        cout << left << setw(6) << "ID" << setw(15) << "Name"
             << setw(15) << "License" << setw(15) << "Phone"
             << "Wallet\n";
        cout << "------------------------------------------------------------------\n";
        for (auto &c : customers.getAll())
            c.displayInfo();
    }

    // ---------- Display Transactions ----------
    void showAllTransactions() const {
        cout << "\n------------------------- TRANSACTION REPORT -------------------------\n";
        cout << left << setw(10) << "TxnID" << setw(8) << "CustID"
             << setw(8) << "VehID" << setw(15) << "RentDate"
             << setw(15) << "DueDate" << setw(15) << "ReturnDate"
             << setw(10) << "Fare" << setw(10) << "Status" << endl;
        cout << "----------------------------------------------------------------------\n";
        for (auto &t : transactions.getAll())
            t.displayInfo();
    }
};

#endif
