#include "arithmetic.h"
#include <sstream>

lexema::lexema(int first, string second) : type(first), str(second)
{
}
bool lexema::operator==(const lexema &zxc) const noexcept
{
    return (type == zxc.type) && (str == zxc.str);
}
ostream &operator<<(ostream &os, const lexema &zxc)
{
    cout << "{" << zxc.type << ", " << zxc.str << "}, ";
    return os;
}

arithmetic::arithmetic(string &tmp) noexcept : inputstring(tmp)
{
    priority = {
        pair<string, int>{"+", 1}, pair<string, int>{"-", 1},
        pair<string, int>{"*", 2}, pair<string, int>{"/", 2},
        pair<string, int>{"(", 0}};
}
/* arithmetic::arithmetic()
    {
        priority = {
        pair<string, int>{"+", 1}, pair<string, int>{"-", 1},
        pair<string, int>{"*", 2}, pair<string, int>{"/", 2},
        pair<string, int>{"(", 0}};
    }
*/
/* void arithmetic::new_polinom_for_calculate(string &tmp) noexcept :
    {
        inputstring.clear();
        input.clear();
        postfix.clear();
        postfix_string.clear();
        variables.clear();
        inputstring = tmp;
    }



*/

void arithmetic::parser()
{
    if (inputstring.size() == 0)
        throw "so_small_input";

    for (size_t i = 0; i < inputstring.size(); i++)
    {
        if (isalpha(inputstring[i])) /// считаю, что переменные состоят из одной буквы(не сочетание)
        {
            string k(1, inputstring[i]);
            lexema tmp(1, k);
            variables[k] = 0.0;
            input.push_back(tmp);
        }
        if (strchr("+-*/", inputstring[i]) != nullptr)
        {
            string k(1, inputstring[i]);
            lexema tmp(3, k);
            input.push_back(tmp);
        }
        if (strchr("()", inputstring[i]) != nullptr)
        {
            string k(1, inputstring[i]);
            lexema tmp(4, k);
            input.push_back(tmp);
        }

        if ((isdigit(inputstring[i])) || (inputstring[i] == '.') || (inputstring[i] == ','))
        {
            string tmp1(1, inputstring[i]);
            int z = 0;
            for (int j = i + 1; j < inputstring.size(); j++)
            {
                if ((isdigit(inputstring[j])) || (inputstring[j] == '.') || (inputstring[j] == ','))
                {
                    tmp1 += inputstring[j];
                    i++;
                }

                else
                    break;
            }
            lexema tmp(2, tmp1);
            input.push_back(tmp);
        }
    }
}
bool arithmetic::check() const
{
    int sosotoinie_skobok = 0;
    if ((input[0].str == "+") || (input[0].str == "*") || (input[0].str == "/"))
    {
        throw "first symbol is invalid(operation)";
    }
    for (size_t i = 0; i < input.size() - 1; i++)
    {

        if (input[i].str == "(")
            sosotoinie_skobok++;
        if (input[i].str == ")")
            sosotoinie_skobok--;
        if (sosotoinie_skobok < 0)
            throw "error skobki";

        for (int k = 1; k < 3; k++)
        {
            for (int p = 1; p < 3; p++)
            {
                if (input[i].type == k && input[i + 1].type == p)
                    throw " error operands";
            }
        }
        if (input[i].type == 3 && input[i + 1].type == 3)
            throw " error (oper)(oper)";
        if (input[i].type == 3 && input[i + 1].str == ")")
            throw "error (oper) ) ";
    }
    if (input[input.size() - 1].str == "(")
        sosotoinie_skobok++;
    if (input[input.size() - 1].str == ")")
        sosotoinie_skobok--;

    if (sosotoinie_skobok != 0)
        throw "error skobki";

    return true;
}

void arithmetic::to_postfix() noexcept
{
    super_stack<lexema> st;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i].type == 1 || input[i].type == 2)
            postfix.push_back(input[i]);
        if (input[i].str == "(")
            st.push(input[i]);
        if (input[i].str == ")")
        {
            while (st.Top().str != "(")
            {
                postfix.push_back(st.Top());
                st.pop();
            }

            st.pop();
        }
        if (input[i].type == 3)
        {

            while (!st.empty())
            {
                lexema rt = st.pop();

                if (priority[input[i].str] <= priority[rt.str])
                {
                    postfix.push_back(rt);
                }
                else
                {
                    st.push(rt);
                    break;
                }
            }
            st.push(input[i]);
        }
    }
    while (!st.empty())
    {
        postfix.push_back(st.Top());
        st.pop();
    }

    for (int i = 0; i < postfix.size(); i++)
        postfix_string += postfix[i].str + " ";
    postfix_string.pop_back();
}

double arithmetic::calculate() noexcept ////    double -> polinom and lower!!! in this method
{
    super_stack<double> st;
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i].type == 1)
            st.push(variables[postfix[i].str]);

        if (postfix[i].type == 2)
        {
            for (int j = 0; j < postfix[i].str.size(); j++)
            {
                if (postfix[i].str[j] == ',')
                    postfix[i].str[j] = '.';
            }
            stringstream s(postfix[i].str); /// here SYETA
            double k;                       /// делать из числа полином!!!!!!
            s >> k;
            st.push(k);
        }

        if (postfix[i].type == 3)
        {
            string s = postfix[i].str;
            switch (s[0])
            {
            case '+':
            {
                double right = st.pop(), left = st.pop();
                st.push(left + right);
                break;
            }

            case '-':
            {
                double right = st.pop(), left = st.pop();
                st.push(left - right);
                break;
            }

            case '*':
            {
                double right = st.pop(), left = st.pop();
                st.push(left * right);
                break;
            }

            case '/':
            {
                double right = st.pop(), left = st.pop();
                st.push(static_cast<double>(left / right));
                break;
            }
            default:
            {
                cout << " it's fiasko" << endl;
                break;
            }
            }
        }
    }

    return static_cast<double>(st.pop());
}

void arithmetic::getvalue()
{
    for (auto &[first, second] : variables)
    {
        cout << "Input value of " << first << ": "; /// из таблицы брать
        cin >> second;                              // polinom NOT STR!        ////////////////////////////////////////////////////////
    }
}

double arithmetic::try_calculate() //////////     double -> polinom
{
    this->parser();
    this->check();
    this->to_postfix();
    this->getvalue();
    return this->calculate();
}

string arithmetic::input_string_out() const noexcept
{
    return inputstring;
}
string arithmetic::postfix_string_out() noexcept
{
    return postfix_string;
}

///////////////////
///////////////////
///////////////////
///////////////////
///////////////////
///////////////////
///////////////////

bool for_check ::check_parser(arithmetic &zxc, const vector<lexema> res)
{
    zxc.parser();
    return zxc.input == res;
}

bool for_check::check_check(arithmetic &zxc)
{
    zxc.parser();
    return zxc.check();
}
bool for_check::check_calculate(arithmetic &zxc, const double &res) // double -> polinom
{
    zxc.parser();
    zxc.check();
    zxc.to_postfix();
    return zxc.calculate() == res;
}
bool for_check::check_postfix(arithmetic &zxc, const string &res)
{
    zxc.parser();
    zxc.check();
    zxc.to_postfix();
    return (zxc.postfix_string == res);
}
