#pragma once
#ifndef __Monom__
#define __Monom__

#include<iostream>
#include<string>
#include <cctype>
using namespace std;

class Monom
{
    double coeff;
    int pow_x;
    int pow_y;
    int pow_z;
public:
    Monom(double c, int px, int py, int pz);
    Monom(const string& s);

    int getPowX();
    int getPowY();
    int getPowZ();
    double getCoeff();

    Monom operator+(const Monom& m) const;

    Monom operator*(const Monom& other) const;

    bool operator==(const Monom& m) const;

    bool operator<(const Monom& m) const;

    friend ostream& operator<<(ostream& ostr, const Monom& m);
};
#endif
