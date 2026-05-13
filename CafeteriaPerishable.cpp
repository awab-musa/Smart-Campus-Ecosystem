#include "CafeteriaPerishable.h"
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>

CafeteriaPerishable::CafeteriaPerishable()
    : Resource(), expiryDate(""), isRefrigerated(false), calories(0) {}

CafeteriaPerishable::CafeteriaPerishable(const string &id, const string &name,
                                         double price, int stock,
                                         const string &expiry,
                                         bool refrigerated, int cals)
    : Resource(id, name, price, stock),
      expiryDate(expiry), isRefrigerated(refrigerated), calories(cals) {}

string CafeteriaPerishable::getExpiryDate() const { return expiryDate; }
bool CafeteriaPerishable::getIsRefrigerated() const { return isRefrigerated; }
int CafeteriaPerishable::getCalories() const { return calories; }

void CafeteriaPerishable::setExpiryDate(const string &d) { expiryDate = d; }
void CafeteriaPerishable::setIsRefrigerated(bool r) { isRefrigerated = r; }
void CafeteriaPerishable::setCalories(int c) { calories = c; }

bool CafeteriaPerishable::isExpired() const
{
    time_t now = time(nullptr);
    tm *t = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    string today(buf);
    return expiryDate < today;
}

string CafeteriaPerishable::freshStatus() const
{
    return isExpired() ? "EXPIRED" : "Fresh";
}

void CafeteriaPerishable::displayInfo() const
{
    cout << *this;
    cout << "  Expiry Date  : " << expiryDate << "\n"
         << "  Status       : " << freshStatus() << "\n"
         << "  Refrigerated : " << (isRefrigerated ? "Yes" : "No") << "\n"
         << "  Calories     : " << calories << " kcal" << "\n";
}

string CafeteriaPerishable::getCategory() const
{
    return "Cafeteria Perishable";
}

string CafeteriaPerishable::getTypeTag() const
{
    return "CAFE";
}

string CafeteriaPerishable::serialize() const
{
    ostringstream oss;
    oss << getTypeTag() << "|"
        << resourceID << "|"
        << name << "|"
        << fixed << setprecision(2) << price << "|"
        << stock << "|"
        << expiryDate << "|"
        << (isRefrigerated ? "1" : "0") << "|"
        << calories;
    return oss.str();
}
CafeteriaPerishable* CafeteriaPerishable::fromString(const string& line)
{
    stringstream ss(line);
    string token;
    vector<string> tokens;
    while (getline(ss, token, '|'))
        tokens.push_back(token);
    if (tokens.size() < 8)
        throw invalid_argument("Invalid CafeteriaPerishable data: " + line);
    string id     = tokens[1];
    string name   = tokens[2];
    double price  = stod(tokens[3]);
    int stock     = stoi(tokens[4]);
    string expiry = tokens[5];
    bool refrig   = tokens[6] == "1";
    int calories  = stoi(tokens[7]);
    return new CafeteriaPerishable(id, name, price, stock, expiry, refrig, calories);
}
