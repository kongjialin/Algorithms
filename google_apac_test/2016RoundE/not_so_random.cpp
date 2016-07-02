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
 * https://code.google.com/codejam/contest/5254486/dashboard#s=p2
 * Since the operation is bitwise, each bit is independent.
 * We can calculate the probability of each bit being one after
 * n steps -- pi, and the final expected value is sum{pi * (1 << i)}.
 * For each bit of x:
 * dp[i][j]: the probability of the current bit being j after i steps,
 * and j is 0 or 1.
 * We need to calculate dp[n][1].
 * dp[0][0] = (xbit == 1) ? 0 : 1, dp[0][1] = (xbit == 1) ? 1 : 0
 */
int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t) {
    int n, x, k, a, b, c;
    cin >> n >> x >> k >> a >> b >> c;
    cout << "Case #" << t << ": ";
    double aa = a / 100.0, bb = b / 100.0, cc = c / 100.0;
    double result = 0;
    for (int pos = 0; pos < 32; ++pos) {
      int kbit = (k >> pos) & 1;
      vector<vector<double>> dp(n + 1, vector<double>(2, 0));
      dp[0][(x >> pos) & 1] = 1;
      for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 1; ++j) {
          dp[i][j & kbit] += dp[i - 1][j] * aa;
          dp[i][j | kbit] += dp[i - 1][j] * bb;
          dp[i][j ^ kbit] += dp[i - 1][j] * cc;
        }
      }
      result += dp[n][1] * (1 << pos);
    }
    cout << setprecision(15) << result;
    cout << endl;
  }
  return 0;
}
