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
	~Map();
	int size () const;
	void add (keyType key, valueType value); 
	void remove (keyType key);
	valueType get (keyType key, bool & success) const;
	void merge (const Map<keyType, valueType> & other);
private:
	MapItem <keyType, valueType> *head, *tail;
	int num; //How many items are currently in this linked list
};

#include "MapImp.h"
#endif