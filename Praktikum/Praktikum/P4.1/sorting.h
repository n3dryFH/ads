#ifndef _SORTING_H_
#define _SORTING_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

namespace sorting {
  
  //************
  // QuickSort *
  //************
  void QuickSort(vector<int> &arr, int left, int right);

  //************
  // MergeSort *
  //************
  void Merge(vector<int> &a, int low, int pivot, int high);
  void MergeSort(vector<int> &a, int low, int high);

  //************
  // Heapsort  *
  //************
  void HeapSort(vector<int> &a, int n);

  //************
  // Shellsort *
  //************
  void ShellSort(vector<int> &a, int n);

  //*******************
  // Helper functions *
  //*******************
  void randomizeVector(vector<int> &array, int n);
  
 }
#endif 
