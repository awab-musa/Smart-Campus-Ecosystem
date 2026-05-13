#include "User.h"
#include "Order.h"
#include <iomanip>

User::User() : name(""), campusID("") {}

User::User(const string &n, const string &id)
    : name(n), campusID(id) {}

string User::getName() const { return name; }
string User::getCampusID() const { return campusID; }

void User::setName(const string &n) { name = n; }
void User::setCampusID(const string &id) { campusID = id; }

void User::placeOrder(Order &order) const
{
    cout << "\n[Order] Order placed by " << getRole()
         << " " << name << " (ID: " << campusID << ")\n";
}

string User::getProfile() const
{
    return getRole() + " | " + name + " | ID: " + campusID;
}

ostream &operator<<(ostream &os, const User &u)
{
    os << "+-----------------------------------------+\n"
       << "|  User Profile                           |\n"
       << "+-----------------------------------------+\n"
       << "|  Role     : " << left << setw(28) << u.getRole() << "|\n"
       << "|  Name     : " << left << setw(28) << u.name << "|\n"
       << "|  Campus ID: " << left << setw(28) << u.campusID << "|\n"
       << "|  Discount : " << left << setw(27)
       << (to_string((int)(u.getDiscount() * 100)) + "%") << "|\n"
       << "+-----------------------------------------+\n";
    return os;
}