#include "Set.h"
using namespace std;
template<class T>
Set<T>::Set()
{
	index=0;
}

template<class T>
Set<T>::Set(const Set<T> & other)
{
	index=0;
	merge(other);
}

template<class T>
Set<T>::~Set()
{
	
}

template<class T>
Set<T>& Set<T>::operator= (const Set<T> &other)
{
	index=0;
	merge(other);
}


template<class T>
void Set<T>::first()
{
	internalStorage.first();
}

template<class T>
void Set<T>::next()
{
	internalStorage.next();
}

template<class T>
const T& Set<T>::getCurrent()
{
	internalStorage.getCurrentValue();
}

template<class T>
int Set<T>::size() const
{
	return internalStorage.size();
}

template<class T>
void Set<T>::add(const T item)
{
	bool isin = false;
	for(int i=0;i<index;i++) //Check to see if there is the item is in the bank
	{
		if(internalStorage.get(i)==item)
		{
			isin=true;
			break;
		}
	}
	if(!isin)
	{
		internalStorage.add(index,item);
		index++;
	}
}

template<class T>
void Set<T>::remove(const T item)
{
	int current=-1;
	T hold;
	for(int i=0;i<index;i++) //Check to see if there is the item is in the bank
	{
		if(internalStorage.get(i)==item)
		{
			current=i; //pulls the index of that item
			break;
		}
	}
	if(current>=0) //if there is an item...
	{
		internalStorage.remove(current); //remove that item
		for(int i=current+1;i<index;i++) //shift all the index of the next items back one
		{
			hold=internalStorage.get(i);
			internalStorage.remove(i);
			internalStorage.add(i-1,hold);
		}
		index--;
	}
}

template<class T>
bool Set<T>::contains(T item) const
{
	bool success=false;
	for(int i=0;i<index;i++) //search by value
	{
		if(internalStorage.get(i)==item)
		{
			success=true; 
			break;
		}
	}
	return success;
}

template<class T>
T Set<T>::extract(int index_num) const
{
	return internalStorage.get(index_num);
}

template<class T>
void Set<T>::merge(const Set<T> & other)
{
	Map<int,T> temp;
	int total=other.size();
	T hold;
	for(int i=0;i<other.size();i++)
	{
		hold=other.extract(i);
		temp.add(i+index,hold); 
	}
	internalStorage.merge(temp);
	index+=total;
}

template <class T>
Set<T> Set<T>::Union (const Set<T> & other) const
{
	Set<T> temp;
	temp.merge(this);
	temp.merge(other);
	return temp;
}

template <class T>
Set<T> Set<T>::Intersection (const Set<T> & other) const
{
	Set<T> temp;
	for(int i=0;i<size();i++)
	{
		for(int j=0;j<other.size;j++)
		{
			if(extract(i)==other.extract(j))
			{
				temp.add(extract(i));
			}
		}
	}
	return temp;
}

