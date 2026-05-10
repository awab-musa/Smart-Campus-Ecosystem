#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <vector>
#include <string>
#include "Resource.h"

using namespace std;

class ResourceManager
{
private:
    vector<Resource *> inventory;

public:
    ResourceManager();
    ~ResourceManager();

    void addResource(Resource *r);
    bool removeResource(const string &id);
    Resource *searchByID(const string &id) const;

    void generateReport(const string &id) const;
    void listAll() const;
    void listByCategory(const string &cat) const;

    Resource *getHigherCost(Resource *a, Resource *b) const;
    void compareTwoResources(const string &id1, const string &id2) const;

    const vector<Resource *> &getInventory() const;
    int getTotalCount() const;
    bool isEmpty() const;

    vector<string> serializeAll() const;
    void loadFromLines(const vector<string> &lines);
};

#endif