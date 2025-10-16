#ifndef RENTALTRANSACTION_H
#define RENTALTRANSACTION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>  // <<-- required for stringstream
using namespace std;

class RentalTransaction {
    string txnId;
    int customerId;
    int vehicleId;
    string rentDate;
    string dueDate;
    string returnDate;
    double totalFare;
    string status;

public:
    // ---------- Constructor ----------
    RentalTransaction(string txnId = "", int customerId = 0, int vehicleId = 0,
                      string rentDate = "", string dueDate = "",
                      string returnDate = "", double totalFare = 0.0,
                      string status = "Rented")
        : txnId(txnId), customerId(customerId), vehicleId(vehicleId),
          rentDate(rentDate), dueDate(dueDate), returnDate(returnDate),
          totalFare(totalFare), status(status) {}

    // ---------- Getters ----------
    string getTxnId() const { return txnId; }
    int getCustomerId() const { return customerId; }
    int getVehicleId() const { return vehicleId; }
    string getRentDate() const { return rentDate; }
    string getDueDate() const { return dueDate; }
    string getReturnDate() const { return returnDate; }
    double getTotalFare() const { return totalFare; }
    string getStatus() const { return status; }

    // ---------- Setters ----------
    void setReturnDate(string date) { returnDate = date; }
    void setTotalFare(double fare) { totalFare = fare; }
    void setStatus(string s) { status = s; }

    // ---------- Display ----------
    void displayInfo() const {
        cout << left << setw(10) << txnId
             << setw(8) << customerId
             << setw(8) << vehicleId
             << setw(15) << rentDate
             << setw(15) << dueDate
             << setw(15) << returnDate
             << setw(10) << totalFare
             << setw(10) << status << endl;
    }

    // ---------- Convert to CSV ----------
    string toCSV() const {
        return txnId + "," + to_string(customerId) + "," + to_string(vehicleId) + "," +
               rentDate + "," + dueDate + "," + returnDate + "," +
               to_string(totalFare) + "," + status;
    }

    // ---------- Convert from CSV ----------
    static RentalTransaction fromCSV(const string &line) {
        RentalTransaction txn;
        stringstream ss(line);
        string item;

        getline(ss, txn.txnId, ',');
        getline(ss, item, ','); txn.customerId = stoi(item);
        getline(ss, item, ','); txn.vehicleId = stoi(item);
        getline(ss, txn.rentDate, ',');
        getline(ss, txn.dueDate, ',');
        getline(ss, txn.returnDate, ',');
        getline(ss, item, ','); txn.totalFare = stod(item);
        getline(ss, txn.status, ',');

        return txn;
    }

    // ---------- Operator Overload ----------
    friend ostream &operator<<(ostream &os, const RentalTransaction &t) {
        os << left << setw(10) << t.txnId
           << setw(8) << t.customerId
           << setw(8) << t.vehicleId
           << setw(15) << t.rentDate
           << setw(15) << t.dueDate
           << setw(15) << t.returnDate
           << setw(10) << t.totalFare
           << setw(10) << t.status;
        return os;
    }
};

#endif
