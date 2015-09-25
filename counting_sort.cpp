#include <iostream>
#include <vector>
using namespace std;

/* For simplicity, the input array is an integer array. Actually, to apply
 * counting sort to wide use cases, the input array element can be of many other
 * types, such as a pointer to a complex object, containing an integer member
 * variable, on which the sort is based. */

/* The following implementation makes counting sort stable. */
/* Time complexity: O(n + k), Auxiliary space: O(n + k) */
// @param n  The number of inputs
// @param k  The range of the inputs (0 to k - 1)
void CountingSort(vector<int>& input, int n, int k) {
  vector<int> count(k, 0);
  vector<int> output(n, 0);
  for (int i = 0; i < n; ++i)
    ++count[input[i]];
  int current = 0, total = 0;
  for (int i = 0; i < k; ++i) { // modify the count[], so that count[i] stores
    current = count[i];         // the total number of elements that have the
    count[i] = total;           // key smaller than i, which is also the
    total += current;           // beginning index of i in the output array.
  }
  int key;
  for (int i = 0; i < n; ++i) {
    key = input[i];
    output[count[key]++] = key;
  }
  for (int i = 0; i < n; ++i)
    cout << output[i] << " ";
  cout << endl;
}

/* If the input elements are just integers, then the counting sort can be
 * simplified, without modifying the counting array, and directly generate the
 * output. */
void IntCountingSort(vector<int>& input, int n, int k) {
  vector<int> count(k, 0);
  for (int i = 0; i < n; ++i)
    ++count[input[i]];
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < count[i]; ++j)
      cout << i << " ";
  }
  cout << endl;
}

int main() {
  srand(time(0));
  int n = 100, k = 10;
  vector<int> input;
  for (int i = 0; i < n; ++i)
    input.push_back(rand() % k);
  CountingSort(input, n, k);
  IntCountingSort(input, n, k);
  return 0;
}
