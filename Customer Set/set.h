#ifndef DEQUE_H
#define DEQUE_H
#ifdef UNIT_TESTING_
int main(int argc, const char **argv);
#endif

#include <cstddef>
#include <iostream>
#include <string>

//no inline implementations!
namespace custom
{
template <class T>
class set
{
public:
    T *buffer;
    int numElements;
    int numCapacity;

    void init(int newCapacity);
    set();
    set(const int numCapacity);
    set(const set<T> &rhs);
    ~set();

    set<T> &operator=(const set<T> &rhs);
    int size() const;
    bool empty() const;
    void clear();
    int capacity();

    class iterator; //Nested Class Implementation bellow out of the scope

    iterator find(const T &t);
    void insert(const T &t);
    void erase(iterator &it);

    //Union
    set<T> &operator||(const set<T> &rhs);

    //Intersection
    set<T> &operator&&(const set<T> &rhs);

    //differences
    set<T> &operator-(const set<T> &rhs);

    iterator begin();
    iterator end();

    int findIndex(const T &t);
    void resize(const int newSize);
};

//Iterator Class
template <class T>
class set<T>::iterator
{

public:
    T *ptr;

public:
    iterator();
    iterator(T *p);
    iterator(const iterator &it);
    iterator &operator=(const iterator &it);
    bool operator==(const iterator &it) const;
    bool operator!=(const iterator &it) const;
    iterator &operator++();
    iterator &operator--(); //Remember the rule of prefix and pos fix
    iterator operator++(int postfix);
    iterator operator--(int postfix);
    T &operator*() const;
};

/********************************************************************************************
    * IMPLEMENTATION OF SET METHODS 
    * *******************************************************************************************/
template <class T>
void set<T>::init(int newCapacity)
{
    numElements = 0;
    numCapacity = newCapacity;
    buffer = NULL;
    if (newCapacity > 0)
    {
        buffer = new T[newCapacity];
    }
}

/***********************************
    * DEFAULT CONSTRUCTOR
    ************************************/
template <class T>
set<T>::set()
{
    init(0);
}

/***********************************
    * NON-DEFAULT CONSTRUCTOR
    ************************************/
template <class T>
set<T>::set(const int numCapacity)
{
    if (numCapacity < 0)
    {
        throw "Error: set sizes must be greater than or equal to 0.";
    }
    init(numCapacity);
}

/***********************************
    * COPY CONSTRUCTOR
    ************************************/
template <class T>
set<T>::set(const set<T> &rhs)
{
    *this = rhs;
}

/***********************************
    * DESTRUCTOR
    ************************************/
template <class T>
set<T>::~set()
{
    if (buffer != NULL)
        delete[] buffer;
}

/***********************************
    * ASSIGN OPERATOR
    ************************************/
template <class T>
set<T> &set<T>::operator=(const set<T> &rhs)
{
    init(rhs.numElements);
    for (int i = 0; i < rhs.numElements; i++)
        buffer[i] = rhs.buffer[i];
    numElements = rhs.numElements;
    return *this;
}

/***********************************
    * RETURN SIZE
    ************************************/
template <class T>
int set<T>::size() const
{
    return numElements;
}

/***********************************
    * CHECK IF IT EMPTY
    ************************************/
template <class T>
bool set<T>::empty() const
{
    if (numElements == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/***********************************
    * CLEAR THE BUFFER
    ************************************/
template <class T>
void set<T>::clear()
{
    numElements = 0;
}

/***********************************
    * FIND AN ELEMENT
    ************************************/
template <class T>
typename set<T>::iterator set<T>::find(const T &t)
{
    iterator value;
    int index = findIndex(t);
    if (index != numElements && buffer[index] == t)
    {
        value = iterator(buffer + index);
    }
    return value;
}

/***********************************
    * INSERT AN ELEMENT
    ************************************/
template <class T>
void set<T>::insert(const T &t)
{
    int iInsert = findIndex(t);
    if (iInsert == numElements || buffer[iInsert] != t)
    {
        if (numCapacity == numElements)
        {
            resize(numCapacity == 0 ? 1 : numCapacity * 2);
        }
        for (int i = numElements; i > iInsert; i--)
        {
            buffer[i] = buffer[i - 1];
        }
        buffer[iInsert] = t;
        numElements++;
    }
}

/***********************************
    * ERASE AN ELEMENT
    ************************************/
template <class T>
void set<T>::erase(const iterator &it)
{
    iterator empty;
    if (it != empty)
    {
        T t = *it;
        int index = findIndex(t);
        if (index != numElements && buffer[index] == t)
        {
            for (int i = index; i < numElements; i++)
            {
                buffer[i] = buffer[i + 1];
            }
        }
        numElements--;
    }
}

/***********************************
    * UNION OVERLOAD
    ************************************/
template <class T>
set<T> &set<T>::operator||(const set<T> &rhs)
{
    int iLhs = 0;
    int iRhs = 0;
    set<T> result(numElements + rhs.numElements);

    while (iLhs < numElements || iRhs < rhs.numElements)
    {
        // The end of the left so it adds to the right.
        if (iLhs == numElements)
            result.buffer[result.numElements++] = rhs.buffer[iRhs++];

        // the end of the right so it addes to the left.
        else if (iRhs == rhs.numElements)
            result.buffer[result.numElements++] = buffer[iLhs++];

        // if the left set comes before the right, it addes to the left.
        else if (buffer[iLhs] < rhs.buffer[iRhs])
            result.buffer[result.numElements++] = buffer[iLhs++];

        // if the right set comes before the left, it addes to the right.
        else if (buffer[iLhs] > rhs.buffer[iRhs])
            result.buffer[result.numElements++] = rhs.buffer[iRhs++];

        // when both sides are the same, it addes wither iLhs or iRhs.
        else if (buffer[iLhs] == rhs.buffer[iRhs])
        {
            result.buffer[result.numElements++] = buffer[iLhs++];
            iRhs++; // can also be iLhs++;
        }
    }
    if (result.numElements == 0)
        result.buffer = NULL;
    result.numCapacity = result.numElements;
    return result;
}

/***********************************
    * INTERSECTION OVERLOAD
    ************************************/
template <class T>
set<T> &set<T>::operator&&(const set<T> &rhs)
{
    int iLhs = 0;
    int iRhs = 0;
    set<T> result(numElements + rhs.numElements);

    while (iLhs < numElements || iRhs < rhs.numElements)
    {
        if (iLhs == numElements || iRhs == rhs.numElements)
            break;

        // when the left comes before the right, we put the left first
        else if (buffer[iLhs] < rhs.buffer[iRhs])
            iLhs++;

        // when the right comes before the left, we put the right first
        else if (buffer[iLhs] > rhs.buffer[iRhs])
            iRhs++;

        // when both sides are the same. We add either one.
        else if (buffer[iLhs] == rhs.buffer[iRhs])
        {
            result.buffer[result.numElements++] = buffer[iLhs++];
            iRhs++; // can also be iLhs++;
        }
    }
    if (result.numElements == 0)
    {
        result.buffer = NULL;
    }
    result.numCapacity = result.numElements;
    return result;
}
/***********************************
    * DIFFERENCES OVERLOAD
    ************************************/
template <class T>
set<T> &set<T>::operator-(const set<T> &rhs)
{
    int iLhs = 0;
    int iRhs = 0;
    set<T> result(numElements + rhs.numElements);

    while (iLhs < numElements || iRhs < rhs.numElements)
    {
        // the end of the left, done, because there are no more elements on the left to compare
        if (iLhs == numElements)
            break; // don't do anything but continue.

        // the end of the right, therefore we add the left.
        // because we have something on the left but not on the right.
        else if (iRhs == rhs.numElements)
            result.buffer[result.numElements++] = buffer[iLhs++];

        // if we have something on the left, that's not on the right,
        // we left comes before the right, so we add the left.
        else if (buffer[iLhs] < rhs.buffer[iRhs])
            result.buffer[result.numElements++] = buffer[iLhs++];

        // when right comes before left, move the right to the next element.
        else if (buffer[iLhs] > rhs.buffer[iRhs])
            iRhs++;

        // if both sides are the same we move both of them.
        else if (buffer[iLhs] == rhs.buffer[iRhs])
        {
            iRhs++;
            iLhs++;
        }
    }
    if (result.numElements == 0)
        result.buffer = NULL;
    result.numCapacity = result.numElements;
    return result;
}
/***********************************
    * RETURN THE BEGIN OF THE BUFFER
    ************************************/
template <class T>
typename set<T>::iterator set<T>::begin()
{
    return iterator(buffer);
}

/***********************************
    * RETURN THE END OF THE 
    ************************************/
template <class T>
typename set<T>::iterator set<T>::end()
{
    return iterator(buffer + numElements);
}

/***********************************
    * FIND THE INDEX
    ************************************/
template <class T>
int set<T>::findIndex(const T &t)
{
    int iBegin = 0;
    int iEnd = numElements - 1;
    while (iBegin <= iEnd)
    {
        int iMiddle = (iBegin + iEnd) / 2;
        if (buffer[iMiddle] >= t)
        {
            iEnd = iMiddle - 1;
        }
        else
        {
            iBegin = iMiddle + 1;
        }
    }

    return iBegin;
}

/***********************************
    * RESIZE
    ************************************/
template <class T>
void set<T>::resize(const int newCapacity)
{
    if (newCapacity == 0)
        init(0);
    if (newCapacity > 0)
    {
        T *newBuffer = new T[newCapacity];
        int a = (newCapacity < numElements) ? newCapacity : numElements;
        for (int i = 0; i < a; i++)
            newBuffer[i] = buffer[i];
        delete[] buffer;
        buffer = newBuffer;
        numCapacity = newCapacity;
        numElements = a;
    }
}



/********************************************************************************************
    * IMPLEMENTATION OF THE ITERATOR 
    * *******************************************************************************************/
/**********************************************************
    * Interator Default Iterator
    * ********************************************************/
template <class T>
set<T>::iterator::iterator()
{
    ptr = NULL;
}

/**********************************************************
    * Noun Default Iterator
    * ********************************************************/
template <class T>
set<T>::iterator::iterator(T *p)
{
    ptr = p;
}

/**********************************************************
    * Copy Constructor
    * ********************************************************/
template <class T>
set<T>::iterator::iterator(const iterator &it)
{
    *this = it;
}

/**********************************************************
    * The assignment opertator =
    * ********************************************************/
template <class T>
typename set<T>::iterator &set<T>::iterator::operator=(const iterator &it)
{
    ptr = it.ptr;
}

/**********************************************************
    * The coomparation Operator ==
    * ********************************************************/
template <class T>
bool set<T>::iterator::operator==(const iterator &it) const
{
    return ptr == it.ptr;
}

/**********************************************************
    * The coomparation Operator !=
    * ********************************************************/
template <class T>
bool set<T>::iterator::operator!=(const iterator &it) const
{
    return (ptr != it.ptr);
}

/**********************************************************
    * PRE-FIX OPERATOR ++
    * ********************************************************/
template <class T>
typename set<T>::iterator &set<T>::iterator::operator++()
{
    if (ptr != NULL)
    {
        ptr++;
    }

    return *this;
}

/**********************************************************
    * PRE-FIX OPERATOR --
    * ********************************************************/
template <class T>
typename set<T>::iterator &set<T>::iterator::operator--()
{
    if (ptr != NULL)
    {
        ptr--;
    }

    return *this;
}

/**********************************************************
    * PRO-FIX OPERATOR ++
    * ********************************************************/
template <class T>
typename set<T>::iterator set<T>::iterator::operator++(int postfix)
{
    iterator temp = iterator(ptr);
    if (ptr != NULL)
    {
        ptr++;
    }

    return temp;
}

/**********************************************************
    * PRO-FIX OPERATOR --
    * ********************************************************/
template <class T>
typename set<T>::iterator set<T>::iterator::operator--(int postfix)
{
    iterator temp = iterator(ptr);
    if (ptr != NULL)
    {
        ptr--;
    }

    return temp;
}

/**********************************************************
    * Dereference Operator *
    * ********************************************************/
template <class T>
T &set<T>::iterator::operator*() const
{
    return *ptr;
}

}; // namespace custom

#endif