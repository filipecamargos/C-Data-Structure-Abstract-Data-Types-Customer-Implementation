#ifndef LIST_H //Always include header guard

#define LIST_H

#ifdef UNIT_TESTING

int main(int argc, const char *argv[]);

#endif

namespace custom
{

/**********************************************************
                     LIST CLASS
/**********************************************************/
template <class T>
class list
{

public:
#ifdef UNIT_TESTING
    friend int ::main(int argc, const char *argv[]);
#endif

    class node;
    class iterator;

    //Atributes
    private:
    node *pHead;
    node *pTail;
    int numElements;

    //Methodos
    list();
    list(const list<T> &rhs);
    ~list();

    list &operator=(const list<T> &rhs);
    int size();
    bool empty();
    void clear();

    void push_back(const T &t);
    void push_front(const T &t);
    void pop_back();
    void pop_front();

    void insertAt(node *pCurrent, T element, bool after = true);
    T &front();
    T &back();
    void insert(iterator it, const T &t);

    iterator find(const T &t);
    iterator erase(iterator it);
    iterator begin();
    iterator end();
};

/*******************************
         NODE CLASS 
/*******************************/
template <class T>
class list<T>::node
{

public:
#ifdef UNIT_TESTING
    friend int ::main(int argc, const char *argv[]);
#endif

    friend list;

    node();
    node(T t);
    ~node();

private:
    T data;
    node *pNext;
    node *pPrev;
};

/*******************************
         ITERATOR CLASS
/*******************************/
template <class T>
class list<T>::iterator
{

private:
    node *ptr;

public:
#ifdef UNIT_TESTING
    friend int ::main(int argc, const char *argv[]);
#endif

    friend list;
    iterator();
    iterator(node *ptr);
    iterator(const iterator &rhs);
    iterator &operator=(const iterator &it);
    bool operator==(const iterator it) const;
    bool operator!=(const iterator it) const;
    iterator &operator++(); //num++
    iterator operator++(int postfix); //++num
    iterator &operator--();
    iterator operator--(int postfix);
    T &operator*();
};

} // namespace custom

#include "list.cpp"

#endif