#ifndef DORM_DELIVERY_H
#define DORM_DELIVERY_H

#include "DeliveryMethod.h"

constexpr double DELIVERY_SURCHARGE = 2.50;

class DormDelivery : public DeliveryMethod
{
private:
    double surcharge;
    string dormAddress;
public:
    DormDelivery();
    explicit DormDelivery(const string &dormAddress);

    double getSurcharge() const;
    string getDormAddress() const;
    void setDormAddress(const string &addr);

    double getCost() const override;
    string getDescription() const override;
    string getTypeTag() const override;
};

#endif