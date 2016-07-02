#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> // abs
#include <climits> // INT_MAX, INT_MIN
#include <utility> // std::max, std::min
#include <cmath>   // log10, pow, sqrt
#include <iomanip> // setprecision

using namespace std;
/**
 * https://code.google.com/codejam/contest/5254486/dashboard#s=p3
 * Since n is large, we can not calculate all the elements in the new array.
 * 1. Preprocess to get the "sum" and "sum of sum" of the original array.
 * 2. Use binary search on the value of the final sorted new array to find the
 *    value corresponding to the specified index.
 * 3. Calculate the sum of all the subarray having sum less than or equal(partial)
 *    to the value found.
 * Use sliding window to reduce time complexity when iterating all the
 * subarrays.
 */
vector<long long> s(200001, 0), ss(200001, 0);

long long calc(int n, long long index) {
  if (index == 0) return 0;
  long long low = 1, high = s[n];
  long long e = 0, t = 0;
  while (low <= high) {
    long long mid = low + (high - low) / 2;
    long long equal = 0, total = 0;
    int j = 0;
    for (int i = 1; i <= n; ++i) { // sliding window
      while (j < i && s[i] - s[j] > mid) ++j;
      total += i - j;
      if (s[i] - s[j] == mid) ++equal;
    }
    if (total < index) {
      low = mid + 1;
    } else {
      high = mid - 1;
      e = equal;
      t = total;
    }
  }
  long long result = (index - (t - e)) * low;
  int j = 0;
  for (int i = 1; i <= n; ++i) { // sliding window
    while (j < i && s[i] - s[j] >= low) ++j;
    result += (i - j) * s[i] - (ss[i - 1] - ss[j - 1]);
  }
  return result;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
      cin >> s[i];
      s[i] += s[i - 1];          // s[i]: sum
      ss[i] = ss[i - 1] + s[i];  // ss[i]: sum of sum
    }

    cout << "Case #" << t << ":" << endl;
    for (int qq = 0; qq < q; ++qq) {
      long long l, r;
      cin >> l >> r;
      cout << calc(n, r) - calc(n, l - 1) << endl;
    }
  }
  return 0;
}
