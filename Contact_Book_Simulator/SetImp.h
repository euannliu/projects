#include "Set.h"
using namespace std;
template<class T>
Set<T>::Set()
{
	index=0;
}

template<class T>
Set<T>::~Set()
{
	
}

template<class T>
int Set<T>::size() const
{
	return internalStorage.size();
}

template<class T>
void Set<T>::add(T item)
{
	bool isin = false;
	bool success;
	for(int i=0;i<index;i++) //Check to see if there is the item is in the bank
	{
		if(internalStorage.get(i,success)==item)
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
void Set<T>::remove(T item)
{
	int current=-1;
	T hold;
	bool success;
	for(int i=0;i<index;i++) //Check to see if there is the item is in the bank
	{
		if(internalStorage.get(i,success)==item)
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
			hold=internalStorage.get(i,success);
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
	bool fake;
	for(int i=0;i<index;i++) //search by value
	{
		if(internalStorage.get(i,fake)==item)
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
	bool temp;
	return internalStorage.get(index_num,temp);
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

