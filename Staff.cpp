#include "Staff.h"
#include <sstream>

Staff::Staff()
    : User(), department(""), role("") {}

Staff::Staff(const string &name, const string &campusID,
             const string &department, const string &role)
    : User(name, campusID), department(department), role(role) {}

string Staff::getDepartment() const { return department; }
string Staff::getRole() const { return role; }

void Staff::setDepartment(const string &d) { department = d; }
void Staff::setStaffRole(const string &r) { role = r; }

double Staff::getDiscount() const { return 0.10; }
string Staff::getTypeTag() const { return "STAFF"; }

void Staff::displayProfile() const
{
    cout << *this;
    cout << "  Department : " << department << "\n"
         << "  Staff Role : " << role << "\n";
}

string Staff::serialize() const
{
    ostringstream oss;
    oss << getTypeTag() << "|" << name << "|"
        << campusID << "|" << department << "|" << role;
    return oss.str();
}