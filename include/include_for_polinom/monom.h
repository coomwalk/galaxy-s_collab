#ifndef __MONOM__
#define __MONOM__

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

    Monom();
    Monom(const Monom& m) noexcept;
    Monom(double c, int px, int py, int pz) noexcept;
    Monom(const string& s);

    Monom& operator=(const Monom& m) noexcept;
    Monom operator+(const Monom& m);
    Monom operator-(const Monom& m);
    Monom operator*(const double& oth) const noexcept;
    Monom operator*(const Monom& other) const noexcept;
    
    bool operator==(const Monom& m) const noexcept;
    bool operator!=(const Monom& m) const noexcept;

    bool EqPow(const Monom& m) const noexcept;
    double GetCoeff() const;

    friend ostream& operator<<(ostream& ostr, const Monom& m);
};
#endif
