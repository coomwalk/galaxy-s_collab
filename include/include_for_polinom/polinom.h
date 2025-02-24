#pragma once
#ifndef __Polynom__
#define __Polynom__

#include<iostream>
#include<string>
#include <cctype>
#include <sstream>
#include "monom.h"
#include "list.h"
using namespace std;

/*template <class T>
struct Node
{
    T value;
    Node* next;
    Node(T val1, Node* p) : value(val1), next(p) {}
};

template <class T>
class List {
    Node<T>* first; //first ук-ль на первое звено
    Node<T>* last;
public:
    List() : first(nullptr) {}
    ~List() {
        while (first != nullptr) {
            Node<T>* temp = first;
            first = first->next;
            delete temp;
        }
    }
    // Конструктор копирования
    List(const List<T>& other) : first(nullptr), last(nullptr) {
        Node<T>* current = other.first;
        while (current != nullptr) {
            Insert(current->value);
            current = current->next;
        }
    }
    // Оператор присваивания
    List<T>& operator=(const List<T>& other) {
        if (this != &other) { // Проверяем самоприсваивание
            // Освобождаем текущие 
            while (first != nullptr) {
                Node<T>* temp = first;
                first = first->next;
                delete temp;
            }
            // Инициализируем указатели для нового списка
            first = nullptr;
            last = nullptr;
            // Копируем элементы из другого списка
            Node<T>* current = other.first;
            while (current != nullptr) {
                Insert(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    void InsertCurr(Node<T>* prev, Node<T>* curr, T value) {  // добавление элемента между prev и curr
        Node<T>* p = new Node<T>(value, nullptr);
        if (first == nullptr) {  // Если список пуст
            first = p;
            last = p;
            return;
        }
        // Если добавляется в начало
        if (prev == nullptr) {
            p->next = first;
            first = p;
            return;
        }
        // Если добавляется в конец
        if (curr == nullptr) {
            p->next = nullptr;
            last->next = p;
            last = p;
            return;
        }
        // последний вариант - добавляение в середину, между prev и curr
        prev->next = p;
        p->next = curr;
    }

    void DeleteCurr(Node<T>* prev, Node<T>* curr) {  // удаление curr
        Node<T>* p;
        if (first == last) {  // Если список пуст
            delete curr;
            first = last = nullptr;
            return;
        }
        // Если удаляется первый
        if (prev == nullptr) {
            p = first;
            first = first->next;
            delete p;
            return;
        }
        // удаление любого другого
        if (curr != nullptr) {
            p = curr;
            prev->next = curr->next;
            delete p;
            return;
        }
    }

    void Insert(T value) {  // добавление элемента в упорядоченном порядке
        Node<T>* p = new Node<T>(value, nullptr);
        if (first == nullptr) {  // Если список пуст
            first = p;
            last = p;
            return;
        }
        // Если добавляемый элемент меньше первого элемента
        if (value < first->value) {
            p->next = first;
            first = p;
            return;
        }
        // Найдем позицию для вставки
        Node<T>* current = first;
        while (current->next != nullptr && current->next->value < value) {
            current = current->next;
        }
        p->next = current->next;
        current->next = p;
        // Обновляем указатель на последний узел
        if (p->next == nullptr) {
            last = p;
        }
    }

    /*void Insert(T val) {  //просто добавляем
        Node<T>* p = new Node<T>(val, nullptr);
        if (first == nullptr) { // Если список пуст
            first = p;
            last = p;
        }
        else { // Если список не пуст
            last->next = p; // Указываем, что текущий последний элемент ссылается на новый
            last = p;       // Обновляем указатель на последний элемент
        }
    }

    void print() {
        Node<T>* p = first;
        while (p->next != nullptr) { //пока список не кончится
            cout << p->value << " ";
            p = p->next;
        }
        cout << p->value; //печать послед.
    }

    Node<T>* getFirst() {
        return first;
    }
};*/

class Polynom
{
    List<Monom> p;

public:
    Polynom();
    Polynom(const string& s);
    void printPol();
    Polynom operator+(Polynom& other);
    Polynom operator*(Monom& m);
    Polynom operator*(Polynom& other);
    friend Polynom operator*(Monom& m, Polynom& oth);
    //Polynom operator*(Monom& m, Polynom& p);
};
#endif


