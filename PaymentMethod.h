#pragma once
#include <string>
#include <iostream>
using namespace std;

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual void processPayment(double amount) = 0;
    virtual string getPaymentType() const = 0;
    virtual string toLogString() const = 0;
    friend ostream& operator<<(ostream& os, const PaymentMethod& pm);
};
