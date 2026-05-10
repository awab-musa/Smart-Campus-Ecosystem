#include <iostream>
using namespace std;

class Resource;
class IComparable
{
public:
    virtual bool comparaCost(const Resource *other) const = 0;
    virtual ~IComparable() = default;
};
