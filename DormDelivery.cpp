#include "DormDelivery.h"
#include <iomanip>
#include <sstream>

DormDelivery::DormDelivery()
    : DeliveryMethod("Dorm Delivery"),
      surcharge(DELIVERY_SURCHARGE),
      dormAddress("") {}

DormDelivery::DormDelivery(const string &addr)
    : DeliveryMethod("Dorm Delivery"),
      surcharge(DELIVERY_SURCHARGE),
      dormAddress(addr) {}

double DormDelivery::getSurcharge() const { return surcharge; }
string DormDelivery::getDormAddress() const { return dormAddress; }
void DormDelivery::setDormAddress(const string &addr) { dormAddress = addr; }

double DormDelivery::getCost() const { return surcharge; }

string DormDelivery::getDescription() const
{
    ostringstream oss;
    oss << "Dorm Delivery";
    if (!dormAddress.empty())
        oss << " -> " << dormAddress;
    oss << " — EGP " << fixed << setprecision(2) << surcharge;
    return oss.str();
}

string DormDelivery::getTypeTag() const { return "DORM"; }