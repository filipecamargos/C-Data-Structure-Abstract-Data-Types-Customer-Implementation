#ifndef VECTOR_H
#define VECTOR_H
#ifdef UNIT_TESTING_
int main(int argc, const char* argv[]);
#endif

#include <cstddef>
#include <iostream>
#include <string>

//no inline implementations!
namespace custom
{
    /***********Our Vector Class******************/
    template <class T>
    class vector
    {
        public:
            T *buffer;
            int numCapacity;
            int numElements;
        
        public:

            /*#ifdef UNIT_TESTING
                friend int  ::main(int argc, const char* argv[]);
            #endif*/

            //Constructors & desctructor
            vector(); 
            vector(const int numElements);
            vector(const int numElements, const T& t);
            vector(const vector<T>& rhs);
            ~vector();

            //Class Methods Declaration
            vector<T>& operator=(const vector<T>& rhs);
            int size() const;
            int capacity() const;
            bool empty() const;
            void clear(); 
            void push_back(const T& t);
            T& operator[](const int index);

            class iterator; //Nested Class Implementation bellow out of the scope

            iterator begin();
            iterator end();

            void resize(int numCapacity);

    };

    //Iterator Class
    template <class T>
    class vector<T>::iterator
    {
        /*#ifdef UNIT_TESTING
            friend int  ::main(int argc, const char* argv[]);
        #endif*/

        public:
        T *ptr;

        public:
        iterator();
        iterator(T *p);
        iterator(const iterator& it);
        iterator& operator=(const iterator& it);
        bool operator==(const iterator& it) const;
        bool operator!=(const iterator& it) const;
        iterator&  operator++();
        iterator& operator--(); //Remember the rule of prefix and pos fix 
        iterator operator++(int postfix);
        iterator operator--(int postfix);
        T& operator*() const;
    };

    /********************************************************************************************
    * IMPLEMENTATION OF THE FUNCTIONS FOR VECTOR
    * *******************************************************************************************/
    /************************************************
    * DEFAULT CONSTRUCTOR
    * **********************************************/
    template<class T>
    custom::vector<T>::vector()
    {
        buffer = NULL;
        numElements = 0; //Number of elements in the array 
        numCapacity = 0; //Capacity that is there
    }

    /************************************************
   * NO DEFAULT - determine the buffer size
    * **********************************************/
    template<class T>
    vector<T>::vector(const int numElements)
    {
        //Check for invalid numbers
        if(numElements <= 0)
        {
            throw "Error: vector sizes must be greater than 0.";
        }

        this->numElements = numElements;
        this->numCapacity = numElements;
        this->buffer = new T[numElements];

        //Initiate Everyhting to 0
        for (int i = 0; i < numElements; i++)
        {
            this->buffer[i] = 0;
        }
    }

    /**********************************************************
    * NO DEFAULT - SET THE VALUES SPECIFIED IN THE BUFFER
    * ********************************************************/
    template<class T>
    vector<T>::vector(const int numElements, const T& t)
    {
        //Test for wrong values
        if (numElements <= 0 )
        {
            throw "Error: vector sizes must be greater than 0.";
        }
        this->numElements = numElements;
        this->numCapacity = numElements;
        buffer = new T[numElements];

        //Assigne the values
        for (int i = 0; i < numElements; i++)
        {
            this->buffer[i] = t;
        }

    }


    /**********************************************************
    * COPY CONSTRUCTOR
    * ********************************************************/
    template <class T>
    vector<T>::vector(const vector<T>& rhs)
    {
        numCapacity = rhs.numElements;
        numElements = rhs.numElements;

        buffer = new T[numCapacity];

        for(int i = 0; i < numCapacity; i++)
        {
            buffer[i] = rhs.buffer[i];
        }

    }

    /**********************************************************
    * VECTOR DESCTRUCTOR
    * ********************************************************/
    template <class T>
    vector<T>::~vector()
    {
        delete [] buffer;
    }

    /**********************************************************
    * Assigne operator which will assing value of vector
    * ********************************************************/
    template <class T>
    vector<T>& vector<T>::operator=(const vector<T>& rhs)
    {
        numElements = 0;
        if (rhs.size() > capacity())
        {
            resize(rhs.size());
        }

        numElements = rhs.size();
        for( int i = 0; i < numElements; i++)
        {
            buffer[i] = rhs.buffer[i];
        }

        return *this;
    }

    /**********************************************************
    * Get the Size
    * ********************************************************/
    template<class T>
    int vector<T>::size() const
    {
        return numElements;
    }

    /**********************************************************
    * Get the Capacity
    * ********************************************************/
    template<class T>
    int vector<T>::capacity() const
    {
        return numCapacity;
    }

    /**********************************************************
    * Check to see if the vector is empty
    * ********************************************************/
    template<class T>
    bool vector<T>::empty() const
    {
        return (numElements == 0) ? true : false;
    }

    /**********************************************************
    * Check to see if the vector is empty
    * ********************************************************/
    template<class T>
    void vector<T>::clear()
    {
        numElements = 0;
    }

    /**********************************************************
    * This Function will add the values to the buffer
    * ********************************************************/
    template<class T>
    void vector<T>::push_back(const T& t)
    {
        if (numCapacity == 0)
        {
            resize(1);
        }

        if (size() >= capacity()) //This will double the value of the capacity
        {
            resize(capacity() * 2);
        }
        

        buffer[numElements] = t;
        numElements++;


    }

    /**********************************************************
    * This Function will give the index of the vector (buffer)
    * ********************************************************/
    template<class T>
    T& vector<T>::operator[](const int index)
    {
        if( 0 <= index && index < numElements)
        {
            return buffer[index];
        }
        throw "Error: indices must be greater than zero and less than size().";
    }

    /**********************************************************
    * Iterator Begin implementation get the info of the Vector
    * ********************************************************/
    template<class T>
    typename vector<T>::iterator vector<T>::begin()
    {
        return iterator(buffer);

    }

    /**********************************************************
    * Iterator end implementation get the info of the Vector
    * ********************************************************/
    template<class T>
    typename vector<T>::iterator vector<T>::end()
    {
        return iterator(buffer + numElements);

    }

    /**********************************************************
    * RESIZE THE VECTOR
    * ********************************************************/
    template<class T>
    void vector<T>::resize(int newSize)
    {

        if (newSize < 0)
        {
            return;
        }

        //make array
        T* newBuffer = new T[newSize];

        numCapacity = newSize;

        //make sure capacity is bigger than new size
        if (numCapacity < numElements)
        {
            numElements = numCapacity;
        }  

        for (int i = 0; i < numElements; i++)
        {
            newBuffer[i] = buffer[i];
        }

        delete[] buffer;

        if (newSize == 0)
        {
            numCapacity = 0;
            numElements = 0;
            newBuffer = NULL;
        }
        
        buffer = newBuffer;
    }


    /********************************************************************************************
    * IMPLEMENTATION OF THE ITERATOR 
    * *******************************************************************************************/
    /**********************************************************
    * Interator Default Iterator
    * ********************************************************/
    template<class T>
    vector<T>::iterator::iterator()
    {
        ptr = NULL;
    }

    /**********************************************************
    * Noun Default Iterator
    * ********************************************************/
    template<class T>
    vector<T>::iterator::iterator(T *p)
    {
        ptr = p;
    }

    /**********************************************************
    * Copy Constructor
    * ********************************************************/    
    template<class T>
    vector<T>::iterator::iterator(const iterator& it)
    {
        *this = it;
    }

    /**********************************************************
    * The assignment opertator =
    * ********************************************************/
    template<class T>
    typename vector<T>::iterator& vector<T>::iterator::operator=(const iterator& it)
    {
        ptr = it.ptr;
    }

    /**********************************************************
    * The coomparation Operator ==
    * ********************************************************/
    template<class T>
    bool vector<T>::iterator::operator==(const iterator& it) const
    {
        return ptr == it.ptr;
    }

    /**********************************************************
    * The coomparation Operator !=
    * ********************************************************/
    template<class T>
    bool vector<T>::iterator::operator!=(const iterator& it) const
    {
        return (ptr != it.ptr);
    }

    /**********************************************************
    * PRE-FIX OPERATOR ++
    * ********************************************************/
    template<class T>
    typename vector<T>::iterator& vector<T>::iterator::operator++()
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
    template<class T>
    typename vector<T>::iterator& vector<T>::iterator::operator--()
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
    template<class T>
    typename vector<T>::iterator vector<T>::iterator::operator++(int postfix)
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
    template<class T>
    typename vector<T>::iterator vector<T>::iterator::operator--(int postfix)
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
    template<class T>
    T& vector<T>::iterator::operator*() const
    {
        return *ptr;
    }

}

#endif