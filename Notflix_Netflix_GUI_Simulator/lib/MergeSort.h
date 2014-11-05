#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
using namespace std;

template <class T>
class MergeSort 
{
	static void Merge(vector<T> &a, int first, int last, int newlast)
	{
		int i = first, j = newlast + 1, k = 0;
		const int size = last - first + 1;
		double *temp;
		temp = new double[size];
		while (i <= newlast || j <= last)
		{
			if (((a[i] <= a[j]) || (j > last)) && (i <= newlast))	
			{
				temp[k] = a[i];
				i++;
				k++;
			}
			else
			{
				temp[k] = a[j];
				j++;
				k++;
			}
		}
		for (k = 0; k < last - first + 1; k++)
		{
			a[k + first] = temp[k];
		}
		delete[] temp;
	}
	
	static void MergeSorting(vector<T> &a, int first, int last)
	{
		if (first < last)
		{
			int newlast = (first + last) / 2;
			MergeSorting(a, first, newlast);
			MergeSorting(a, newlast + 1, last);
			Merge(a, first, last, newlast);
		}
	}
	
public:
	static vector<T> sort (vector<T> a)
	{
		int x = a.size() - 1;
		MergeSorting(a,0,x);
		return a;
	}
};

#endif
