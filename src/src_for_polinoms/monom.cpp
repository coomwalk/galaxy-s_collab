#include<iostream>
#include<string>
#include <cctype>
#include "monom.h"

Monom::Monom() : coeff(0), pow_x(0), pow_y(0), pow_z(0) {}

Monom::Monom(const Monom& m) noexcept : coeff(m.coeff), pow_x(m.pow_x), pow_y(m.pow_y), pow_z(m.pow_z) {}

Monom::Monom(double c, int px, int py, int pz) noexcept : coeff(c), pow_x(px), pow_y(py), pow_z(pz) {}

Monom::Monom(const string& s)
{
    std::string::const_iterator it = s.begin();
    std::string sub;

    for (it; *it != 'x'; ++it)
    {
        sub.push_back(*it);
    }
    ++it;
    
    coeff = std::stod(sub);
    sub.clear();

    for (it; *it != 'y'; ++it)
    {
        sub.push_back(*it);
    }
    ++it;
    pow_x = std::stoi(sub);
    sub.clear();

    for (it; *it != 'z'; ++it)
    {
        sub.push_back(*it);
    }
    ++it;
    pow_y = std::stoi(sub);
    sub.clear();

    for (it; it != s.end(); ++it)
    {
        sub.push_back(*it);
    }
    pow_z = std::stoi(sub);
}

Monom& Monom::operator=(const Monom& m) noexcept
{
    if (*this == m)
    {
        return *this;
    }

    coeff = m.coeff;
    pow_x = m.pow_x;
    pow_y = m.pow_y;
    pow_z = m.pow_z;

    return *this;
}

Monom Monom::operator+(const Monom& m)
{
    if ((pow_x == m.pow_x) && (pow_y == m.pow_y) && (pow_z == m.pow_z))
    {
        return Monom(coeff + m.coeff, pow_x, pow_y, pow_z);
    }
    else
    {
        throw std::invalid_argument("Cannot add monomials with different pows");
    }
}

Monom Monom::operator-(const Monom& m)
{
    if ((pow_x == m.pow_x) && (pow_y == m.pow_y) && (pow_z == m.pow_z))
    {
        return Monom(coeff - m.coeff, pow_x, pow_y, pow_z);
    }
    else
    {
        throw std::invalid_argument("Cannot add monomials with different pows");
    }
}

Monom Monom::operator*(const double& oth) const noexcept
{
    if (oth == 0 || coeff == 0.0)
    {
        return Monom();
    }
    return Monom(coeff * oth, pow_x, pow_y, pow_z);
}

Monom Monom::operator*(const Monom& m) const noexcept
{
    if (coeff == 0 || m.coeff == 0)
    {
        return Monom();
    }

    return Monom(coeff * m.coeff, pow_x + m.pow_x, pow_y + m.pow_y, pow_z + m.pow_z);
}

bool Monom::operator==(const Monom& m) const noexcept
{
    return (coeff == m.coeff) && (pow_x == m.pow_x) && (pow_y == m.pow_y) && (pow_z == m.pow_z);
}

bool Monom::operator!=(const Monom& m) const noexcept
{
    return !(*this == m);
}

ostream& operator<<(ostream& ostr, const Monom& m)
{
    ostr << m.coeff;
    ostr << "x" << m.pow_x;
    ostr << "y" << m.pow_y;
    ostr << "z" << m.pow_z;
    return ostr;
}

bool Monom::EqPow(const Monom& m) const noexcept
{
    return (pow_x == m.pow_x) && (pow_y == m.pow_y) && (pow_z == m.pow_z);
}

double Monom::GetCoeff() const
{
    return coeff;
}