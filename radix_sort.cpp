#include <iostream>
#include <vector>
using namespace std;

/* Least Significant Digit Radix Sort (LSD) 
 * The radix in the following implementatin is 10.
 * The input numbers are all non-negative.
 * Time complexity: O(kn), where k is the maximum digit length of the input
 */

// Find the maximum length of the digits in the input
int MaxLength(const vector<int>& input) {
  if (!input.size()) return 0;
  int max = input[0];
  for (int i = 1; i < input.size(); ++i) {
    if (input[i] > max)
      max = input[i];
  }
  int max_length = 0;
  do {
    ++max_length;
    max /= 10;
  } while (max);
  return max_length;
}

/* Use counting sort for each position of digit
 * @param digit The digit on which the sort is based (0 to max_length - 1)
 */
void CountingSort(vector<int>& input, int digit) {
  vector<int> count(10, 0);
  vector<int> output(input.size(), 0);
  int divisor = 1;
  for (int i = 0; i < digit; ++i) // calculate 10^digit
    divisor *= 10;
  int index = 0;
  for (int i = 0; i < input.size(); ++i) {
    index = input[i] / divisor % 10;
    ++count[index];
  }
  int total = 0, current = 0;
  for (int i = 0; i < 10; ++i) {
    current = count[i];
    count[i] = total;
    total += current;
  }
  for (int i = 0; i < input.size(); ++i) {
    index = input[i] / divisor % 10;
    output[count[index]++] = input[i];
  }
  for (int i = 0; i < input.size(); ++i)
    input[i] = output[i];
}

void LSDRadixSort(vector<int>& input) {
  int max_length = MaxLength(input);
  for (int i = 0; i < max_length; ++i)
    CountingSort(input, i);
}

int main() {
  srand(time(0));
  int n = 100;
  vector<int> input;
  for (int i = 0; i < n; ++i)
    input.push_back(rand() % 1000);
  LSDRadixSort(input);
  for (int i = 0; i < input.size(); ++i)
    cout << input[i] << " ";
  cout << endl;
  return 0;
}
