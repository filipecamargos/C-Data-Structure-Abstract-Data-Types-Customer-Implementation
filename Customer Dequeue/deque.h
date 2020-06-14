#ifndef DEQUE_H
#define DEQUE_H
#ifdef UNIT_TESTING_
int main(int argc, const char** argv);
#endif

#include <cstddef>
#include <iostream>
#include <string>

//no inline implementations!
namespace custom
{
    template <class T>
    class deque
    {   
        /*public: 
        #ifdef UNIT_TESTING
                friend int  ::main(int argc, const char* argv[]);
        #endif*/
    //This  would be private but the is a problem with the files provided if we make main a friend and it private it won't compile
    public:
        T *buffer;
        int iFront;
        int iBack;
        int numCapacity;

        deque();
        deque(const int newCapacity);
        deque(const deque<T>& rhs);
        ~deque();

        deque<T>& operator=(const T& rhs);
        int size() const;
        int capacity() const;
        bool empty() const;
        void clear();
        void push_front(const T& t);
        void push_back(const T& t);
        void pop_front();
        void pop_back();
        T& front();
        T& back();
        void resize(const int newCapacity);
        int iFrontNormalize() const;
        int iBackNormalize() const;
        int iNormalize(const int t) const;
       
    };
    /*******************************************************
    * CONSTRUCTORS
    * *****************************************************/
    /*************************************
    * DEFAULT CONSTRUCTOR
    * ***********************************/
    template<class T>
    deque<T>::deque()
    {
        buffer = NULL;
        iFront = 0;
        iBack = -1;
        numCapacity = 0;

    }

    /*************************************
    * NONe DEFAULT CONSTRUCTOR
    * ***********************************/
    template<class T>
    deque<T>::deque(const int newCapacity)
    {
        this->numCapacity = newCapacity;
        if(numCapacity <= 0)
        {
            numCapacity = 0;
            throw "Error: deque sizes must be greater than or equal to 0.";
        }

        buffer = new T[numCapacity];
        iFront = 0;
        iBack = -1;

        for(int i = 0; i < numCapacity; i++)
        {
            buffer[i] = 0;
        }
    }

    /*************************************
    * Copy Constructor
    * ***********************************/
    template<class T>
    deque<T>::deque(const deque<T>& rhs)
    {
        clear();
        if (rhs.numCapacity <= 0)
        {
            throw "Error: deque is empty.";
        }


        iBack = -1;
        iFront = 0;
        numCapacity = rhs.size();
        buffer = new T[numCapacity];
     
        int j = rhs.iFrontNormalize();
        for( int i = 0; i < numCapacity; i++)
        {
            buffer[i] = rhs.buffer[j];
            j++;
            iBack++;
        }
        
    }

    /*************************************
    * Delet the Buffer
    * ***********************************/ 
    template<class T>
    deque<T>::~deque()
    {
        delete [] buffer;
    }

    /*************************************
    * Assign Operator
    * ***********************************/
    template<class T>
    deque<T>& deque<T>::operator=(const T& rhs)
    {
        clear();
        if (numCapacity < rhs.size())
        {
            resize(rhs.size());
        }

        for(int i = rhs.iFront; i < rhs.iBack; i ++)
        {
            push_back(rhs.buffer[iNormalize(i)]);
        }
        return *this;
    }

    /*************************************
    * Return the Size of the Class
    * ***********************************/
    template<class T>
    int deque<T>::size() const
    {
        return iBack - (iFront) +1;
    }

    /*************************************
    * Return the Capacity
    * ***********************************/
    template<class T>
    int deque<T>::capacity() const
    {
        return numCapacity;
    }

    /*************************************
    * Rerturn True if it is empty
    * ***********************************/
    template<class T>
    bool deque<T>::empty() const
    {
        return size() == 0;
    }

    /*************************************
    * Clear in a way that the buffer is 
    * not returning values
    * ***********************************/
    template<class T>
    void deque<T>::clear()
    {
        iFront = 0;
        iBack = -1;
    }

    /*************************************
    * Push an Item to the front of the 
    * Buffer
    * ***********************************/
    template<class T>
    void deque<T>::push_front(const T& t)
    {
        if (numCapacity == 0)
        {
            resize(1);
        }

        if (size() == capacity())
        {
            resize(numCapacity * 2);
        }

        iFront--;
        buffer[iFrontNormalize()] = t;
    }

    /*************************************
    * Push an item in the Back of the 
    * buffer
    * ***********************************/
    template<class T>
    void deque<T>::push_back(const T& t)
    {
        if (numCapacity <= 0)
        {
            resize(1);
        }

        if (size() == capacity())
        {
            resize(numCapacity * 2);
        }

        iBack++;
        buffer[iBackNormalize()] = t;
    }

    /*************************************
    * Take an item out of the front
    * ***********************************/
    template<class T>
    void deque<T>::pop_front()
    {
        if(empty())
        {
            throw "Error: Can not pop an empty deque.";
        }
        iFront++;
        
    }

    /*************************************
    * Take an item of the back
    * ***********************************/
    template<class T>
    void deque<T>::pop_back()
    {
        if(empty())
        {
            throw "Error: Can not pop an empty deque.";
        }
        iBack--;
    }

    /*************************************
    * Return the first value of the front
    * ***********************************/
    template<class T>
    T& deque<T>::front()
    {
        if (empty())
        {
            throw "Error: deque is empty.";
        }
        else
        {
            return buffer[iFrontNormalize()];
        }
        
    }

    /*************************************
    * Return the first value of the back
    * ***********************************/
    template<class T>
    T& deque<T>::back()
    {
        if (empty())
        {
            throw "Error: deque is empty.";
        }
        else
        {
            return buffer[iBackNormalize()];
        }
    }

    /*************************************
    * Resize the the buffer and copy the 
    * intem into it
    * ***********************************/
    template<class T>
    void deque<T>::resize(const int newSize)
    {
        if (newSize <= 0)
        {
            numCapacity = 0;
            iBack = -1;
            iFront = 0;
            buffer = NULL;

            return;
        }

        int newBack = -1;
        T* tempArray = new T[newSize];
        int numElements;
        
        //Think about the buffer as if it small then you want just to copy the numbers that are left
        if(newSize < size())
        {
            numElements = newSize;
        }
        else
        {
            numElements = size();
        }

        for( int i = 0; i < numElements; i++)
        {
            tempArray[i] = buffer[iFrontNormalize()];
            pop_front();
            newBack++;
        }

        delete [] buffer;

        iBack = newBack;
        iFront = 0;
        numCapacity = newSize;
        buffer = tempArray;

    }

    /*************************************
    * Normalize to get the proper
    * inder of the front
    * ***********************************/
    template<class T>
    int deque<T>::iFrontNormalize() const
    {
        return iNormalize(iFront);
    }

    /*************************************
    * normalize to take the last index
    * of the buffer
    * ***********************************/
    template<class T>
    int deque<T>::iBackNormalize() const
    {
        return iNormalize(iBack);
    }

    /*************************************
    * Used for to normalize and provide 
    * support to get the index of the two 
    * function before
    * ***********************************/
    template<class T>
    int deque<T>::iNormalize(const int t) const
    {   
        if (numCapacity == 0)
        {
            throw "Error: uninitialized deque.";
        }

        int normalize = t % numCapacity;

        while(normalize < 0)
        {
            normalize += numCapacity;
        }

        return normalize;
    }

};

#endif