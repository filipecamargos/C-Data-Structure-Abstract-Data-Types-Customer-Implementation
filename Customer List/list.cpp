#include "list.h"
#include <cstring>
#include "unit_testing.h"

using namespace custom;

/*******************************************************************************
FUNCTION IMPLEMENTATION
/*******************************************************************************/
template <class T>
void list<T>::insertAt(node *pNode, T t, bool after)
{

    node *pNew = new node(t);

    if (empty())
    {

        pHead = pNew;

        pTail = pNew;

        numElements++;

        return;
    }

    if (after == false)
    {

        if (pHead == pNode)

            pHead = pNew;

        pNew->pNext = pNode;

        pNew->pPrev = pNode->pPrev;

        pNode->pPrev = pNew;

        if (pNew->pPrev)
        {

            pNew->pPrev->pNext = pNew;
        }

        numElements++;
    }

    else
    {

        if (pTail == pNode)

            pTail = pNew;

        pNew->pPrev = pNode;

        pNew->pNext = pNode->pNext;

        pNode->pNext = pNew;

        if (pNew->pNext)
        {

            pNew->pNext->pPrev = pNew;
        }

        numElements++;
    }
}

//DEFAULT CONSTRUCTORS
template <class T>
list<T>::list()
{

    pHead = NULL;

    pTail = NULL;

    numElements = 0;
}

//NON DEFAULT CONSTRUCTOR
template <class T>
list<T>::list(const list<T> &rhs)
{

    pHead = NULL;

    pTail = NULL;

    numElements = 0;

    if (rhs.numElements != 0)
    {

        *this = rhs;
    }
}

//DESTRUCTOR
template <class T>
list<T>::~list()
{
    unit_testing_delete_call_counter++;
    clear();
}

//ASSIGN OPERATOR
template <class T>
list<T> &list<T>::operator=(const list<T> &rhs)
{

    clear();

    for (node *p = rhs.pHead; p; p = p->pNext)
    {

        insertAt(pTail, p->data, true);
    }

    return *this;
}

//GET LIST SIZE
template <class T>
int list<T>::size()
{
    return numElements;
}

//CHECK IF IT IS EMPTY
template <class T>
bool list<T>::empty()
{
    return (numElements == 0);
}

//CLEAR THE LIST
template <class T>
void list<T>::clear()
{
    if (!empty())
    {

        node *pDelete;

        while (pHead != NULL)
        {

            pDelete = pHead;

            pHead = pHead->pNext;

            delete pDelete;
        }

        pTail = NULL;

        numElements = 0;
    }
}

//PUSH AN ITEM BACK
template <class T>
void list<T>::push_back(const T &t)
{

    insertAt(pTail, t, true);
}

//PUSH AN ITEM FRONT
template <class T>
void list<T>::push_front(const T &t)
{
    insertAt(pHead, t, false);
}

//POP ONE ITEM  BACK
template <class T>
void list<T>::pop_back()
{

    if (!empty())
    {

        pTail = pTail->pPrev;

        pTail->pNext = NULL;

        numElements--;
    }
}

//POP AN ITEM FRONT
template <class T>
void list<T>::pop_front()
{

    if (!empty())
    {

        pHead = pHead->pNext;

        pHead->pPrev = NULL;

        numElements--;
    }
}

//RETURN THE FRONT ITEM
template <class T>
T &list<T>::front()
{

    if (!empty())

        return pHead->data;

    else

        throw "Error: Calling front on empty list.";
}

//RETUR THE BACK ITEM
template <class T>
T &list<T>::back()
{

    if (!empty())

        return pTail->data;

    else

        throw "Error: Calling back on empty list.";
}

//INSERT AN ITEM TO A PLACE SPECIFIED
template <class T>
void list<T>::insert(iterator it, const T &t)
{

    insertAt(it.ptr, t, false);
}

template <class T>
typename list<T>::iterator list<T>::find(const T &t)
{

    iterator it;


    for (node *p = pHead; p; p = p->pNext)
    {

        if (p->data == t)
        {

            it = iterator(p);

            break;
        }
    }

    return it;
}

template <class T>
typename list<T>::iterator list<T>::erase(iterator it)
{

    node *pTarget = it.ptr;

    if (pTarget == NULL)

        return iterator(NULL);

    node *pResult = (pTarget->pPrev) ? pTarget->pPrev : pTarget->pNext;

    if (pTarget->pPrev)

        pTarget->pPrev->pNext = pTarget->pNext;

    if (pTarget->pNext)

        pTarget->pNext->pPrev = pTarget->pPrev;

    if (pTarget == pHead)

        pHead = pTarget->pNext;

    delete pTarget;

    pTarget = NULL;

    return iterator(pResult);
}

template <class T>
typename list<T>::iterator list<T>::begin()
{

    return iterator(*root);
}

template <class T>
typename list<T>::iterator list<T>::end()
{
    return iterator(NULL);
}

/**************************************************

 * Node Class Methods Begin.

 **************************************************/

template <class T>
list<T>::node::node()
{

    data = T();

    pNext = NULL;

    pPrev = NULL;
}

template <class T>
list<T>::node::node(T t)
{

    data = t;

    pNext = NULL;

    pPrev = NULL;
}

template <class T>

list<T>::node::~node()
{
    unit_testing_delete_call_counter++;
}

/**************************************************

 * Iterator Class Methods Begin.

 **************************************************/

template <class T>

list<T>::iterator::iterator()
{

    ptr = NULL;
}

template <class T>
list<T>::iterator::iterator(node *ptr)
{

    this->ptr = ptr;
}

template <class T>
list<T>::iterator::iterator(const iterator &rhs)
{

    this->ptr = rhs.ptr;
}

template <class T>
typename list<T>::iterator &list<T>::iterator::operator=(const iterator &it)
{

    this->ptr = it.ptr;

    return *this;
}

template <class T>
bool list<T>::iterator::operator==(const iterator it) const
{

    return ptr == it.ptr;
}

template <class T>
bool list<T>::iterator::operator!=(const iterator it) const
{

    return ptr != it.ptr;
}

template <class T>
typename list<T>::iterator &list<T>::iterator::operator++()
{

    if (ptr == NULL)

        throw "Error: Incrementing null node.";

    if (ptr->pNext)

        ptr = ptr->pNext;

    return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator++(int postfix)
{

    iterator tmp(*this);

    if (ptr == NULL)

        throw "Error: Incrementing null node.";

    if (ptr->pNext)

        ptr = ptr->pNext;

    return tmp;
}

template <class T>
typename list<T>::iterator &list<T>::iterator::operator--()
{

    if (ptr == NULL)

        throw "Error: Decrementing null node.";

    if (ptr->pPrev)

        ptr = ptr->pPrev;

    return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator--(int postfix)
{

    iterator tmp(*this);

    if (ptr == NULL)

        throw "Error: Decrementing null node.";

    if (ptr->pPrev)

        ptr = ptr->pPrev;

    return tmp;
}

template <class T>
T &list<T>::iterator::operator*()
{

    if (ptr == NULL)

        throw "Error: Dereferencing null node.";

    return ptr->data;
}
/*
template <class T>
std::ostream &operator<<(std::ostream &out, const typename list<T>::node *pHead)
{

    for (const typename list<T>::node *pCurrent = pHead; pCurrent; pCurrent = pCurrent->pNext)
    {

        if (pCurrent->pNext != NULL)

            out << pCurrent->data << ", ";

        else

            out << pCurrent->data;
    }

    return out;
}*/