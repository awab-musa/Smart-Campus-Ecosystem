#include "CashPayment.h"
#include "CampusExceptions.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

CashPayment::CashPayment(double amountTendered)
    : amountTendered(amountTendered) {}

void CashPayment::processPayment(double amount) {
    if (amountTendered < amount)
        throw CampusException("Insufficient cash tendered. Required: " +
                              to_string(amount) + ", Provided: " +
                              to_string(amountTendered));
    cout << fixed << setprecision(2);
    cout << "Cash payment of EGP " << amount << " accepted.\n";
    cout << "Change returned: EGP " << (amountTendered - amount) << "\n";
}

string CashPayment::toLogString() const {
    ostringstream oss;
    oss << "CASH|tendered=" << fixed << setprecision(2) << amountTendered;
    return oss.str();
}
