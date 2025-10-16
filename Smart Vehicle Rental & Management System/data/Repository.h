// ===================================================================
// File: Repository.h
// Description: Template class for file storage and data persistence
// ===================================================================

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class Repository {
    vector<T> items;         // container for storing objects
    string filename;         // file path (e.g., "data/vehicles.csv")

public:
    // ---------- Constructor ----------
    Repository(string file) : filename(file) {
        load(); // automatically load data when repository is created
    }

    // ---------- Add new record ----------
    void add(const T &item) {
        items.push_back(item);
        save(); // auto-save after adding
    }

    // ---------- Get all records ----------
    vector<T> &getAll() { return items; }

    // ---------- Find by Index ----------
    T &getByIndex(int index) { return items.at(index); }

    // ---------- Get total count ----------
    size_t size() const { return items.size(); }

    // ---------- Delete by Index ----------
    void remove(int index) {
        if (index >= 0 && index < (int)items.size()) {
            items.erase(items.begin() + index);
            save();
        }
    }

    // ---------- Save all data to file ----------
    void save() {
        ofstream fout(filename);
        if (!fout) {
            cerr << "Error: Unable to open " << filename << " for writing!\n";
            return;
        }

        for (auto &item : items) {
            fout << item.toCSV() << "\n";
        }
        fout.close();
    }

    // ---------- Load all data from file ----------
    void load() {
        items.clear();
        ifstream fin(filename);
        if (!fin) return; // if file doesn't exist yet, skip

        string line;
        while (getline(fin, line)) {
            if (line.empty()) continue;

            // Each type T must implement a static fromCSV() method
            T obj = T::fromCSV(line);
            items.push_back(obj);
        }
        fin.close();
    }
};

#endif
