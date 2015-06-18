#include <iostream>
using namespace std;

void BubbleSort(int arr[], int n) {
  for (int i = n - 1; i > 0; --i) {
    for (int j = 0; j < i; ++j) {
      if (arr[j] > arr[j + 1])
        swap(arr[j], arr[j + 1]);
    }
  }
}

void BubbleSortImproved(int arr[], int n) {
  int pos = n - 1; // pos: position of the last swap operation
  int bound;
  while (pos) {
    bound = pos;
    pos = 0;
    for (int i = 0; i < bound; ++i) {
      if (arr[i] > arr[i + 1]) {
        swap(arr[i], arr[i + 1]);
        pos = i;
      }
    }
  }
}

int main() {
  int arr[] = {3,7,1,2,5,9,8,6,4};
  BubbleSortImproved(arr, 9);
  for (int i = 0; i < 9; ++i)
    cout << arr[i] << " ";
  cout << endl;
  return 0;
}
