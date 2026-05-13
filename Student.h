#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User
{
private:
    string major;
    int yearLevel;

public:
    Student();
    Student(const string &name, const string &campusID,
            const string &major, int yearLevel);

    string getMajor() const;
    int getYearLevel() const;
    void setMajor(const string &m);
    void setYearLevel(int y);

    double getDiscount() const override;
    string getRole() const override;
    string getTypeTag() const override;
    void displayProfile() const override;
    string serialize() const override;
};

#endif