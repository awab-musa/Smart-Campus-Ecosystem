#include "CampusSystem.h"
#include "LabHardware.h"
#include "CafeteriaPerishable.h"
#include "BookstoreMedia.h"
#include "PaymentMethod.h"
#include "CashPayment.h"
#include "CardPayment.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <string>

using namespace std;

CampusSystem::CampusSystem()
    : fileManager("inventory.txt", "transactions.txt")
{
    printHeader("Smart Campus Ecosystem - Loading Data");
    try
    {
        fileManager.loadInventory(resourceManager);
    }
    catch (const FileNotFoundException &e)
    {
        cout << "[Warning] " << e.what() << " Starting with empty inventory.\n";
    }
    try
    {
        loadUsersFromFile();
    }
    catch (const FileNotFoundException &e)
    {
        cout << "[Warning] " << e.what() << " No users loaded. You can add users from the menu.\n";
    }
}

CampusSystem::~CampusSystem()
{
    try
    {
        fileManager.saveInventory(resourceManager);
        saveUsersToFile();
    }
    catch (const CampusException &e)
    {
        cerr << "[Save Error] " << e.what() << "\n";
    }
    for (User *u : users)
        delete u;
    users.clear();
}

void CampusSystem::run()
{
    int choice = -1;
    do
    {
        printHeader("Main Menu");
        cout << "1. Resource & Inventory Management\n";
        cout << "2. Place an Order\n";
        cout << "3. Reports & Analytics\n";
        cout << "4. Manage Users\n";
        cout << "0. Exit & Save\n";
        cout << string(50, '-') << "\n";
        choice = getIntInput("Select an option: ");
        switch (choice)
        {
        case 1:
            menuInventory();
            break;
        case 2:
            menuOrders();
            break;
        case 3:
            menuReports();
            break;
        case 4:
        {
            printHeader("User Management");
            cout << "1. Add Student\n";
            cout << "2. Add Staff\n";
            cout << "3. View Users\n";
            cout << "0. Back\n";
            int uc = getIntInput("Select: ");
            if (uc == 1)
            {
                string name = getStringInput("Student name: ");
                string id = getStringInput("Campus ID: ");
                string major = getStringInput("Major: ");
                int year = getIntInput("Year Level: ");
                users.push_back(new Student(name, id, major, year));
                cout << "Student added successfully.\n";
            }
            else if (uc == 2)
            {
                string name = getStringInput("Staff name: ");
                string id = getStringInput("Campus ID: ");
                string dept = getStringInput("Department: ");
                string role = getStringInput("Role: ");
                users.push_back(new Staff(name, id, dept, role));
                cout << "Staff member added successfully.\n";
            }
            else if (uc == 3)
            {
                if (users.empty())
                {
                    cout << "No users registered.\n";
                    break;
                }
                cout << "\n=== Registered Users ===\n";
                for (const auto &u : users)
                    cout << *u << "\n";
                cout << "\n";
            }
            else if (uc == 0)
            {
                cout << "Returning to main menu...\n";
            }
            else
            {
                cout << "Invalid option.\n";
            }
            break;
        }
        case 0:
            cout << "Saving data and exiting...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);
}

void CampusSystem::menuInventory()
{
    printHeader("Resource & Inventory Management");
    cout << "1. View all resources\n";
    cout << "2. Add Lab Hardware\n";
    cout << "3. Add Cafeteria Perishable\n";
    cout << "4. Add Bookstore Media\n";
    cout << "5. Restock a Resource\n";
    cout << "6. Remove a Resource\n";
    cout << "7. Compare Two Resources (cost Burden)\n";
    cout << "0. Back to Main Menu\n";
    int choice = getIntInput("Select: ");
    switch (choice)
    {
    case 1:
        resourceManager.listAll();
        break;
    case 2:
    {
        string id = getStringInput("ID: ");
        string name = getStringInput("Name: ");
        double price = getDoubleInput("Price: ");
        int stock = getIntInput("Stock: ");
        int warranty = getIntInput("Warranty (months): ");
        string mfr = getStringInput("Manufacturer: ");
        string serial = getStringInput("Serial Number: ");
        try
        {
            resourceManager.addResource(new LabHardware(id, name, price, stock, warranty, mfr, serial));
            cout << "Lab Hardware added successfully.\n";
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
        break;
    }
    case 3:
    {
        string id = getStringInput("ID: ");
        string name = getStringInput("Name: ");
        double price = getDoubleInput("Price: ");
        int stock = getIntInput("Stock: ");
        string expiry = getStringInput("Expiry Date (YYYY-MM-DD): ");
        int refrig = getIntInput("Refrigerated? (1=Yes, 0=No): ");
        int calories = getIntInput("Calories: ");
        try
        {
            resourceManager.addResource(new CafeteriaPerishable(id, name, price, stock, expiry, refrig, calories));
            cout << "Cafeteria Perishable added successfully.\n";
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
        break;
    }
    case 4:
    {
        string id = getStringInput("ID: ");
        string name = getStringInput("Name: ");
        double price = getDoubleInput("Price: ");
        int stock = getIntInput("Stock: ");
        string isbn = getStringInput("ISBN: ");
        string author = getStringInput("Author: ");
        int edition = getIntInput("Edition: ");
        try
        {
            resourceManager.addResource(new BookstoreMedia(id, name, price, stock, isbn, author, edition));
            cout << "Bookstore Media added successfully.\n";
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
        break;
    }
    case 5:
    {
        string id = getStringInput("Resource ID to restock: ");
        int amount = getIntInput("Amount to add: ");
        try
        {
            Resource *r = resourceManager.searchByID(id);
            if (!r)
                throw ResourceNotFoundException(id);
            r->restock(amount);
            fileManager.saveInventory(resourceManager);
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
        break;
    }
    case 6:
    {
        string id = getStringInput("Resource ID to remove: ");
        try
        {
            resourceManager.removeResource(id);
            cout << "Resource removed successfully.\n";
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
        break;
    }
    case 7:
    {
        string id1 = getStringInput("First Resource ID: ");
        string id2 = getStringInput("Second Resource ID: ");
        try
        {
            resourceManager.compareTwoResources(id1, id2);
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
        break;
    }
    case 0:
        break;
    default:
        cout << "Invalid option.\n";
    }
}

void CampusSystem::menuOrders()
{
    printHeader("Place an Order");
    if (users.empty())
    {
        cout << "No users registered. Please add users before placing orders.\n";
        return;
    }
    if (resourceManager.getInventory().empty())
    {
        cout << "No resources available. Please add resources before placing orders.\n";
        return;
    }
    User *user = selectUser();
    if (!user)
        return;

    cout << "\nDelivery method:\n";
    cout << "1. Pickup\n";
    cout << "2. Dorm Delivery\n";
    int dm = getIntInput("Select: ");
    DeliveryMethod *delivery = nullptr;
    if (dm == 1)
    {
        delivery = new Pickup();
    }
    else
    {
        string addr = getStringInput("Enter dorm address: ");
        delivery = new DormDelivery(addr);
    }
    Order *order = new Order(user, delivery);
    bool addingItems = true;
    while (addingItems)
    {
        resourceManager.listAll();
        string rid = getStringInput("Enter Resource ID to add (0 to finish): ");
        if (rid == "0")
        {
            addingItems = false;
            break;
        }
        int qty = getIntInput("Quantity: ");
        try
        {
            Resource *r = resourceManager.searchByID(rid);
            if (!r)
                throw ResourceNotFoundException(rid);
            order->addItem(r, qty);
            cout << "Item added to order.\n";
        }
        catch (const InsufficientStockException &e)
        {
            cout << "[Stock Error] " << e.what() << "\n";
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
    }
    order->displayReceipt();
    cout << "\nPayment method:\n";
    cout << "1. Cash\n";
    cout << "2. Card\n";
    int pm = getIntInput("Select: ");
    PaymentMethod *payment = nullptr;
    bool paymentSuccess = false;
    if (pm == 1)
    {
        double tendered = getDoubleInput("Enter cash amount tendered: ");
        payment = new CashPayment(tendered);
    }
    else
    {
        bool validCard = false;
        while (!validCard)
        {
            try
            {
                string cardNum = getStringInput("Enter 16-digit card number: ");
                string holder = getStringInput("Enter cardholder name: ");
                payment = new CardPayment(cardNum, holder);
                validCard = true;
            }
            catch (const InvalidCardException &e)
            {
                cout << "[Card Error] " << e.what() << "\nPlease try again.\n";
            }
        }
    }
    try
    {
        payment->processPayment(order->calcTotal());
        paymentSuccess = true;
    }
    catch (const CampusException &e)
    {
        cout << "[Payment Error] " << e.what() << "\n";
    }
    if (paymentSuccess)
    {
        string logLine = order->serialize() + "|" + payment->toLogString();
        try
        {
            fileManager.logTransaction(logLine);
            fileManager.saveInventory(resourceManager);
            cout << "Transaction logged successfully.\n";
        }
        catch (const CampusException &e)
        {
            cout << "[Logging Error] " << e.what() << "\n";
        }
    }
    delete payment;
    delete order;
}

void CampusSystem::menuReports()
{
    printHeader("Reports & Analytics");
    cout << "1. Full Inventory Report\n";
    cout << "2. Search Resource by ID\n";
    cout << "0. Back\n";
    int choice = getIntInput("Select: ");
    switch (choice)
    {
    case 1:
        resourceManager.listAll();
        break;
    case 2:
    {
        string id = getStringInput("Resource ID: ");
        try
        {
            resourceManager.generateReport(id);
        }
        catch (const CampusException &e)
        {
            cout << "[Error] " << e.what() << "\n";
        }
        break;
    }
    case 0:
        break;
    default:
        cout << "Invalid option.\n";
    }
}

User *CampusSystem::selectUser()
{
    cout << "\n=== Registered Users ===\n";
    for (size_t i = 0; i < users.size(); ++i)
        cout << " " << i + 1 << ". " << *users[i] << "\n";
    cout << "=======================\n";
    int idx = getIntInput("Select user number (0 to cancel): ");
    if (idx <= 0 || idx > (int)users.size())
        return nullptr;
    return users[idx - 1];
}

User *CampusSystem::findUserById(const string &id)
{
    for (auto *u : users)
        if (u->getCampusID() == id)
            return u;
    return nullptr;
}

void CampusSystem::loadUsersFromFile()
{
    vector<string> lines = fileManager.loadUsers("users.txt");
    for (const auto &line : lines)
    {
        size_t p1 = line.find('|');
        size_t p2 = line.rfind('|');
        if (p1 == string::npos || p2 == string::npos || p1 == p2)
            continue;
        string role = line.substr(0, p1);
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string campusID = line.substr(p2 + 1);
        if (role == "Student")
            users.push_back(new Student(name, campusID, "", 1));
        else if (role == "Staff")
            users.push_back(new Staff(name, campusID, "", ""));
    }
    cout << "[FileManager] " << users.size() << " users loaded from 'users.txt'.\n";
}

void CampusSystem::saveUsersToFile()
{
    vector<string> lines;
    for (auto *u : users)
        lines.push_back(u->getRole() + "|" + u->getName() + "|" + u->getCampusID());
    fileManager.saveUsers(lines, "users.txt");
}

void CampusSystem::clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int CampusSystem::getIntInput(const string &prompt)
{
    int val;
    while (true)
    {
        cout << prompt;
        if (cin >> val)
        {
            clearInputBuffer();
            return val;
        }
        else
        {
            cout << "Invalid input. Please enter a valid integer.\n";
            clearInputBuffer();
        }
    }
}

double CampusSystem::getDoubleInput(const string &prompt)
{
    double val;
    while (true)
    {
        cout << prompt;
        if (cin >> val)
        {
            clearInputBuffer();
            return val;
        }
        else
        {
            cout << "Invalid input. Please enter a valid number.\n";
            clearInputBuffer();
        }
    }
}

string CampusSystem::getStringInput(const string &prompt)
{
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}

void CampusSystem::printHeader(const string &title) const
{
    cout << "\n"
         << string(50, '=') << "\n";
    cout << "    " << title << "\n";
    cout << string(50, '=') << "\n";
}