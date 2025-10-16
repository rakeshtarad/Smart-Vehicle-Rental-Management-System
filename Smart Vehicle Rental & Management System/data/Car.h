// ================================================
// File: Car.h
// Description: Derived class representing a Car
// ================================================

#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
    int seats;           // number of seats
    string fuelType;     // Petrol, Diesel, EV

public:
    // ---------- Constructor ----------
    Car(int id = 0, string make = "", string model = "", int year = 0,
        double baseRate = 0.0, bool available = true,
        int seats = 4, string fuelType = "Petrol")
        : Vehicle(id, "Car", make, model, year, baseRate, available),
          seats(seats), fuelType(fuelType) {}

    // ---------- Override Fare Calculation ----------
    double calculateFare(int days) const override {
        double total = baseRate * days;
        // Additional fare rules
        if (fuelType == "Diesel") total += 200;     // diesel surcharge
        if (fuelType == "EV") total -= 150;         // eco discount
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
             << setw(8) << seats
             << setw(10) << fuelType
             << (isAvailable ? "Available" : "Rented") << endl;
    }

    // ---------- Extend CSV Serialization ----------
    string toCSV() const override {
        return Vehicle::toCSV() + "," + to_string(seats) + "," + fuelType;
    }
};

#endif
