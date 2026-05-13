#pragma once
#include "PaymentMethod.h"
#include "CampusExceptions.h"
#include <string>
using namespace std;

class CardPayment : public PaymentMethod {
private:
    string cardNumber;
    string cardHolder;
    string maskedNumber() const;
    static void validateCardNumber(const string& number);
public:
    CardPayment(const string& cardNumber, const string& cardHolder);
    void processPayment(double amount) override;
    string getPaymentType() const override { return "Card"; }
    string toLogString() const override;
};
