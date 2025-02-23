// объявление функций и классов для вычисления арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include "super_stack.h"

using namespace std;

struct lexema
{
    int type; // !переменная 1  || число-операнд 2 || !операция 3 || 4 скобка 
    string  str;
    lexema(int first, string second);
    bool operator == (const lexema& zxc)const noexcept;
    friend ostream& operator <<(ostream &os, const lexema& zxc);
};

class for_check;

class arithmetic
{
    friend class for_check;
    private:
    string inputstring;
    vector <lexema> input;
    vector <lexema> postfix;
    string postfix_string = "";
    map <string, double> variables;
    map <string, int> priority;
    bool check()const ;
    void parser();
    void to_postfix()noexcept;
    void getvalue();
    double calculate()  noexcept;

    public:

    arithmetic(string& tmp) noexcept;
    double try_calculate();
    ~arithmetic() = default;



    string input_string_out()const noexcept;
    string postfix_string_out()  noexcept;
};

class for_check
{
    public:
    bool check_parser( arithmetic& zxc, const vector <lexema> res);
    bool check_check(arithmetic& zxc);
    bool check_calculate(arithmetic& zxc, const double& res);
    bool check_postfix(arithmetic& zxc, const string& res);


};








#endif