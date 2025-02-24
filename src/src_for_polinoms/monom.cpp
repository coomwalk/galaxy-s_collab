
#include<iostream>
#include<string>
#include <cctype>
#include "monom.h"
using namespace std;

Monom::Monom(double c, int px = 0, int py = 0, int pz = 0) : coeff(c), pow_x(px), pow_y(py), pow_z(pz) {}

Monom::Monom(const string& s) : coeff(0), pow_x(0), pow_y(0), pow_z(0) {   // Конструктор по строке ("3x1y2z1")
        size_t i = 0;
        while (i < s.length() && isdigit(s[i]))
        {
            coeff = coeff * 10 + (s[i] - '0');
            //coeff = coeff * 10 + s[i];
            i++;
        }
        while (i < s.length()) {
            char var = s[i++]; // Считываем переменную
            int pow = 0;
            if (i < s.length() && isdigit(s[i])) {

                while (i < s.length() && isdigit(s[i])) {
                    pow = pow * 10 + (s[i] - '0');
                    //pow = pow * 10 + s[i];
                    i++;
                }
            }
            switch (var) {
            case 'x':
                pow_x = pow;
                break;
            case 'y':
                pow_y = pow;
                break;
            case 'z':
                pow_z = pow;
                break;
            }
        }
    }

int Monom::getPowX()
{
    return pow_x;
}
    int Monom::getPowY()
    {
        return pow_y;
    }
    int Monom::getPowZ()
    {
        return pow_z;
    }
    double Monom::getCoeff()
    {
        return coeff;
    }

    Monom Monom::operator+(const Monom& m) const
    {
        if (pow_x == m.pow_x && pow_y == m.pow_y && pow_z == m.pow_z) {
            return Monom(coeff + m.coeff, pow_x, pow_y, pow_z);
        }
        return *this;
    }

    Monom Monom::operator*(const Monom& other) const
    {
        return Monom(coeff * other.coeff, pow_x + other.pow_x, pow_y + other.pow_y, pow_z + other.pow_z);
    }

    bool Monom::operator==(const Monom& m) const
    {
        return (coeff == m.coeff && pow_x == m.pow_x && pow_y == m.pow_y && pow_z == m.pow_z);
    }

    // Сравнение по сумме степеней, затем по коэффициентам
    bool Monom::operator<(const Monom& m) const
    {
        if (pow_x + pow_y + pow_z != m.pow_x + m.pow_y + m.pow_z) {
            return (pow_x + pow_y + pow_z) < (m.pow_x + m.pow_y + m.pow_z);
        }
        // Если степени одинаковые, сравниваем коэффициенты
        return coeff < m.coeff;
    }

    ostream& operator<<(ostream& ostr, const Monom& m)
    {
        ostr << "Коэффициент: " << m.coeff << endl;
        ostr << "Степень X: " << m.pow_x << endl << "Степень Y: " << m.pow_y << endl << "Степень Z: " << m.pow_z << endl;
        return ostr;
    }