#pragma once
#include "ResourceManager.h"
#include "FileManager.h"
#include "Student.h"
#include "Staff.h"
#include "Order.h"
#include "CashPayment.h"
#include "CardPayment.h"
#include "Pickup.h"
#include "DormDelivery.h"
#include "CampusExceptions.h"
#include <vector>
#include <iostream>
#include <limits>
using namespace std;

class CampusSystem
{
private:
    ResourceManager resourceManager;
    FileManager fileManager;
    vector<User *> users;

    void menuInventory();
    void menuOrders();
    void menuReports();

    User *selectUser();
    User *findUserById(const string &id);
    void loadUsersFromFile();
    void saveUsersToFile();

    int getIntInput(const string &prompt);
    double getDoubleInput(const string &prompt);
    string getStringInput(const string &prompt);
    void clearInputBuffer();
    void printHeader(const string &title) const;

public:
    CampusSystem();
    ~CampusSystem();
    void run();
};