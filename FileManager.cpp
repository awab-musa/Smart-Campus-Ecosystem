#include "FileManager.h"
#include "CampusExceptions.h"
#include "LabHardware.h"
#include "CafeteriaPerishable.h"
#include "BookstoreMedia.h"
#include <fstream>
#include <iostream>
using namespace std;

FileManager::FileManager(const string& inventoryFile, const string& transactionsFile)
    : inventoryFile(inventoryFile), transactionsFile(transactionsFile) {}

void FileManager::loadInventory(ResourceManager& rm) {
    ifstream file(inventoryFile);
    if (!file.is_open()) throw FileNotFoundException(inventoryFile);
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        string tag = line.substr(0, line.find('|'));
        Resource* r = nullptr;
        if (tag == "LabHardware")  r = LabHardware::fromString(line);
        else if (tag == "CafeteriaPerishable") r = CafeteriaPerishable::fromString(line);
        else if (tag == "BookstoreMedia") r = BookstoreMedia::fromString(line);
        if (r) rm.addResource(r);
    }
    cout << "[FileManager] Inventory loaded from '" << inventoryFile << "'.\n";
}

void FileManager::saveInventory(const ResourceManager& rm) {
    ofstream file(inventoryFile);
    if (!file.is_open()) throw FileWriteException(inventoryFile);
    for (const string& line : rm.serializeAll())
        file << line << "\n";
    cout << "[FileManager] Inventory saved to '" << inventoryFile << "'.\n";
}

void FileManager::logTransaction(const string& logLine) {
    ofstream file(transactionsFile, ios::app);
    if (!file.is_open()) throw FileWriteException(transactionsFile);
    file << logLine << "\n";
}

vector<string> FileManager::loadUsers(const string& userFile) {
    ifstream file(userFile);
    if (!file.is_open()) throw FileNotFoundException(userFile);
    vector<string> lines;
    string line;
    while (getline(file, line))
        if (!line.empty()) lines.push_back(line);
    return lines;
}

void FileManager::saveUsers(const vector<string>& userLines, const string& userFile) {
    ofstream file(userFile);
    if (!file.is_open()) throw FileWriteException(userFile);
    for (const string& line : userLines)
        file << line << "\n";
}
