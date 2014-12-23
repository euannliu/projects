#include "Map.h"
using namespace std;

template<class keyType, class valueType>
Map<keyType, valueType>::Map()
{
	bank = new RedBlackTree<keyType,valueType>;
	num=0;
}

template<class keyType, class valueType>
Map<keyType, valueType>::Map(const Map<keyType, valueType> & other)
{
	bank = new RedBlackTree<keyType,valueType>;
	num=0;
	merge(other);
}

template<class keyType, class valueType>
Map<keyType, valueType>& Map<keyType, valueType>::operator = (const Map<keyType, valueType> & other)
{
	bank = new RedBlackTree<keyType,valueType>;
	num=0;
	merge(other);
	return *this;
}

template<class keyType, class valueType>
Map<keyType, valueType>::~Map()
{
	delete bank;
}

template<class keyType, class valueType>
int Map<keyType, valueType>::size () const
{
	return num;
}

template<class keyType, class valueType>
void Map<keyType, valueType>::add (keyType key, valueType value)
{
	try
	{
		bank->lookup(key);
	}
	catch(KeyNotFoundException &e)
	{
	}
	
	bank->add(key,value);
	num++;
}

template<class keyType, class valueType>
void Map<keyType, valueType>::remove (keyType key)
{
	try
	{
		bank->lookup(key);
	}
	catch(KeyNotFoundException &e)
	{
	}
	
	bank->remove(key);
	num--;
}

template<class keyType, class valueType>
void Map<keyType, valueType>::merge (const Map<keyType, valueType> & other)
{
	Map<keyType, valueType>::Iterator o_it;
	Pair<keyType,valueType> temp_pair;
	o_it = other.begin();
	
	while(o_it.iter!=o_it.temp_it)
	{
		temp_pair = *o_it;
		add(temp_pair.first, temp_pair.second);
		try
		{
			++o_it;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}
}
template<class keyType, class valueType>
bool Map<keyType, valueType>::search (keyType key)
{
	try
	{
		bank->lookup(key);
	}
	catch(KeyNotFoundException &e)
	{
		return false;
	}
	return true;
}

