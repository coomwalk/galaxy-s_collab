#ifndef ALL_TABLE
#define ALL_TABLE
#include "../include_for_polinom/polinom.h"
#include "../include_for_arithmetic/arithmetic.h"
#include "table_on_tree_AVL.h"
#include "table_on_vector.h"
#include "table_on_tree_RB.h"
#include "table_mama_and_papa.h"



template<class tkey , class tval>
class all_tables
{
    public:

    all_tables() = default;

    void Insert(const tkey& key, const tval& val)
    {
        t_vec.insert(key, val);
        //t_avl.insert(key, val);
        //t_rb.insert(key, val);
    };

    void Erase(cosnt tkey& key)
    {
        t_vec.erase(key);
        //t_avl.erase(key);
        //t_rb.erase(key);
    };

    tval Find(const tkey& key, const int what_table) const
    {
        Polynom bad;
        switch (what_table)
        {
        case 1:
            return t_vec.find(key);
            break;
        
        case 2:
            return t_avl.find(key);
            break;
        
        case 3:
            return t_rb.find(key);
            break;
        default:
            std::cout<<"it's fiasko returned empty polinom"<<std::endl;
            return bad;
            break;
        }

        
    };
    
    Polynom calculate(std::string& zxc, unsigned int what_table, std::string name_new_pol)
    {
        table_mama_and_papa* p = nullptr;
        switch (what_table)
        {
        case 1:
            p = &t_vec;
            break;
        
        case 2:
            p = &t_avl;
            break;
        
        case 3:
            p = &t_rb;
            break;
        default:
            std::cout<<"it's fiasko"<<std::endl;
            break;
        }
        
        calculator.new_task_for_calculate(zxc, p);
        Polynom tmp = calculator.try_calculate();
        this->Insert(name_new_pol, tmp);
        return tmp;
    };

    
    ~all_tables() = default;

    private:

    table_on_vector<tkey,tval> t_vec;
    table_on_avl<tkey,tval> t_avl;
    table_on_rb<tkey,tval> t_rb;

    arithmetic calculator{};
};

#endif