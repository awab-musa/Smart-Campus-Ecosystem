#include "DeliveryMethod.h"
#include <iomanip>

DeliveryMethod::DeliveryMethod()
    : methodName("Unknown") {}

DeliveryMethod::DeliveryMethod(const string &name)
    : methodName(name) {}

string DeliveryMethod::getMethodName() const { return methodName; }

ostream &operator<<(ostream &os, const DeliveryMethod &d)
{
    os << "  Delivery   : " << d.getDescription()
       << "  (EGP " << fixed << setprecision(2) << d.getCost() << ")\n";
    return os;
}