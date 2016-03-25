/***********************************************************************
* Header:
*    Lesson 02, Stack
*    Br. Helfrich, CS 235
* Summary:
*    This class contains the notion of a stack: a bucket to hold
*    data for the user. <Last In, First Out>
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Stack
* Author
*    Br. Helfrich & Jacob Casperson
************************************************************************/

#ifndef Stack_H
#define Stack_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class StackIterator;

/***********************************************************************
 * Vector
 * A class that holds stuff
************************************************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
  Stack() : numItems(0), limit(0), data(0x00000000){}   

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Stack(int limit) throw (const char *);
   
   // destructor : free everything
   ~Stack()        { if (limit) delete [] data; }
   
   // is the container currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the container
//   void clear()        { numItems = 0;                 }

   // how many items are currently in the container?
   int size() const    { return numItems;              }

   // add an item to the container
   void push(const T & t) throw (const char *);

   // remove an item off the container
   void pop();

   // show what's on top of the stack
   T top();

   // stack isn't big enough, so reallocate 
   void reallocateData();
   
   //how large is the capacity
   int capacity() const { return limit;           }

private:
   T * data;       // dynamically allocated array of T
   int numItems;   // how many items are currently in the Container?
   int limit;      // capacity. 
 
};

/***********************************************************************
 * Stack :: COPY CONSTRUCTOR
 ************************************************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.limit >= 0);
   
   // do nothing if there is nothing to do
   if (rhs.limit == 0)
   {
      limit = numItems = 0;
      data = 0x00000000;
      return;
   }
   
   // attempt to allocate
   try
   {
      data = new T[rhs.limit];
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the stuff
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.limit);
   limit = rhs.limit;
   numItems = rhs.numItems;
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];
}

/***********************************************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "capacity"
 ************************************************************************/
template <class T>
Stack <T> :: Stack(int limit) throw (const char *)
{
   assert(limit >= 0);
   
   // do nothing if there is nothing to do
   if (limit == 0)
   {
      this->limit = this->numItems = 0; //this->iTop = 0;
      this->data = 0x00000000;
      return;
   }
   
   // attempt to allocate
   try
   {
      data = new T[limit];
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate buffer";
   }
 
   // copy over the stuff
   this->limit = limit;
   this->numItems = 0;
   
}

/***********************************************************************
 * Stack:: Reallocate
 * stack isn't big enough so make it bigger
 ************************************************************************/
template<class T>
void Stack<T> :: reallocateData()
{
       //allocate new Stack or  attempt to allocate  
      limit *= 2;
      T * newData;

      // allocate size
      try
      {
         newData = new T[limit];
      }
      catch (...)
      {
         throw "ERROR: Unable to allocate buffer";
      }

      // copy the data into new stack
      int i;
      if (numItems != 0)
      {
         for (i = 0; i < numItems; i++)
         {
            newData[i] = data[i];
         }
         newData[i] = '\0';

         // delete the old stack
         delete [] data;
      }
      
      // rename our array
      data = newData;
}

/***********************************************************************
 * Stack:: TOP
 * Check to see what is on the top of the stack
 ************************************************************************/
template<class T>
T Stack<T> :: top()
{                
   if (numItems > 0)
      return data[numItems - 1];
   else
       throw "ERROR: Unable to reference the element from an empty Stack";     
}

/***********************************************************************
 * Stack:: REMOVE
 * Remove an item from the end of the stack
 * Increase the stack size when needed
 ************************************************************************/
template<class T>
void Stack<T> :: pop()
{
   if (numItems > 0)
      numItems--;       
   else
      throw "ERROR: Unable to pop from an empty Stack";   
}

/***********************************************************************
 * Stack:: INSERT
 * Insert an item from the end of the stack.
 * (In reality it just decrements the index on the stack
 ************************************************************************/
template <class T>
void Stack<T> :: push(const T & t) throw (const char *)
{
   // make sure we have some capacity
   if (limit == 0)
   {
      limit = 1;
   }
   
   // if the limit of the stack is reached increase the capacity
   if (limit <= (numItems + 1))
      reallocateData();
  
   
   // add an item to the end and increment the top
   data[numItems++] = t;
}

#endif // Stack_CONTAINER_H

/***********************************************************************
 * Square bracket operator overloading
 ************************************************************************
template <class T>
const T Stack<T>::operator [](const int& index) const
{
    return data[index];
}
*/
