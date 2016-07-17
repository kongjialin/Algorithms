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
#include <cmath>   // log10, pow, sqrt, ceil
#include <iomanip> // setprecision

using namespace std;

/**
 * https://code.google.com/codejam/contest/11274486/dashboard#s=p2
 * The original expression can be changed into:
 * val = 1 / (1 + r)
 * c0 = c1 * val + c2 * val^2 + ... + cm * val^m
 *    = (((cm * val + c[m-1]) * val + c[m-2])... + c1) * val
 *    = f(m)
 * if r increases, then f(m) will decrease, 
 * and if r decreases, then f(m) will increase.
 * Use binary search.
 */


int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int m;
    cin >> m;
    vector<int> c(m + 1);
    for (int i = 0; i <= m; ++i) cin >> c[i];
    double low = -1, high = 1;
    while (high - low >= 1e-9) {
      double mid = (low + high) / 2;
      double val = 1 / (1 + mid);
      double result = 0;
      for (int i = m; i > 0; --i)
        result = (result + c[i]) * val;
      if (result == c[0]) {
        low = mid;
        break;
      } else if (result < c[0]) {
        high = mid;
      } else {
        low = mid;
      }
    }
    cout << "Case #" << t << ": ";
    cout << setprecision(15) << low;
    cout << endl;
  }
  return 0;
}
