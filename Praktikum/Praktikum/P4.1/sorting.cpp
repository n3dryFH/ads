#include "sorting.h"


namespace sorting {


	//************
	// QuickSort *
	//************      
	void swap(int& a, int& b)
	{
		int t = a;
		a = b;
		b = t;
	}

	int Partition(vector<int> &arr, int left, int right)
	{
		int pivot = arr[right];
		int indexOfSmallerElement = left - 1;
		for (int i = left; i < right; ++i)
		{
			if (arr[i] <= pivot)
			{
				++indexOfSmallerElement;
				swap(arr[indexOfSmallerElement], arr[i]);
			}
		}
		swap(arr[indexOfSmallerElement + 1], arr[right]); // put pivot between smaller and higher values
		return indexOfSmallerElement + 1;
	}
	
	void QuickSort(vector<int> &arr, int left, int right) {
		
		//***************************
		// implement quicksort here *
		//************ **************
		if (left < right)
		{
			int partition = Partition(arr, left, right);
			QuickSort(arr, left, partition - 1);
			QuickSort(arr, partition + 1, right);
		}
	}

	//************
	// MergeSort *
	//************

	//***************************
	// implement mergesort here *
	//***************************


	void Merge(vector<int> &a, int low, int pivot, int high) 
	{
		int lSize = pivot - low + 1;
		int rSize = high - pivot;

		vector<int> lVec(lSize);
		vector<int> rVec(rSize);		

		for (int i = 0; i < lSize; i++)
			lVec[i] = a[low + i];
		for (int i = 0; i < rSize; i++)
			rVec[i] = a[pivot +1 + i];
		
		int lIndex = 0, rIndex = 0, aIndex = low;
		while (lIndex < lSize && rIndex < rSize)
		{
			if (lVec[lIndex] <= rVec[rIndex])
			{
				a[aIndex] = lVec[lIndex];
				++lIndex;
			}
			else
			{
				a[aIndex] = rVec[rIndex];
				++rIndex;
			}
			++aIndex;
		}
		for (;lIndex < lSize; ++lIndex)		
			a[aIndex++] = lVec[lIndex];		

		for (;rIndex < rSize; ++rIndex)		
			a[aIndex++] = rVec[rIndex];		
	}

	void MergeSort(vector<int> &a, int low, int high) 
	{
		if (low < high)
		{
			int m = (low + high) / 2;
			MergeSort(a, low, m);
			MergeSort(a, m + 1, high);
			Merge(a, low, m, high);
		}
	}



	//************
	// Heapsort  *
	//************

	void Heapify(vector<int> &a, int heapSize, int index)
	{
		int largest = index;
		int leftChildIndex = 2 * index + 1;
		int rightChildIndex = 2 * index + 2;

		if (leftChildIndex < heapSize && a[leftChildIndex] > a[largest])
			largest = leftChildIndex;
		if (rightChildIndex < heapSize && a[rightChildIndex] > a[largest])
			largest = rightChildIndex;

		if (largest != index)
		{
			swap(a[index], a[largest]);
			Heapify(a, heapSize, largest);
		}
	}

	void HeapSort(vector<int> &a, int n) 
	{
		//***************************
		// implement heapsort here *
		//***************************

		for (int i = n / 2 - 1; i >= 0; --i)
			Heapify(a, n, i);

		for (int i = n - 1; i >= 0; --i)
		{
			swap(a[0], a[i]);
			Heapify(a, i, 0);
		}
	}

	int GetHibbard(int value)
	{
		int hibbardValue = 1;
		while (value > hibbardValue)
		{
			hibbardValue = (hibbardValue * 2) + 1;
		}
		return (hibbardValue -1) / 2;
	}

	//************
	// Shellsort *
	//************
	void ShellSort(vector<int> &a, int n)
	{

		//***************************
		// implement shellsort here *
		//***************************
		int gap = GetHibbard(n);
		for (; gap > 0; gap = (gap -1) / 2)
		{
			for (int i = gap; i < n; ++i)
			{
				int tmp = a[i];
				int j = i;
				for (; j >= gap && a[j - gap] > tmp; j -= gap)
					a[j] = a[j - gap];
				a[j] = tmp;
			}
		}
	}


  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





