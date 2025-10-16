// ==========================================================
// File: Exceptions.h
// Description: Custom exception classes for error handling
// ==========================================================

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>
using namespace std;

// ---------- Vehicle not available ----------
class VehicleNotAvailable : public exception {
    string message;
public:
    VehicleNotAvailable(string msg = "Vehicle is not available for rent!") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ---------- Invalid Input ----------
class InvalidInput : public exception {
    string message;
public:
    InvalidInput(string msg = "Invalid input provided!") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ---------- Insufficient Balance ----------
class InsufficientBalance : public exception {
    string message;
public:
    InsufficientBalance(string msg = "Insufficient wallet balance!") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ---------- File I/O Error ----------
class FileIOException : public exception {
    string message;
public:
    FileIOException(string msg = "File could not be opened or written!") : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

#endif
