#pragma once
#ifndef __Polynom__
#define __Polynom__

#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include "monom.h"
#include "list.h"
using namespace std;

class Polynom
{
    List<Monom> p;

public:
    Polynom();
    Polynom(const string &s);
    void printPol();
    Polynom operator+(Polynom &other);
    Polynom operator*(Monom &m);
    Polynom operator*(Polynom &other);
    friend Polynom operator*(Monom &m, Polynom &oth);
    // Polynom operator*(Monom& m, Polynom& p);
};
#endif
