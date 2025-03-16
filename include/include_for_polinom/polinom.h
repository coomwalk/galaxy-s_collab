#ifndef __POLINOM__
#define __POLINOM__

#include<iostream>
#include<string>
#include <cctype>
#include <sstream>
#include "monom.h"
#include "../include_for_list/list.h"

class Polynom
{
    List<Monom> polinoms;
public:
    Polynom() = default;
    Polynom(const string& s);
    Polynom(const Polynom& p);
    Polynom(Polynom&& p) noexcept;
    Polynom& operator=(Polynom&& p) noexcept;
    Polynom& operator=(const Polynom& other);
    Polynom operator*(Monom& m);
    Polynom operator*(double& oth);
    Polynom operator+(Polynom& other);
    Polynom operator-(Polynom& other);

    Polynom operator*(Polynom& other);
    // operatot == 
    void DelCoeffZero();
    ~Polynom() = default;
    
    friend ostream& operator<<(ostream& ostr, const Polynom& poli);
    friend istream& operator>>(istream& istr, Polynom& poli);
};
#endif


