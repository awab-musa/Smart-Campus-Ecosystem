#include "ResourceManager.h"
#include "LabHardware.h"
#include "CafeteriaPerishable.h"
#include "BookstoreMedia.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

using namespace std;

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager()
{
    for (Resource *r : inventory)
    {
        delete r;
    }
    inventory.clear();
}

void ResourceManager::addResource(Resource *r)
{
    if (!r)
        throw invalid_argument("Cannot add null resource.");
    inventory.push_back(r);
}

bool ResourceManager::removeResource(const string &id)
{
    for (auto it = inventory.begin(); it != inventory.end(); ++it)
    {
        if ((*it)->getResourceID() == id)
        {
            delete *it;
            inventory.erase(it);
            return true;
        }
    }
    return false;
}

Resource *ResourceManager::searchByID(const string &id) const
{
    return findById(const_cast<vector<Resource *> &>(inventory), id);
}

void ResourceManager::generateReport(const string &id) const
{
    Resource *r = searchByID(id);
    if (!r)
    {
        cout << "[Error] No resource found with ID: " << id << "\n";
        return;
    }
    r->displayInfo();
}

void ResourceManager::listAll() const
{
    if (inventory.empty())
    {
        cout << "[Inventory] No resources available.\n";
        return;
    }
    cout << "\n══════════════ Campus Inventory ══════════════\n";
    cout << left
         << setw(10) << "ID"
         << setw(28) << "Name"
         << setw(22) << "Category"
         << setw(10) << "Price"
         << setw(8) << "Stock" << "\n";
    cout << string(78, '-') << "\n";
    for (const Resource *r : inventory)
    {
        cout << left
             << setw(10) << r->getResourceID()
             << setw(28) << r->getName()
             << setw(22) << r->getCategory()
             << "EGP " << fixed << setprecision(2)
             << setw(10) << r->getPrice()
             << setw(8) << r->getStock() << "\n";
    }
    cout << "══════════════════════════════════════════════\n\n";
}

void ResourceManager::listByCategory(const string &cat) const
{
    cout << "\n── Resources in category: " << cat << " ──\n";
    bool found = false;
    for (const Resource *r : inventory)
    {
        if (r->getCategory() == cat)
        {
            cout << "  " << r->getResourceID()
                 << " | " << r->getName()
                 << " | EGP " << fixed << setprecision(2) << r->getPrice()
                 << " | Stock: " << r->getStock() << "\n";
            found = true;
        }
    }
    if (!found)
        cout << "  No items found in this category.\n";
}

Resource *ResourceManager::getHigherCost(Resource *a, Resource *b) const
{
    if (!a || !b)
        throw invalid_argument("Null resource passed to getHigherCost.");
    return (*a > *b) ? a : b;
}

void ResourceManager::compareTwoResources(const string &id1, const string &id2) const
{
    Resource *a = searchByID(id1);
    Resource *b = searchByID(id2);
    if (!a || !b)
    {
        cout << "[Compare] One or both resource IDs not found.\n";
        return;
    }
    cout << "\n── Cost Comparison ──────────────────────────\n";
    cout << "  " << a->getName() << "  (EGP " << fixed << setprecision(2) << a->getPrice() << ")\n";
    cout << "  " << b->getName() << "  (EGP " << fixed << setprecision(2) << b->getPrice() << ")\n";
    Resource *higher = getHigherCost(a, b);
    cout << "  ► Higher cost burden: " << higher->getName() << "\n";
    cout << "────────────────────────────────────────────\n\n";
}

const vector<Resource *> &ResourceManager::getInventory() const
{
    return inventory;
}

int ResourceManager::getTotalCount() const
{
    return static_cast<int>(inventory.size());
}

bool ResourceManager::isEmpty() const
{
    return inventory.empty();
}

vector<string> ResourceManager::serializeAll() const
{
    vector<string> lines;
    for (const Resource *r : inventory)
    {
        lines.push_back(r->serialize());
    }
    return lines;
}

void ResourceManager::loadFromLines(const vector<string> &lines)
{
    for (const string &line : lines)
    {
        if (line.empty() || line[0] == '#')
            continue;
        vector<string> fields;
        stringstream ss(line);
        string token;
        while (getline(ss, token, '|'))
        {
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
                inventory.push_back(new LabHardware(id, name, price, stock, warranty, mfr, serial));
            }
            else if (tag == "CAFE" && fields.size() >= 8)
            {
                string expiry = fields[5];
                bool refrigerated = (fields[6] == "1");
                int calories = stoi(fields[7]);
                inventory.push_back(new CafeteriaPerishable(id, name, price, stock, expiry, refrigerated, calories));
            }
            else if (tag == "BOOK" && fields.size() >= 8)
            {
                string isbn = fields[5];
                string author = fields[6];
                int edition = stoi(fields[7]);
                inventory.push_back(new BookstoreMedia(id, name, price, stock, isbn, author, edition));
            }
        }
        catch (const exception &e)
        {
            cerr << "[ResourceManager] Skipping malformed line: " << e.what() << "\n";
        }
    }
}