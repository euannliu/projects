#ifndef MAP_H
#define MAP_H
#include <iostream>
#include "rbbst.h"
using namespace std;


class NoSuchElementException : public exception
{
	public:
		const char * Message()
		{
			return "No Such Element";
		}
};

template <class keyType, class valueType>
struct MapItem
{
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev, *next;
  
};

template <class FirstType, class SecondType> 
struct Pair {
   FirstType first;
   SecondType second;

   Pair() {};
   Pair (FirstType first, SecondType second)
      { this->first = first; this->second = second; }
   // we're very nice and give you this piece of difficult code for free :-P
};

template <class keyType, class valueType>
class Map
{
public:
	Map();
	Map(const Map<keyType, valueType> & other);
	~Map();
	int size () const;
	void add (keyType key, valueType value); 
	void remove (keyType key);
	void merge (const Map<keyType, valueType> & other);
	
	bool search (keyType key);

	Map& operator = (const Map &other);
	
	class Iterator 
	{
        public:
        	Iterator()
        	{
        		iter.curr = NULL;
        		temp_it = NULL;
        	/*
        		iter = new typename RedBlackTree<keyType, valueType>::iterator(NULL);
        		temp_it = new typename  RedBlackTree<keyType, valueType>::iterator(NULL);
        	*/
        	}
        	Iterator(typename RedBlackTree<keyType, valueType>::iterator other)
        	{
        		//temp_it = new typename  RedBlackTree<keyType, valueType>::iterator(NULL);
        		//iter = new typename  RedBlackTree<keyType, valueType>::iterator(NULL);
        		iter = other;
        		temp_it = NULL;
        	}
        	~Iterator()
        	{
        		//delete iter;
        		//delete temp_it;
        	}
          	Pair<keyType, valueType> operator* () const
          	{
          		pair<keyType, valueType> std_pair;
          		Pair<keyType, valueType> temp_pair;
          		
          		if(iter!=temp_it)
		  	{
		  		std_pair = *iter;
		  		
		  		temp_pair.first = std_pair.first;
	      			temp_pair.second = std_pair.second;
	      		}
       			return temp_pair;
           	}
           	
          	Map<keyType,valueType>::Iterator operator++ ()
          	{
          		++iter;
          		if(iter.curr == NULL)
          			throw NoSuchElementException();
          			
          		return *this;
          	}
          	
          	Map<keyType,valueType>::Iterator operator= (const typename RedBlackTree<keyType, valueType>::iterator & other)
          	{
          		if(RedBlackTree<keyType, valueType>::iter.curr!=other.curr)
          		{
		  		iter.curr = other.curr;
		  	}
          		return *this; 
          	}

         	bool operator== (const typename RedBlackTree<keyType, valueType>::iterator & other) const 
            	{
            		if(iter.curr==other.curr)
            			return true;
            		else
            			return false;
            	}
            	
            	bool operator!= (const typename RedBlackTree<keyType, valueType>::iterator & other) const
         	{
            		if(iter.curr==other.curr)
            			return false;
            		else
            			return true;
            	}
            	
              	//MapItem<keyType,valueType> *it_pos;
		typename RedBlackTree<keyType, valueType>::iterator iter;
		typename RedBlackTree<keyType, valueType>::iterator temp_it;
	};

	Map<keyType,valueType>::Iterator begin () const
	{
		return Map<keyType,valueType>::Iterator(bank->begin());
	}
	Map<keyType,valueType>::Iterator end () const
	{
		return Map<keyType,valueType>::Iterator();
	}
        
private:
	RedBlackTree<keyType, valueType> *bank;
	MapItem <keyType, valueType> *head, *tail, *there;

	int num; //How many items are currently in this linked list
};
#include "MapImp.h"
#endif

