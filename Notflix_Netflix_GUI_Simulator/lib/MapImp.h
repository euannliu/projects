#include "Map.h"
using namespace std;

template<class keyType, class valueType>
Map<keyType, valueType>::Map()
{
	head=NULL;
	tail=NULL;
	there=head;
	num=0;
}

template<class keyType, class valueType>
Map<keyType, valueType>::Map(const Map<keyType, valueType> & other)
{
	head=NULL;
	tail=NULL;
	there=head;
	num=0;
	merge(other);
}

template<class keyType, class valueType>
Map<keyType, valueType>& Map<keyType, valueType>::operator = (const Map<keyType, valueType> & other)
{
	head=NULL;
	tail=NULL;
	there=head;
	num=0;
	merge(other);
}

template<class keyType, class valueType>
Map<keyType, valueType>::~Map()
{
	MapItem<keyType,valueType> *temp1, *temp2;
	if(num==2)
	{
		temp1=head->next;
		delete temp1;
		num=1;
	}
	if(num>2)
	{
		temp1=head->next;
		temp2=temp1->next;
		while(temp2!=NULL)
		{
			delete temp1;
			temp1=temp2;
			temp2=temp2->next;
		}
		num=1;
	}
	if(num==1)
	{
		delete head;
	}
}

template<class keyType, class valueType>
int Map<keyType, valueType>::size () const
{
	return num;
}

template<class keyType, class valueType>
void Map<keyType, valueType>::add (keyType key, valueType value)
{
	MapItem<keyType,valueType> *temp=NULL, *newitem=NULL;
	bool check = true; //true if there is no matching key, false if there is
	temp=head;
	for(int i=0;i<num;i++)
	{
		if(temp->key==key)
		{
			check=false;
			break;
		}
		else
		{
			temp=temp->next;
		}
	}

	if(check)
	{
		newitem = new MapItem<keyType,valueType>;
		newitem->key=key;
		newitem->value=value;
		newitem->next=head;
		head=newitem;
		num++;
	}
}

template<class keyType, class valueType>
void Map<keyType, valueType>::remove (keyType key)
{
	if(num>0)
	{
		MapItem<keyType,valueType> *temp1=NULL, *temp2=NULL; //temp1 refers to current item | temp 2 refers to previous item
		temp1=head;
		if(temp1->key==key) //If the head has the matching key
		{
			if(num<3)
			{
				if(num==2)
				{
					head=head->next;
				}
				delete temp1;
				num--;
			}
		}
		else
		{
			temp2=temp1;
			temp1=temp1->next;
			for(int i=0;i<num;i++)
			{
				if(temp1->key==key)
				{
					temp2->next = temp1->next;
					delete temp1;
					num--;
					break;
				}
				else
				{
					temp2=temp1;
					temp1=temp1->next;
				}
			}
		}
	}
}

template<class keyType, class valueType>
void Map<keyType, valueType>::merge (const Map<keyType, valueType> & other)
{
	MapItem<keyType,valueType> *temp1=NULL, *temp2=NULL; //temp1 for this and temp2 for other
	bool check;
	//temp2 = new MapItem<keyType,valueType>;
	temp2=other.head;
	//Go through other's array first
	for(int y=0;y<other.size();y++)
	{
		check=true; //check is to see if there is a matching key in both lists
		temp1=head;
		//Go through this' array
		for(int x=0;x<num;x++)
		{
			if(temp2->key==temp1->key)
			{
				check=false; //check becomes false when there is a matching key in both lists
				break;
			}
			else
			{
				temp1=temp1->next;
			}
		}
		if(check) //if there are no matching keys, add the missing key to this list
		{
			add(temp2->key,temp2->value);
		}
		temp2=temp2->next;
	}
}



