#include "LabHardware.h"
#include <iomanip>
#include <sstream>

LabHardware::LabHardware()
    : Resource(), warrantyMonths(0), manufacturer(""), serialNumber("") {}

LabHardware::LabHardware(const string &id, const string &name,
                         double price, int stock,
                         int warranty, const string &mfr,
                         const string &serial)
    : Resource(id, name, price, stock),
      warrantyMonths(warranty), manufacturer(mfr), serialNumber(serial) {}

int LabHardware::getWarrantyMonths() const { return warrantyMonths; }
string LabHardware::getManufacturer() const { return manufacturer; }
string LabHardware::getSerialNumber() const { return serialNumber; }

void LabHardware::setWarrantyMonths(int w) { warrantyMonths = w; }
void LabHardware::setManufacturer(const string &m) { manufacturer = m; }
void LabHardware::setSerialNumber(const string &s) { serialNumber = s; }

string LabHardware::getWarrantyInfo() const
{
    return to_string(warrantyMonths) + " months warranty by " + manufacturer;
}

bool LabHardware::isUnderWarranty() const
{
    return warrantyMonths > 0;
}

void LabHardware::displayInfo() const
{
    cout << *this;
    cout << "  Manufacturer : " << manufacturer << "\n"
         << "  Serial No.   : " << serialNumber << "\n"
         << "  Warranty     : " << getWarrantyInfo() << "\n";
}

string LabHardware::getCategory() const
{
    return "Lab Hardware";
}

string LabHardware::getTypeTag() const
{
    return "LAB";
}

string LabHardware::serialize() const
{
    ostringstream oss;
    oss << getTypeTag() << "|"
        << resourceID << "|"
        << name << "|"
        << fixed << setprecision(2) << price << "|"
        << stock << "|"
        << warrantyMonths << "|"
        << manufacturer << "|"
        << serialNumber;
    return oss.str();
}