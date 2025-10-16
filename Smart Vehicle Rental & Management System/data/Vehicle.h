// ================================================
// File: Vehicle.h
// Description: Abstract base class for all vehicles
// ================================================

#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Vehicle {
protected:
    int id;
    string type;       // Car / Bike / Truck
    string make;       // Brand
    string model;      // Model name
    int year;
    double baseRate;   // base rent per day
    bool isAvailable;

public:
    // ---------- Constructor ----------
    Vehicle(int id = 0, string type = "", string make = "", string model = "",
            int year = 0, double baseRate = 0.0, bool available = true)
        : id(id), type(type), make(make), model(model), year(year),
          baseRate(baseRate), isAvailable(available) {}

    // ---------- Virtual Destructor ----------
    virtual ~Vehicle() {}

    // ---------- Pure Virtual Methods ----------
    virtual double calculateFare(int days) const = 0;
    virtual void displayInfo() const = 0;

    // ---------- Getters ----------
    int getId() const { return id; }
    string getType() const { return type; }
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    double getBaseRate() const { return baseRate; }
    bool available() const { return isAvailable; }

    // ---------- Setters ----------
    void setAvailable(bool status) { isAvailable = status; }

    // ---------- Serialization for file storage ----------
    virtual string toCSV() const {
        return to_string(id) + "," + type + "," + make + "," + model + "," +
               to_string(year) + "," + to_string(baseRate) + "," +
               (isAvailable ? "Yes" : "No");
    }

    // ---------- Operator Overloading for Display ----------
    friend ostream &operator<<(ostream &os, const Vehicle &v) {
        os << left << setw(6) << v.id
           << setw(10) << v.type
           << setw(12) << v.make
           << setw(12) << v.model
           << setw(8) << v.year
           << setw(10) << v.baseRate
           << (v.isAvailable ? "Available" : "Rented");
        return os;
    }
};

#endif
