#ifndef SET_H
#define SET_H
#include "Map.h"
#include "MergeSort.h"
template <class T>
class Set
{
  public:
    Set ();  // constructor for a new empty set
    Set (const Set<T> & other);
    ~Set (); // destructor

    int size () const; // returns the number of elements in the set
    void add (const T item); 
      /* Adds the item to the set.
         If the item is already in the set, it should do nothing.
      */
    void remove (const T item);
     /* Removes the item from the set.
        If the item was not in the set, it should do nothing. */
    bool contains (T item) const;
     /* Returns whether the item is in the set. */
    void merge (const Set<T> & other);
     /* Adds all elements of other to this set. 
        However, will not create duplicates, i.e., it ignores elements
        already in the set. */

     Set<T> Union (const Set<T> & other) const;
     Set<T> Intersection (const Set<T> & other) const;

	Set& operator = (const Set &other);

	class Iterator
	{
        public:
        	Iterator()
        	{
        		it = new typename Map<int, T>::Iterator(NULL);
        	}
        	Iterator(const Map<int, T> * storage, bool at_beginning) //at_beginning checks whether to call Map's Iterator's begin or end
        	{
        		iS_p = storage;
        		it = new typename Map<int, T>::Iterator;
        		if(at_beginning)
        			*it = storage->begin();
        		else
        			*it = storage->end();
        	}
        	
          	T operator* () const
          	{
          		Pair<int, T> *temp_pair;
          		temp_pair = new Pair<int, T>;
          		*temp_pair = **it;
          		return temp_pair->second;          		
          	}
          	Set<T>::Iterator operator++ ()
          	{
          		++*it; //this an issue?
          		return *this;
          	}
          	Set<T>::Iterator operator= (const Set<T>::Iterator & other)
          	{
          		it->it_pos = other.it->it_pos;
          		return *this;
          	}
         	bool operator== (const Set<T>::Iterator & other) const
         	{
            		if(it->it_pos==other.it->it_pos)
            			return true;
            		else
            			return false;
         	}
            	bool operator!= (const Set<T>::Iterator & other) const //FIX THIS
            	{
            		if(it->it_pos==other.it->it_pos)
            			return false;
            		else
            			return true;            	
            	}
            	
        private:
		typename Map<int, T>::Iterator *it;
		const Map<int, T> *iS_p;
	};

	Set<T>::Iterator begin () const
	{	
		return Iterator(&internalStorage, true);
	}
	
	Set<T>::Iterator end () const
	{
		return Iterator(&internalStorage, false);
	}

	friend class Set<T>::Iterator;
private:
	Map<int, T> internalStorage;
	int index;
};
#include "SetImp.h"
#endif
