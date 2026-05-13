#ifndef CAFETERIA_PERISHABLE_H
#define CAFETERIA_PERISHABLE_H
#include "Resource.h"
class CafeteriaPerishable : public Resource
{
private:
    string expiryDate;
    bool isRefrigerated;
    int calories;
public:
    CafeteriaPerishable();
    CafeteriaPerishable(const string &id, const string &name,
                        double price, int stock,
                        const string &expiryDate,
                        bool isRefrigerated, int calories);
    string getExpiryDate() const;
    bool getIsRefrigerated() const;
    int getCalories() const;
    void setExpiryDate(const string &d);
    void setIsRefrigerated(bool r);
    void setCalories(int c);
    bool isExpired() const;
    string freshStatus() const;
    void displayInfo() const override;
    string getCategory() const override;
    string serialize() const override;
    string getTypeTag() const override;
    static CafeteriaPerishable* fromString(const string& line);
};
#endif
