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
 * https://code.google.com/codejam/contest/11274486/dashboard#s=p3
 * dfs with pruning.
 */

void dfs(int i, int count, int n, int m, long long power, vector<int>& k,
    vector<int>& l, vector<long long>& max_power_sum, vector<vector<int>>& a,
    vector<vector<int>>& c, long long& result) {
  if (count == 8) {
    result = max(result, power);
    return;
  }
  if (power + max_power_sum[i] <= result) return; // pruning 1
  if (n - i > 8 - count)
    dfs(i + 1, count, n, m, power, k, l, max_power_sum, a, c, result);
  dfs(i + 1, count + 1, n, m, power + a[i][l[i]], k, l, max_power_sum, a, c, result);
  for (int j = l[i]; j < k[i]; ++j) {
    m -= c[i][j];
    if (m < 0) break; // pruning 2
    dfs(i + 1, count + 1, n, m, power + a[i][j + 1], k, l, max_power_sum, a, c, result);
  }
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int m, n;
    cin >> m >> n;
    vector<int> k(n), l(n);
    vector<long long> max_power_sum(n + 1, 0);
    vector<vector<int>> a(n, vector<int>()), c(n, vector<int>());
    for (int i = 0; i < n; ++i) {
      cin >> k[i] >> l[i];
      for (int j = 0; j < k[i]; ++j) {
        int aij;
        cin >> aij;
        a[i].push_back(aij);
      }
      for (int j = 0; j < k[i] - 1; ++j) {
        int cij;
        cin >> cij;
        c[i].push_back(cij);
      }
      --k[i];
      --l[i];
    }
    for (int i = n - 1; i >= 0; --i) // max power sum from i to n - 1
      max_power_sum[i] = max_power_sum[i + 1] + a[i][k[i]];
    long long result = 0;
    dfs(0, 0, n, m, 0, k, l, max_power_sum, a, c, result);
    cout << "Case #" << t << ": ";
    cout << result;
    cout << endl;
  }
  return 0;
}
