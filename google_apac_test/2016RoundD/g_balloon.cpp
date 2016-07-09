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
 * https://code.google.com/codejam/contest/11214486/dashboard#s=p1
 * Solution 1:
 * First, get a dfs(backtracking) solution. Then, find overlap and use memoization DP.
 * dp[i][q]: the min time needed from p[i] to p[n - 1] with energy q
 * answer = dp[0][q]
 */
int dfs(int i, int n, int m, int q, vector<int>& p, vector<int>& v,
        vector<int>& h, vector<vector<int>>& dp) {
  if (i == n) return 0;
  if (dp[i][q] != -1) return dp[i][q];
  if (p[i] == 0)
    return dp[i][q] = dfs(i + 1, n, m, q, p, v, h, dp);
  dp[i][q] = INT_MAX;
  for (int j = 0; j < m; ++j) {
    if (v[j] == 0) continue;
    if ((p[i] > 0 ^ v[j] > 0) && q >= abs(j - h[i]))
      dp[i][q] = min(dp[i][q],
                     max(dfs(i + 1, n, m, q - abs(j - h[i]), p, v, h, dp),
                         (int)ceil(abs((double)p[i] / v[j]))));
  }
  return dp[i][q];
}

void solve1(int n, int m, int q, vector<int>& v,
          vector<int>& p, vector<int>& h) {
  vector<vector<int>> dp(n, vector<int>(q + 1, -1));
  int result = dfs(0, n, m, q, p, v, h, dp);
  if (result == INT_MAX) cout << "IMPOSSIBLE";
  else cout << result;
}

/**
 * Solution 2:
 * Use binary search to find the minimum time with energy <= q
 */
bool check(int n, int m, int q, int time, vector<int>& v, vector<int>& p,
    vector<int>& h) {
  for (int i = 0; i < n; ++i) {
    if (p[i] == 0) continue;
    int min_energy = INT_MAX;
    for (int j = 0; j < m; ++j) {
      if (v[j] == 0) continue;
      if ((p[i] > 0 ^ v[j] > 0) && ceil(abs((double)p[i] / v[j])) <= time)
        min_energy = min(min_energy, abs(j - h[i]));
    }
    if (min_energy == INT_MAX) return false;
    q -= min_energy;
    if (q < 0) return false;
  }
  return true;
}

void solve2(int n, int m, int q, vector<int>& v,
          vector<int>& p, vector<int>& h) {
  int low = 0, high = 10000;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (check(n, m, q, mid, v, p, h)) high = mid - 1;
    else low = mid + 1;
  }
  if (low == 10001) cout << "IMPOSSIBLE";
  else cout << low;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> v(m), p(n), h(n);
    for (int i = 0; i < m; ++i) cin >> v[i];
    for (int i = 0; i < n; ++i) cin >> p[i] >> h[i];
    cout << "Case #" << t << ": ";
    solve2(n, m, q, v, p, h);
    // solve1(n, m, q, v, p, h);
    cout << endl;
  }
  return 0;
}
