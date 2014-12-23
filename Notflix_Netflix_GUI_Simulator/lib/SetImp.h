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
	internalStorage.add(item,0);
}

template<class T>
void Set<T>::remove(const T item)
{
	internalStorage.remove(item);
}

template<class T>
bool Set<T>::contains(T item)
{
	return internalStorage.search(item);
}

template<class T>
void Set<T>::merge(const Set<T> & other)
{
	Map<T,int> temp;
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

