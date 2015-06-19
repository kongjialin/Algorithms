#include <iostream>
using namespace std;

int Partition1(int arr[], int begin, int end) {
  int pivot = arr[begin];
  int i = begin, j = end;
  while (i < j) {
    while (i < j && pivot <= arr[j])
      --j;
    arr[i] = arr[j];
    while (i < j && pivot >= arr[i])
      ++i;
    arr[j] = arr[i];
  }
  arr[i] = pivot;
  return i; 
}

int Partition2(int arr[], int begin, int end) {
  int i = begin;
  for (int j = begin; j < end; ++j) {
    if (arr[j] < arr[end]) { // arr[end] is the pivot
      swap(arr[i], arr[j]);
      ++i;
    }
  }
  swap(arr[i], arr[end]);
  return i;
}

void QuickSort(int arr[], int begin, int end) {
  if (begin >= end) return;
  int pivot_index = Partition2(arr, begin, end);
  QuickSort(arr, begin, pivot_index - 1);
  QuickSort(arr, pivot_index + 1, end);
}

// for sorting array with many duplicate elements
pair<int, int> Partition3(int arr[], int begin, int end) {
  int pivot = arr[begin];
  int left = begin, right = end;
  int current = begin + 1;
  while (current <= right) {
    if (arr[current] == pivot) {
      ++current;
    } else if (arr[current] < pivot) {
      swap(arr[left], arr[current]);
      ++left;
      ++current;
    } else {
      swap(arr[current], arr[right]);
      --right;
    }
  }
  return pair<int, int>(left, right);
}

pair<int, int> Partition4(int arr[], int begin, int end) {
  int pivot = arr[begin];
  int p_less = begin - 1, p_equal = begin - 1, p_greater = begin - 1;
  for (int i = begin; i <= end; ++i) {
    if (arr[i] > pivot) {
      ++p_greater;
    } else if (arr[i] == pivot) {
      arr[++p_greater] = arr[++p_equal];
      arr[p_equal] = pivot;
    } else {
      arr[++p_less] = arr[i];
      arr[++p_greater] = arr[++p_equal];
      arr[p_equal] = pivot;
    }
  }
  return pair<int, int>(p_less + 1, p_equal);
}

void QuickSort2(int arr[], int begin, int end) {
  if (begin >= end) return;
  pair<int, int> bounds = Partition3(arr, begin, end);
  QuickSort2(arr, begin, bounds.first - 1);
  QuickSort2(arr, bounds.second + 1, end);
}

int main() {
  int arr[] = {1,3,4,5,1,1,2,9,1,2,6,8,7,1,2};
  QuickSort2(arr, 0, 14);
  for (int i = 0; i < 15; ++i)
    cout << arr[i] << " ";
  cout << endl;
  return 0;
}
