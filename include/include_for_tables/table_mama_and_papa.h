#ifndef MAMA_AND_PAPA
#define MAMA_AND_PAPA



template<class tkey , class tval>
class table_mama_and_papa
{
    public:

    table_mama_and_papa() = default;

    virtual void insert(const tkey& key, const tval& val) = 0;
    virtual void erase(cosnt tkey& key) = 0;
    virtual tval find(const tkey& key) const = 0;
    
    ~table_mama_and_papa() = default;

};

//for this? 
//1 it's NICE
//2 pull in map in arithmetic AND THIS SUPER NICE


#endif