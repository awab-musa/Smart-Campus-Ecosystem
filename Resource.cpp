#include "Resource.h"
#include "CampusExceptions.h"
#include <iomanip>

Resource::Resource()
    : resourceID(""), name(""), price(0.0), stock(0) {}

Resource::Resource(const string &id, const string &n, double p, int s)
    : resourceID(id), name(n), price(p), stock(s) {}

string Resource::getResourceID() const { return resourceID; }
string Resource::getName() const { return name; }
double Resource::getPrice() const { return price; }
int Resource::getStock() const { return stock; }

void Resource::setPrice(double p) { price = p; }
void Resource::setStock(int s) { stock = s; }

void Resource::restock(int qty)
{
    if (qty <= 0)
    {
        throw invalid_argument("Restock quantity must be positive.");
    }
    stock += qty;
    cout << "[Restock] " << name << " — new stock: " << stock << endl;
}

void Resource::purchase(int qty)
{
    if (qty <= 0)
    {
        throw invalid_argument("Purchase quantity must be positive.");
    }
    if (qty > stock)
    {
        throw StockLimitException(name, stock, qty);
    }
    stock -= qty;
}

bool Resource::compareCost(const Resource *other) const
{
    return price > other->price;
}

bool Resource::operator>(const Resource &other) const
{
    return price > other.price;
}

bool Resource::operator<(const Resource &other) const
{
    return price < other.price;
}

ostream &operator<<(ostream &os, const Resource &r)
{
    os << "┌─────────────────────────────────────┐\n"
       << "│  Resource Report                    │\n"
       << "├─────────────────────────────────────┤\n"
       << "│  ID       : " << left << setw(24) << r.resourceID << "│\n"
       << "│  Name     : " << left << setw(24) << r.name << "│\n"
       << "│  Category : " << left << setw(24) << r.getCategory() << "│\n"
       << "│  Price    : EGP " << fixed << setprecision(2)
       << setw(20) << r.price << "│\n"
       << "│  Stock    : " << left << setw(24) << r.stock << "│\n"
       << "└─────────────────────────────────────┘\n";
    return os;
}