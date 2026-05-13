#pragma once
#include "ResourceManager.h"
#include <string>
#include <vector>
using namespace std;

class FileManager
{
private:
    string inventoryFile;
    string transactionsFile;

public:
    FileManager(const string &inventoryFile = "inventory.txt",
                const string &transactionsFile = "transactions.txt");
    void loadInventory(ResourceManager &rm);
    void saveInventory(const ResourceManager &rm);
    void logTransaction(const string &logLine);
    vector<string> loadUsers(const string &userFile = "users.txt");
    void saveUsers(const vector<string> &userLines,
                   const string &userFile = "users.txt");
};