#ifndef AVL_TABLE
#define AVL_TABLE

#include "table_mama_and_papa.h"
#include "../include_for_polinom/polinom.h"
template<class tkey , class tval>
class table_on_avl: public table_mama_and_papa
{
    public:

    void insert(const tkey& key, const tval& val)
    {};
    void erase(cosnt tkey& key)
    {};
    tval find(const tkey& key) const
    {};
    //constructor and destructor

    private:


};




#endif