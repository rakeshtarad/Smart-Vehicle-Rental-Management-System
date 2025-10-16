// ================================================
// File: Bike.h
// Description: Derived class representing a Bike
// ================================================

#ifndef BIKE_H
#define BIKE_H

#include "Vehicle.h"

class Bike : public Vehicle {
    int engineCC;        // engine capacity (e.g., 150, 350)
    bool isGear;         // true if geared bike, false if scooter

public:
    // ---------- Constructor ----------
    Bike(int id = 0, string make = "", string model = "", int year = 0,
         double baseRate = 0.0, bool available = true,
         int engineCC = 150, bool isGear = true)
        : Vehicle(id, "Bike", make, model, year, baseRate, available),
          engineCC(engineCC), isGear(isGear) {}

    // ---------- Override Fare Calculation ----------
    double calculateFare(int days) const override {
        double total = baseRate * days;
        if (engineCC > 300)
            total += 150;  // premium charge for high CC
        if (!isGear)
            total -= 50;   // small discount for gearless scooters
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
             << setw(8) << engineCC
             << setw(10) << (isGear ? "Gear" : "No Gear")
             << (isAvailable ? "Available" : "Rented") << endl;
    }

    // ---------- Extend CSV Serialization ----------
    string toCSV() const override {
        return Vehicle::toCSV() + "," + to_string(engineCC) + "," + (isGear ? "Gear" : "NoGear");
    }
};

#endif
