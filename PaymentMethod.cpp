#include "PaymentMethod.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const PaymentMethod& pm) {
    os << pm.getPaymentType();
    return os;
}
