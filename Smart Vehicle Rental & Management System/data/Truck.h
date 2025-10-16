// ================================================
// File: Truck.h
// Description: Derived class representing a Truck
// ================================================

#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

class Truck : public Vehicle {
    double cargoCapacity;   // in tons
    bool heavyDuty;         // true if heavy-duty truck

public:
    // ---------- Constructor ----------
    Truck(int id = 0, string make = "", string model = "", int year = 0,
          double baseRate = 0.0, bool available = true,
          double cargoCapacity = 5.0, bool heavyDuty = false)
        : Vehicle(id, "Truck", make, model, year, baseRate, available),
          cargoCapacity(cargoCapacity), heavyDuty(heavyDuty) {}

    // ---------- Override Fare Calculation ----------
    double calculateFare(int days) const override {
        double total = baseRate * days;
        if (cargoCapacity > 5)
            total += 500; // additional charge for high-capacity truck
        if (heavyDuty)
            total += 300; // surcharge for heavy-duty trucks
        return total;
    }

    // ---------- Override Display ----------
    void displayInfo() const override {
        cout << left << setw(6) << id
             << setw(10) << type
             << setw(12) << make
             << setw(12) << model
             << setw(8) << year
             << setw(10) << baseRate
             << setw(10) << cargoCapacity
             << setw(10) << (heavyDuty ? "Heavy" : "Light")
             << (isAvailable ? "Available" : "Rented") << endl;
    }

    // ---------- Extend CSV Serialization ----------
    string toCSV() const override {
        return Vehicle::toCSV() + "," + to_string(cargoCapacity) + "," + (heavyDuty ? "Heavy" : "Light");
    }
};

#endif
