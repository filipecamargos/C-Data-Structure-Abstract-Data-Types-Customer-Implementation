#ifndef STACK_h
#define STACK_H
#ifdef UNIT_TESTING_
int main(int argc, const char** argv);
#endif

#include <cstddef>
#include <iostream>
#include <string>

//no inline implementations!
namespace custom
{
    /***********Our Stack Class****************/
    template <class T>
    class stack
    {
        public: //This  would be private but the is a problem with the files provided if we make main a friend and it private it won't compile
        T *buffer;
        int numElements;
        int numCapacity;

        public:
        stack();
        stack(const int numCapacity);
        stack(const stack<T>& rhs);
        ~stack();

        stack<T>& operator=(const stack<T>& rhs);
        int size() const;
        int capacity() const;
        bool empty() const;
        void clear();
        void push(const T& t);
        void pop();
        T& top();
        //const T& top() const;

        void resize(int newSize);
    };

    /********************************************************************************************
    * IMPLEMENTATION OF THE FUNCTIONS FOR THE STACK
    * *******************************************************************************************/
        /************************************************
    * DEFAULT CONSTRUCTOR
    * **********************************************/
    template<class T>
    custom::stack<T>::stack()
    {
        buffer = NULL;
        numElements = 0; //Number of elements in the array 
        numCapacity = 0; //Capacity that is there
    }

    /************************************************
   * NO DEFAULT - determine the buffer size
    * **********************************************/
    template<class T>
    stack<T>::stack(const int numCapacity)
    {
        //Check for invalid numbers
        if(numCapacity <= 0)
        {
            throw "Error: vector sizes must be greater than 0.";
        }

        this->numElements = 0;
        this->numCapacity = numCapacity;
        this->buffer = new T[numCapacity];

        //Initiate Everyhting to 0
        for (int i = 0; i < numCapacity; i++)
        {
            this->buffer[i] = 0;
        }
    }


    /**********************************************************
    * COPY CONSTRUCTOR
    * ********************************************************/
    template <class T>
    stack<T>::stack(const stack<T>& rhs)
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
    stack<T>::~stack()
    {
        delete [] buffer;
    }

    /**********************************************************
    * Assigne operator which will assing value of stack
    * ********************************************************/
    template <class T>
    stack<T>& stack<T>::operator=(const stack<T>& rhs)
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
     *
    * Get the Size
    * ********************************************************/
    template<class T>
    int stack<T>::size() const
    {
        return numElements;
    }

    /**********************************************************
    * Get the Stack
    * ********************************************************/
    template<class T>
    int stack<T>::capacity() const
    {
        return numCapacity;
    }

    /**********************************************************
    * Check to see if the Stack is empty
    * ********************************************************/
    template<class T>
    bool stack<T>::empty() const
    {
        return (numElements == 0) ? true : false;
    }

    /**********************************************************
    * Check to see if the Stack is empty
    * ********************************************************/
    template<class T>
    void stack<T>::clear()
    {
        numElements = 0;
    }

    /**********************************************************
    * 
    * ********************************************************/
    template<class T>
    void stack<T>::push(const T& t)
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
    * 
    * ********************************************************/
    template<class T>
    void stack<T>::pop()
    {
        if(!empty())
        {
            --numElements;
        }
    }

    /**********************************************************
    * 
    * ********************************************************/
    template<class T>
    T& stack<T>::top()
    {  
        if (empty())
        {
            throw "Error: asking for top of empty stack.";           
        }

        return buffer[numElements -1];

    }

    /**********************************************************
    * 
    * ********************************************************/
    /*template<class T>
    const T& stack<T>::top() const
    {
 
        
    }*/

    /**********************************************************
    * RESIZE THE VECTOR
    * ********************************************************/
    template<class T>
    void stack<T>::resize(int newSize)
    {

        if (newSize < 0)
        {
            return;
        }

        //make array
        T* tempArray = new T[newSize];

        numCapacity = newSize;

        //make sure capacity is bigger than new size
        if (numCapacity < numElements)
        {
            numElements = numCapacity;
        }  

        for (int i = 0; i < numElements; i++)
        {
            tempArray[i] = buffer[i];
        }

        delete[] buffer;

        if (newSize == 0)
        {
            numCapacity = 0;
            numElements = 0;
            tempArray = NULL;
        }
        
        buffer = tempArray;
    }

};

#endif