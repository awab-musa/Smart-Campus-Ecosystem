#ifndef STAFF_H
#define STAFF_H

#include "User.h"

class Staff : public User
{
private:
    string department;
    string role;

public:
    Staff();
    Staff(const string &name, const string &campusID,
          const string &department, const string &role);

    string getDepartment() const;
    string getRole() const override;
    void setDepartment(const string &d);
    void setStaffRole(const string &r);

    double getDiscount() const override;
    string getTypeTag() const override;
    void displayProfile() const override;
    string serialize() const override;
};

#endif