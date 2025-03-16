#ifndef VEC_TABLE
#define VEC_TABLE

#include <vector>
#include "table_mama_and_papa.h"
#include "../include_for_polinom/polinom.h"

template<class tkey , class tval>
class table_on_vector: public table_mama_and_papa
{
    public:

    table_on_vector() = default;

    void insert(const tkey& key, const tval& val)
    {   
        vec.push_back(std::make_pair(key,val));
    };

    void erase(cosnt tkey& key)
    {
        if(vec.size() != 0)
        {
            int i;
            bool flag = false;
            for(i = 0; i < vec.size();i++)
            {
                if (vec[i].first == key)
                {
                    flag = true;
                 break;
                }
            }
            if(flag)
            {
                std::swap(vec[i],vec[vec.size()-1]);
                vec.pop_back();
            }
            else std::cout<<"element "<<key<<" don't exist"<<std::endl;
        }
        else std::cout<<"vec is empty"<<std::endl;
    };
    tval find(const tkey& key) const
    {
        Polynom zxc();
        if(vec.size() != 0)
        {
            bool flag = false;
            for(int i = 0; i < vec.size();i++)
            {
                if (vec[i].first == key)
                {
                    zxc = vec[i].second;
                    flag = true;
                    break;
                }
            }
            if (flag) return zxc;
            else 
            {
                std::cout<<"NOT FIND "<<key<<" returned empty polynom"<<std::endl;
                return zxc;
            } 
        }
        else std::cout<<"vec is empty returned empty polinom"<<std::endl;
        return zxc;
    };

    ~table_on_vector() = default;

    private:

    std::vector<std::pair<tkey, tval>> vec;

};











#endif