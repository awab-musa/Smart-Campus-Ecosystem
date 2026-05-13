#ifndef LAB_HARDWARE_H
#define LAB_HARDWARE_H

#include "Resource.h"

class LabHardware : public Resource
{
private:
    int warrantyMonths;
    string manufacturer;
    string serialNumber;

public:
    static LabHardware* fromString(const string& line);
    LabHardware();
    LabHardware(const string &id, const string &name, double price, int stock,
                int warrantyMonths, const string &manufacturer,
                const string &serialNumber);

    int getWarrantyMonths() const;
    string getManufacturer() const;
    string getSerialNumber() const;
    void setWarrantyMonths(int w);
    void setManufacturer(const string &m);
    void setSerialNumber(const string &s);

    string getWarrantyInfo() const;
    bool isUnderWarranty() const;

    void displayInfo() const override;
    string getCategory() const override;
    string serialize() const override;
    string getTypeTag() const override;
};

#endif