#ifndef QUEUE_H
#define QUEUE_H
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
    class queue
    {   
        /*public: 
        #ifdef UNIT_TESTING
                friend int  ::main(int argc, const char* argv[]);
        #endif*/
    //This  would be private but the is a problem with the files provided if we make main a friend and it private it won't compile
    public:
        T *buffer;
        long int numPush;
        long int numPop;
        long int numCapacity;

        queue();
        queue(const int numCapacity);
        queue(const queue<T>& rhs);
        ~queue();

        queue<T>& operator=(const queue<T>& rhs);
        int size() const;
        int capacity() const;
        bool empty() const;
        void clear();
        void push(const T& t);
        void pop();
        T& front() const;
        T& back() const;

        void resize(int newSize);
        int iHead() const;
        int iTail() const;
    };

    /*******************************************************
    * CONSTRUCTORS
    * *****************************************************/
    /*************************************
    * DEFAULT CONSTRUCTOR
    * ***********************************/
    template<class T>
    queue<T>::queue()
    {
        buffer = NULL;
        numPush = 0;
        numPop = 0;
        numCapacity = 0;
    }

    /*************************************
    * NO DEFAULT CONSTRUCTOR
    * ***********************************/
    template<class T>
    queue<T>::queue(const int numCapacity)
    {
        if(numCapacity <= 0)
        {
            throw "Error: set sizes must be greater than or equal to 0.";
        }

        this->numCapacity = numCapacity;
        buffer = new T[numCapacity];
        numPush = 0;
        numPop = 0;

        for(int i = 0; i < numCapacity; i++)
        {
            buffer[i] = 0;
        }

    }

    /*************************************
    * NO DEFAULT CONSTRUCTOR
    * ***********************************/
    template<class T>
    queue<T>::queue(const queue<T>& rhs)
    {
        numCapacity = rhs.size();

        buffer = new T[numCapacity];
        if (rhs.numCapacity <= 0)
        {
            throw "Error: attempting to assign a queue with invalid size";
        }

        int j = rhs.iHead();
        for (int i = 0; i < numCapacity; i++)
        {
            buffer[i] = rhs.buffer[j];
            j = (j + 1) % rhs.capacity();
        }

        numPush = rhs.size();
        numPop = 0;
       
        /*this->numCapacity = rhs.numCapacity;
        this->numPush = rhs.numPush;
        this->numPop = rhs.numPop;

        buffer = new T[numCapacity];

        for(int i = 0; i < numCapacity; i++)
        {
            buffer[i] = rhs.buffer[i];
        }*/

    }

    /*************************************
    * DESTRUCTOR
    * ***********************************/
    template<class T>
    queue<T>::~queue()
    {
        delete [] buffer;
    }

    /*************************************
    * ASSIGNMENT OVERLOAD
    * ***********************************/
    template <class T>
    queue<T>& queue<T>::operator=(const queue<T>& rhs)
    {

        numCapacity = rhs.size();

        buffer = new T[numCapacity];
        if (rhs.numCapacity <= 0)
        {
            throw "Error: attempting to assign a queue with invalid size";
        }

        int j = rhs.iHead();
        for (int i = 0; i < numCapacity; i++)
        {
            buffer[i] = rhs.buffer[j];
            j = (j + 1) % rhs.capacity();
        }

        numPush = rhs.size();
        numPop = 0;

        return *this;
        /*delete []  buffer;

        if(rhs.numCapacity > this->numCapacity)
        {
            resize(rhs.size());
        }

        else if(rhs.size() == 0)
        {
            numCapacity = 0;
            numPop = 0;
            numPush = 0;
            buffer = NULL;

        }

        numPop = rhs.numPop;
        numPush = rhs.numPush;
        int numElements = rhs.size();

        for(int i = 0; i < numElements; i++, numPop++)
        {
            buffer[i] = rhs.buffer[iHead()];
        }

        numPop = rhs.numPop;
        numPush = rhs.numPush;

        

        /*for(int i = 0; i < rhs.size(); i++)
        {
            buffer[i] = rhs.buffer[i];
        }
        */
    
    }

    /*************************************
    * GET SIZE
    * ***********************************/
    template<class T>
    int queue<T>::size() const
    {
        return (numPush - numPop);
    }

    /*************************************
    * CLEAR THE QUEUE
    * ***********************************/
    template<class T>
    void queue<T>::clear()
    {
        numPop = 0;
        numPush = 0;
    }

    /*************************************
    * GET CAPACITY
    * ***********************************/
    template<class T>
    int queue<T>::capacity() const
    {
        return numCapacity;
      
    }

    /*************************************
    * CHECK IF IT IS EMPTY
    * ***********************************/
    template<class T>
    bool queue<T>::empty() const
    {
        if(numPush == numPop)
        {
            return true;
        }
        else
        {
            return false;
        }
    }    

    /*************************************
    * PUSH TO THE END
    * ***********************************/
    template<class T>
    void queue<T>::push(const T& t)
    {
        if (numCapacity == 0)
        {
            resize(1);
        }

        if (size() >= capacity()) //This will double the value of the capacity
        {
            resize(capacity() * 2);
        }

        numPush++;
        buffer[iTail()] = t;
      
        
    }

    /*************************************
    * POP ELEMENT OUT OF THE FRONT
    * ***********************************/
    template<class T>
    void queue<T>::pop()
    {

        if(empty())
        {
           return;
        }
        numPop++;
    }  

    /*************************************
    * RETURN THE FRONT
    * ***********************************/
    template<class T>
    T& queue<T>::front() const
    {   
        if(empty())
        {
            throw "Error: asking for front of empty queue.";
        }
        else
        {
            return buffer[iHead()];
        }
    }  

    /*************************************
    * RETURN THE BACK
    * ***********************************/
    template<class T>
    T& queue<T>::back() const
    {
        if(empty())
        {
            throw "Error: asking for back of empty queue.";
        }
        else
        {
            return buffer[iTail()];
        }
        
    }  

    /*************************************
    * RESIZE THE BUFFER BIG CAPACITY
    * ***********************************/
    template<class T>
    void queue<T>::resize(int newSize)
    {   
        if (newSize <= 0)
        {
            numCapacity = 0;
            numPop = 0;
            numPush = 0;
            buffer = NULL;

            return;
        }

        T* tempArray = new T[newSize];
        int numElements = size();

        if(newSize < size())
        {
            numElements = newSize;
        }       

        for(int i = 0; i < numElements; i++, numPop++)
        {
            tempArray[i] = buffer[iHead()];
        }

        delete[] buffer;

        numPush = numElements;
        numPop = 0;
        numCapacity = newSize;
        buffer = tempArray;


    }  

    /*************************************
    * KEEP TRACK OF THE HEAD ELEMENT
    * ***********************************/
    template<class T>
    int queue<T>::iHead() const
    {
        return (numPop) % numCapacity;
    }

    /*************************************
    * KEEP TRACK OF THE TAIL ELEMENT
    * ***********************************/
    template<class T>
    int queue<T>::iTail() const
    {
        return (numPush - 1) % numCapacity; 
    } 

};

#endif