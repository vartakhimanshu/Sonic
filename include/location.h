
#pragma once

#include <stdexcept>

using namespace std;

template <class T>
class Location {
    T x;
    T y;
    T z;
public:
    Location () : x(0), y(0), z(0) {}
    Location (T x0, T y0, T z0) : x(x0), y(y0), z(z0) {}
    Location<T>& operator= (const Location<T>&);
	Location<T>& operator+=(const Location<T>&);
    bool operator< (const Location<T>&) const;
    T getX (void) const;
    T getY (void) const;
    T getZ (void) const;
};

template <class T>
Location<T>& Location<T>::operator=(const Location<T>& rhs)
{
    x = (rhs.x);
    y = (rhs.y);
    z = (rhs.z);
    return *this;
}

template <class T>
Location<T>& Location<T>::operator+=(const Location<T>& rhs)
{
    x = x + rhs.x;
    y = y + rhs.y;
    z = z + rhs.z;
    return *this;
}

template <class T>
Location<T> operator+(Location<T> lhs, const Location<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
bool Location<T>::operator< (const Location<T>& rhs) const
{
    if (x == rhs.x){
        if (y == rhs.y){
            return z < rhs.z;
        }return y < rhs.y;
    }return x < rhs.x;
}

template <class T>
std::ostream& operator<< (std::ostream& os, const Location<T>& obj)
{
    os << obj.getX() <<","<< obj.getY() <<","<< obj.getZ();
    return os;
}

template <class T>
T Location<T>::getX (void) const
{
    return this->x;
}

template <class T>
T Location<T>::getY (void) const
{
    return this->y;
}

template <class T>
T Location<T>::getZ (void) const
{
    return this->z;
}
