#include "OrderItem.h"
#include <iomanip>
#include <stdexcept>

OrderItem::OrderItem()
    : resource(nullptr), quantity(0) {}

OrderItem::OrderItem(Resource *r, int qty)
    : resource(r), quantity(qty)
{
    if (!r)
        throw invalid_argument("OrderItem: resource cannot be null.");
    if (qty <= 0)
        throw invalid_argument("OrderItem: quantity must be positive.");
}

Resource *OrderItem::getResource() const { return resource; }
int OrderItem::getQuantity() const { return quantity; }

void OrderItem::setQuantity(int q)
{
    if (q <= 0)
        throw invalid_argument("Quantity must be positive.");
    quantity = q;
}

double OrderItem::getLineTotal() const
{
    return resource->getPrice() * quantity;
}

void OrderItem::display() const
{
    cout << *this;
}

ostream &operator<<(ostream &os, const OrderItem &item)
{
    os << "  " << left
       << setw(30) << item.resource->getName()
       << " x" << setw(4) << item.quantity
       << "  EGP " << fixed << setprecision(2)
       << item.getLineTotal() << "\n";
    return os;
}