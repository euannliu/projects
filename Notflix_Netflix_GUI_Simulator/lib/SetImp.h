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
	return *this;
}

template<class T>
int Set<T>::size() const
{
	return internalStorage.size();
}

template<class T>
void Set<T>::add(const T item)
{
	Pair<int,T> thepair;
	typename Map<int,T>::Iterator iterate;
	iterate = internalStorage.begin();
	bool isin = false;
	for(int i=0;i<index;i++) //Check to see if there is the item is in the bank
	{
		thepair=*iterate;
		if(thepair.second==item)
		{
			isin=true;
			break;
		}
		try
		{
			++iterate;
		}
		catch(NoSuchElementException &e)
		{
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
	Pair<int,T> thepair;
	typename Map<int,T>::Iterator iterate;
	iterate = internalStorage.begin();
	int current=-1;
	T hold;
	for(int i=0;i<index;i++) //Check to see if there is the item is in the bank
	{
		thepair=*iterate;
		if(thepair.second==item)
		{
			current=thepair.first; //pulls the index of that item
			break;
		}
		try
		{
			++iterate;
		}
		catch(NoSuchElementException &e)
		{
		}
	}
	if(current>=0) //if there is an item...
	{
		internalStorage.remove(current); //remove that item
		iterate = internalStorage.begin();
		for(int i=current+1;i<index;i++) //shift all the index of the next items back one
		{
			thepair=*iterate;
			hold=thepair.second;
			internalStorage.remove(i);
			internalStorage.add(i-1,hold);
			try
			{
				++iterate;
			}
			catch(NoSuchElementException &e)
			{
			}
		}
		index--;
	}
}

template<class T>
bool Set<T>::contains(T item) const
{
	Pair<int,T> thepair;
	typename Map<int,T>::Iterator iterate;
	iterate = internalStorage.begin();
	bool success=false;
	for(int i=0;i<index;i++) //search by value
	{
		thepair = *iterate;
		if(thepair.second==item)
		{
			success=true; 
			break;
		}
		try
		{
			++iterate;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}
	return success;
}

template<class T>
void Set<T>::merge(const Set<T> & other)
{
	Map<int,T> temp;
	int total=other.size();
	T hold;
	Set<T>::Iterator iterate;
	iterate = other.begin();
	for(int i=0;i<other.size();i++)
	{
		hold=*iterate;
		temp.add(i+index,hold); 
		try
		{
			++iterate;
		}
		catch(NoSuchElementException &e)
		{
		}
	}
	internalStorage.merge(temp);
	index+=total;
}

template <class T>
Set<T> Set<T>::Union (const Set<T> & other) const
{
	vector<T> temp_vector;
	Set<T> temp_set;
	Set<T>::Iterator union_iterator;
	union_iterator = begin();
	while(size()>0)
	{
		temp_vector.push_back(*union_iterator);
		try
		{
			++union_iterator;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}
	union_iterator = other.begin();
	while(other.size()>0)
	{
		temp_vector.push_back(*union_iterator);
		try
		{
			++union_iterator;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}
	
	MergeSort<T> sorter;
	temp_vector = sorter.sort(temp_vector);
	
	for(int i=0; i<temp_vector.size(); i++)
	{
		temp_set.add(temp_vector[i]);
	}
	
	return temp_set;
}

template <class T>
Set<T> Set<T>::Intersection (const Set<T> & other) const
{
	vector<T> temp_vector;
	Set<T> temp_set;
	Set<T>::Iterator union_iterator;
	union_iterator = begin();
	while(size()>0)
	{
		temp_vector.push_back(*union_iterator);
		try
		{
			++union_iterator;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}
	union_iterator = other.begin();
	while(other.size()>0)
	{
		temp_vector.push_back(*union_iterator);
		try
		{
			++union_iterator;
		}
		catch(NoSuchElementException &e)
		{
			break;
		}
	}
	
	MergeSort<T> sorter;
	temp_vector = sorter.sort(temp_vector);

	for(int i=0; i<temp_vector.size(); i++)
	{
		if((temp_vector.size()>1) && (temp_vector[i]==temp_vector[i+1]))
			temp_set.add(temp_vector[i]);
	}
	
	return temp_set;
}

