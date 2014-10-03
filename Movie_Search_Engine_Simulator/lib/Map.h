#ifndef MAP_H
#define MAP_H
#include <iostream>
using namespace std;

template <class keyType, class valueType>
struct MapItem
{
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev, *next;
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
	const valueType & get (const keyType & key) const;
	void merge (const Map<keyType, valueType> & other);

	void first();
	void next();
	const keyType & getCurrentKey();
	const valueType & getCurrentValue();
	Map& operator = (const Map &other);

private:
	MapItem <keyType, valueType> *head, *tail, *there;
	int num; //How many items are currently in this linked list
};

class NoSuchElementException : public exception
{
	public:
		const char * Message()
		{
			return "No Such Element";
		}
};
#include "MapImp.h"
#endif
