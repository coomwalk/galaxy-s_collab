#ifndef __SUPER_STACK_H__
#define __SUPER_STACK_H__

#include <iostream>
#include <vector>

using namespace std;

// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

template <class T>
class super_stack
{   private:

    int top = -1; 
    vector <T> zxc;

    public:

    super_stack(): top(-1){};
    super_stack(const super_stack& tmp)
    {
        zxc = tmp.zxc;
        top = tmp.top;
    }
    bool empty() const noexcept
    {
        return top == -1;
    }
    size_t size() const noexcept
    {
        return size_t(top+1);
    }
    void push(const T& tmp )
    {
        zxc.push_back(tmp);
        top++;
    }
    T pop()
    {
        if(this->empty()) throw out_of_range("pop_of_stack_is_empty");
        T out = zxc.back();
        zxc.pop_back();
        top--;
        return out;
    }
    T Top() const
    {
        if(this->empty()) throw out_of_range("top_of_stack_is_empty");
        return T(zxc.back());
    }
    void clear() noexcept
    {
        zxc.clear();
        top = -1;
    }
    super_stack& operator = (const super_stack& tmp) noexcept
    {
        zxc = tmp.zxc;
        top = tmp.top;
        return *this;
    }
    bool operator == (const super_stack& tmp) const noexcept
    {
        if(top != tmp.top) return 0;
        if(zxc != tmp.zxc) return 0;
        return 1;
    }
    bool operator != (const super_stack& tmp) const noexcept
    {
        return !(*this==tmp);
    }
    ~super_stack() = default;
};

#endif