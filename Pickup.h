#ifndef PICKUP_H
#define PICKUP_H

#include "DeliveryMethod.h"

class Pickup : public DeliveryMethod
{
public:
    Pickup();

    double getCost() const override;
    string getDescription() const override;
    string getTypeTag() const override;
};

#endif