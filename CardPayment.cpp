#include "CardPayment.h"
#include "CampusExceptions.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

void CardPayment::validateCardNumber(const string &number)
{
    if (number.length() != 16)
        throw InvalidCardException("Card number must be exactly 16 digits.");
    for (char c : number)
        if (!isdigit(c))
            throw InvalidCardException("Card number must contain only digits.");
}

CardPayment::CardPayment(const string &cardNumber, const string &cardHolder)
    : cardNumber(cardNumber), cardHolder(cardHolder)
{
    validateCardNumber(cardNumber);
}

string CardPayment::maskedNumber() const
{
    return "************" + cardNumber.substr(12);
}

void CardPayment::processPayment(double amount)
{
    cout << fixed << setprecision(2);
    cout << "Card payment of EGP " << amount << " processed.\n";
    cout << "Card: " << maskedNumber() << " | Holder: " << cardHolder << "\n";
}

string CardPayment::toLogString() const
{
    ostringstream oss;
    oss << "CARD|card=" << maskedNumber() << "|holder=" << cardHolder;
    return oss.str();
}