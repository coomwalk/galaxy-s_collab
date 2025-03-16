#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include "polinom.h"
#include "monom.h"
#include "list.h"

Polynom::Polynom(const string& s) //-3.1x10y10z10 + 20.2x-10y-10z-10
{
    std::string copy_s = s;
    std::string tmp;
    std::string::iterator it = copy_s.begin();

    while (it != copy_s.end())
    {
        if (*it != ' ' && *it != '+')
        {
            tmp.push_back(*it);
        }
        else if(*it == '+')
        {
            polinoms.InsertToTail(Monom(tmp));
            tmp.clear();
        }

        ++it;
    }

    if (it == copy_s.end())
    {
        polinoms.InsertToTail(Monom(tmp));
        tmp.clear();
    }
}
Polynom::Polynom(Polynom&& p) noexcept
{
    polinoms = std::move(p.polinoms);  
}

Polynom::Polynom(const Polynom& p)
{
    polinoms.Clean();
    listIterator<Monom> start = p.polinoms.GetFirst();

    while (start != p.polinoms.end())
    {
        polinoms.InsertToTail(*start);
        ++start;
    }
}

Polynom& Polynom::operator=( const Polynom& p)
{
    if (this == &p)
    {
        return *this;
    }

    polinoms.Clean();
    
    listIterator<Monom> start = p.polinoms.GetFirst();

    while (start != p.polinoms.end())
    {
        polinoms.InsertToTail(*start);
        ++start;
    }

    return *this;
}
Polynom& Polynom::operator=(Polynom&& p) noexcept
{
    polinoms = std::move(p.polinoms);
    return *this;
}

Polynom Polynom::operator*(Monom& m)
{
    Polynom res;
    listIterator<Monom> start;// = polinoms.GetFirst();

    for (start = polinoms.GetFirst(); start != polinoms.end(); ++start)
    {
        Monom tmp = *start * m;
        res.polinoms.InsertToTail(tmp);
    }

    return res;
}

Polynom Polynom::operator*(double& oth)
{
    Polynom res;
    listIterator<Monom> start;// = polinoms.GetFirst();

    for (start = polinoms.GetFirst(); start != polinoms.end(); ++start)
    {
        Monom tmp = *start * oth;
        res.polinoms.InsertToTail(tmp);
    }

    return res;


}

Polynom Polynom::operator+(Polynom& p)
{
    Polynom res;

    res.polinoms = polinoms.Merge(p.polinoms);
    res.DelCoeffZero();
    
    listIterator<Monom> it = res.polinoms.GetFirst();
    listIterator<Monom> next_it = it;

    while (it != res.polinoms.end())
    {
        next_it = it;
        ++next_it;

        while (next_it != res.polinoms.end())
        {
            if ((*it).EqPow(*next_it))
            {
                *it = *it + *next_it;
                listIterator<Monom> to_delete = next_it;
                ++next_it;
                res.polinoms.Delete(*to_delete);
            }
            else
            {
                ++next_it;
            }
        }
        ++it;
    }

    return res;
}

Polynom Polynom::operator-(Polynom& p)
{
    Polynom res;
    double c = -1.0;
    p = p * c;
    res = *this + p;

    return res;
}

Polynom Polynom::operator*(Polynom& p)
{
    Polynom res;

    listIterator<Monom> it1;// = polinoms.GetFirst();
    

    for (it1 = polinoms.GetFirst(); it1 != polinoms.end(); ++it1)
    {
        for (listIterator<Monom> it2 = p.polinoms.GetFirst(); it2 != p.polinoms.end(); ++it2)
        {
            Monom tmp = *it1 * *it2;
            res.polinoms.InsertToTail(tmp);
        }
    }
    res.DelCoeffZero();

    listIterator<Monom> it = res.polinoms.GetFirst();
    listIterator<Monom> next_it = it;

    while (it != res.polinoms.end())
    {
        next_it = it;
        ++next_it;

        while (next_it != res.polinoms.end())
        {
            if ((*it).EqPow(*next_it))
            {
                *it = *it + *next_it;
                listIterator<Monom> to_delete = next_it;
                ++next_it;
                res.polinoms.Delete(*to_delete);
            }
            else
            {
                ++next_it;
            }
        }
        ++it;
    }


    return res;
}

ostream& operator<<(ostream& ostr, const Polynom& p)
{
    listIterator<Monom> start;// = p.polinoms.GetFirst();
    listIterator<Monom> end = p.polinoms.end();

    for (start = p.polinoms.GetFirst(); start != end; ++start)
    {
        ostr << *start;
        if (std::next(start) != end)
        {
            ostr << " + ";
        }
    }

    return ostr;
}

istream& operator>>(istream& istr, Polynom& poli)
{
    poli.polinoms.Clean();

    std::string input;

    cout << "Enter <<end>> to exit" << endl;
    cout << "Enter Polinom:" << endl;

    while (true)
    {
        cout << "> ";
        istr >> input;

        if (input == "end")
        {
            break;
        }

        poli.polinoms.InsertToTail(Monom(input));
    }
    
    return istr;
}

void Polynom::DelCoeffZero()
{
    listIterator<Monom> current = polinoms.GetFirst();

    while (current != polinoms.end())
    {
        if ((*current).GetCoeff() == 0.0)
        {
            listIterator<Monom> del = current;
            ++current;
            polinoms.Delete(*del);
        }
        else
        {
            ++current;
        }
    }
}
