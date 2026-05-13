#include "Pickup.h"

Pickup::Pickup() : DeliveryMethod("Pickup") {}

double Pickup::getCost() const { return 0.0; }
string Pickup::getDescription() const { return "Campus Pickup — Free"; }
string Pickup::getTypeTag() const { return "PICKUP"; }