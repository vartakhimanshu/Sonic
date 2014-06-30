//========================================================
// velocity.h
// Defines class 'Velocity' in 3 dimensions
// Author: Avinash Repaka
//========================================================

#pragma once

#include <stdexcept>

using namespace std;

template <class T>
class Velocity {
    T dx;
    T dy;
    T dz;
public:
    Velocity () : dx(0), dy(0), dz(0) {}
    Velocity (T dx0, T dy0, T dz0) : dx(dx0), dy(dy0), dz(dz0) {}
    Velocity<T>& operator= (const Velocity<T>&);
	Velocity<T>& operator+=(const Velocity<T>&);
    bool operator< (const Velocity<T>&) const;
    T getdX (void) const;
    T getdY (void) const;
    T getdZ (void) const;
};

template <class T>
Velocity<T>& Velocity<T>::operator=(const Velocity<T>& rhs)
{
    dx = (rhs.dx);
    dy = (rhs.dy);
    dz = (rhs.dz);
    return *this;
}

template <class T>
Velocity<T>& Velocity<T>::operator+=(const Velocity<T>& rhs)
{
    dx = dx + rhs.dx;
    dy = dy + rhs.dy;
    dz = dz + rhs.dz;
    return *this;
}

template <class T>
Velocity<T> operator+(Velocity<T> lhs, const Velocity<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
bool Velocity<T>::operator< (const Velocity<T>& rhs) const
{
    if (dx == rhs.dx){
        if (dy == rhs.dy){
            return dz < rhs.dz;
        }return dy < rhs.dy;
    }return dx < rhs.dx;
}

template <class T>
std::ostream& operator<< (std::ostream& os, const Velocity<T>& obj)
{
    os << obj.getdX() <<","<< obj.getdY() <<","<< obj.getdZ();
    return os;
}

template <class T>
T Velocity<T>::getdX (void) const
{
    return this->dx;
}

template <class T>
T Velocity<T>::getdY (void) const
{
    return this->dy;
}

template <class T>
T Velocity<T>::getdZ (void) const
{
    return this->dz;
}
