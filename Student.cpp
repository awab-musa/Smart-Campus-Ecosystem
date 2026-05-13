#include "Student.h"
#include <sstream>

Student::Student()
    : User(), major(""), yearLevel(1) {}

Student::Student(const string &name, const string &campusID,
                 const string &major, int yearLevel)
    : User(name, campusID), major(major), yearLevel(yearLevel) {}

string Student::getMajor() const { return major; }
int Student::getYearLevel() const { return yearLevel; }

void Student::setMajor(const string &m) { major = m; }
void Student::setYearLevel(int y) { yearLevel = y; }

double Student::getDiscount() const { return 0.0; }
string Student::getRole() const { return "Student"; }
string Student::getTypeTag() const { return "STUDENT"; }

void Student::displayProfile() const
{
    cout << *this;
    cout << "  Major      : " << major << "\n"
         << "  Year Level : " << yearLevel << "\n";
}

string Student::serialize() const
{
    ostringstream oss;
    oss << getTypeTag() << "|" << name << "|"
        << campusID << "|" << major << "|" << yearLevel;
    return oss.str();
}