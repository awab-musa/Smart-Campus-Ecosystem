#pragma once
#include "PaymentMethod.h"
#include <string>
using namespace std;

class CashPayment : public PaymentMethod
{
private:
    double amountTendered;

public:
    explicit CashPayment(double amountTendered = 0.0);
    void processPayment(double amount) override;
    string getPaymentType() const override { return "Cash"; }
    string toLogString() const override;
    double getChange(double amount) const { return amountTendered - amount; }
};