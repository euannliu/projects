#ifndef MAP_H
#define MAP_H
#include <iostream>
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

	Map& operator = (const Map &other);
	
	class Iterator 
	{
        public:
        	Iterator()
        	{
        		it_pos = NULL;
        	}
        	Iterator(MapItem<keyType,valueType> *other)
        	{
        		it_pos = other;
        	}
        		
          	Pair<keyType, valueType> operator* () const
          	{
          		Pair<keyType, valueType> temp_pair;
          		temp_pair.first = it_pos->key;
      			temp_pair.second = it_pos->value;
       			return temp_pair;
           	}
           	
          	Map<keyType,valueType>::Iterator operator++ ()
          	{
          		if(it_pos->next==NULL)
          			throw NoSuchElementException();
          		else
          			it_pos = it_pos->next;
          			
          		return *this;
          	}
          	
          	Map<keyType,valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other)
          	{
          		if(it_pos!=other.it_pos)
          		{
		  		it_pos = other.it_pos;
		  	}
          		return *this; 
          	}

         	bool operator== (const Map<keyType,valueType>::Iterator & other) const 
            	{
            		if(it_pos==other.it_pos)
            			return true;
            		else
            			return false;
            	}
            	
            	bool operator!= (const Map<keyType,valueType>::Iterator & other) const
         	{
            		if(it_pos==other.it_pos)
            			return false;
            		else
            			return true;
            	}
            	
              	MapItem<keyType,valueType> *it_pos;

	};

	Map<keyType,valueType>::Iterator begin () const
	{
		return Map<keyType,valueType>::Iterator(head);
	}
	Map<keyType,valueType>::Iterator end () const
	{
		return Map<keyType,valueType>::Iterator(NULL);
	}
        
private:
	MapItem <keyType, valueType> *head, *tail, *there;

	int num; //How many items are currently in this linked list
};
#include "MapImp.h"
#endif

