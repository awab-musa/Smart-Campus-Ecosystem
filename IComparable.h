#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H

class Resource;

class IComparable
{
public:
    virtual bool compareCost(const Resource *other) const = 0;
    virtual ~IComparable() = default;
};

#endif