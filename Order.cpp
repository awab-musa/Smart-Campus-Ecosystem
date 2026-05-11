#include "Order.h"
#include "User.h"
#include "CampusExceptions.h"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <stdexcept>

int Order::orderCounter = 1;

string Order::generateOrderID()
{
    ostringstream oss;
    oss << "ORD-" << setw(4) << setfill('0') << orderCounter++;
    return oss.str();
}

static string todayDate()
{
    time_t now = time(nullptr);
    tm *t = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    return string(buf);
}

Order::Order()
    : orderID(generateOrderID()),
      user(nullptr),
      delivery(nullptr),
      orderDate(todayDate()) {}

Order::Order(const User *u, DeliveryMethod *d)
    : orderID(generateOrderID()),
      user(u),
      delivery(d),
      orderDate(todayDate()) {}

Order::~Order() {}

void Order::addItem(Resource *resource, int quantity)
{
    if (!resource)
        throw invalid_argument("Cannot add null resource to order.");
    if (quantity <= 0)
        throw invalid_argument("Quantity must be a positive integer.");

    resource->purchase(quantity);

    for (auto &item : items)
    {
        if (item.getResource()->getResourceID() == resource->getResourceID())
        {
            item.setQuantity(item.getQuantity() + quantity);
            return;
        }
    }
    items.emplace_back(resource, quantity);
}

void Order::removeItem(const string &resourceID)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if (it->getResource()->getResourceID() == resourceID)
        {
            it->getResource()->restock(it->getQuantity());
            items.erase(it);
            return;
        }
    }
    cout << "[Order] Item with ID " << resourceID << " not found in order.\n";
}

bool Order::hasItems() const { return !items.empty(); }
int Order::itemCount() const { return static_cast<int>(items.size()); }

double Order::calcSubtotal() const
{
    double total = 0.0;
    for (const auto &item : items)
        total += item.getLineTotal();
    return total;
}

double Order::calcDiscount() const { return user ? calcSubtotal() * user->getDiscount() : 0.0; }
double Order::calcDeliveryCost() const { return delivery ? delivery->getCost() : 0.0; }
double Order::calcTotal() const { return calcSubtotal() - calcDiscount() + calcDeliveryCost(); }

string Order::getOrderID() const { return orderID; }
const vector<OrderItem> &Order::getItems() const { return items; }
const User *Order::getUser() const { return user; }
DeliveryMethod *Order::getDelivery() const { return delivery; }
string Order::getOrderDate() const { return orderDate; }

void Order::displaySummary() const
{
    cout << orderID << " | "
         << (user ? user->getName() : "Unknown") << " | "
         << itemCount() << " item(s) | "
         << "Total: EGP " << fixed << setprecision(2) << calcTotal() << "\n";
}

void Order::displayReceipt() const
{
    cout << "\n+==========================================+\n";
    cout << "|        SMART CAMPUS RECEIPT              |\n";
    cout << "+==========================================+\n";
    cout << "  Order ID  : " << orderID << "\n";
    cout << "  Date      : " << orderDate << "\n";
    if (user)
    {
        cout << "  Customer  : " << user->getName() << " (" << user->getRole() << ")\n";
        cout << "  Campus ID : " << user->getCampusID() << "\n";
    }
    cout << "------------------------------------------\n";
    cout << "  ITEMS\n";
    for (const auto &item : items)
        cout << item;
    cout << "------------------------------------------\n";
    cout << "  Subtotal  : EGP " << fixed << setprecision(2) << calcSubtotal() << "\n";
    if (user && user->getDiscount() > 0.0)
    {
        cout << "  Discount  : -EGP " << fixed << setprecision(2) << calcDiscount()
             << "  (" << (int)(user->getDiscount() * 100) << "% staff)\n";
    }
    if (delivery)
        cout << *delivery;
    cout << "==========================================\n";
    cout << "  TOTAL     : EGP " << fixed << setprecision(2) << calcTotal() << "\n";
    cout << "+==========================================+\n\n";
}

string Order::serialize() const
{
    ostringstream oss;
    oss << orderID << "|"
        << (user ? user->getCampusID() : "UNKNOWN") << "|"
        << (user ? user->getRole() : "UNKNOWN") << "|";
    for (size_t i = 0; i < items.size(); ++i)
    {
        oss << items[i].getResource()->getResourceID() << ":" << items[i].getQuantity();
        if (i + 1 < items.size())
            oss << ",";
    }
    oss << "|" << (delivery ? delivery->getTypeTag() : "NONE")
        << "|" << orderDate
        << "|" << fixed << setprecision(2) << calcTotal();
    return oss.str();
}

ostream &operator<<(ostream &os, const Order &o)
{
    o.displayReceipt();
    return os;
}