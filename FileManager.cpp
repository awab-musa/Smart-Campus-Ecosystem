#include "FileManager.h"
#include "CampusExceptions.h"
#include "ResourceManager.h"
#include "LabHardware.h"
#include "CafeteriaPerishable.h"
#include "BookstoreMedia.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

FileManager::FileManager(const string &inventoryFile, const string &transactionsFile)
    : inventoryFile(inventoryFile), transactionsFile(transactionsFile) {}

void FileManager::loadInventory(ResourceManager &rm)
{
    ifstream file(inventoryFile);
    if (!file.is_open())
        throw FileNotFoundException(inventoryFile);

    string line;
    while (getline(file, line))
    {
        // strip \r for Windows CRLF files
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty() || line[0] == '#')
            continue;

        // split by '|'
        vector<string> fields;
        stringstream ss(line);
        string token;
        while (getline(ss, token, '|'))
        {
            // strip \r from each field too (safety)
            if (!token.empty() && token.back() == '\r')
                token.pop_back();
            fields.push_back(token);
        }

        if (fields.size() < 5)
            continue;

        string tag = fields[0];
        string id = fields[1];
        string name = fields[2];
        double price = stod(fields[3]);
        int stock = stoi(fields[4]);

        try
        {
            if (tag == "LAB" && fields.size() >= 8)
            {
                int warranty = stoi(fields[5]);
                string mfr = fields[6];
                string serial = fields[7];
                rm.addResource(new LabHardware(id, name, price, stock,
                                               warranty, mfr, serial));
            }
            else if (tag == "CAFE" && fields.size() >= 8)
            {
                string expiry = fields[5];
                bool refrigerated = (fields[6] == "1");
                int calories = stoi(fields[7]);
                rm.addResource(new CafeteriaPerishable(id, name, price, stock,
                                                       expiry, refrigerated, calories));
            }
            else if (tag == "BOOK" && fields.size() >= 8)
            {
                string isbn = fields[5];
                string author = fields[6];
                int edition = stoi(fields[7]);
                rm.addResource(new BookstoreMedia(id, name, price, stock,
                                                  isbn, author, edition));
            }
            else
            {
                cerr << "[FileManager] Unknown or incomplete line skipped: "
                     << line << "\n";
            }
        }
        catch (const exception &e)
        {
            cerr << "[FileManager] Skipping malformed line: " << e.what() << "\n";
        }
    }

    cout << "[FileManager] Inventory loaded from '" << inventoryFile << "'.\n";
}

void FileManager::saveInventory(const ResourceManager &rm)
{
    ofstream file(inventoryFile);
    if (!file.is_open())
        throw FileNotFoundException(inventoryFile);
    for (const string &line : rm.serializeAll())
        file << line << "\n";
    cout << "[FileManager] Inventory saved to '" << inventoryFile << "'.\n";
}

void FileManager::logTransaction(const string &logLine)
{
    ofstream file(transactionsFile, ios::app);
    if (!file.is_open())
        throw FileNotFoundException(transactionsFile);
    file << logLine << "\n";
}

vector<string> FileManager::loadUsers(const string &userFile)
{
    ifstream file(userFile);
    if (!file.is_open())
        throw FileNotFoundException(userFile);
    vector<string> lines;
    string line;
    while (getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (!line.empty())
            lines.push_back(line);
    }
    return lines;
}

void FileManager::saveUsers(const vector<string> &userLines, const string &userFile)
{
    ofstream file(userFile);
    if (!file.is_open())
        throw FileNotFoundException(userFile);
    for (const string &line : userLines)
        file << line << "\n";
}
