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
 * https://code.google.com/codejam/contest/6274486/dashboard#s=p1
 * m[i][j]: the number of squares taking the corresponding cell as the bottom right corrner
 */
int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int r, c, k;
    cin >> r >> c >> k;
    vector<vector<int>> m(r + 1, vector<int>(c + 1, 0));
    for (int i = 0; i < k; ++i) {
      int x, y;
      cin >> x >> y;
      m[x + 1][y + 1] = -1;
    }
    long long result = 0;
    for (int i = 1; i <= r; ++i) {
      for (int j = 1; j <= c; ++j) {
        if (!m[i][j]) {
          m[i][j] = min(min(max(m[i - 1][j - 1], 0), max(m[i - 1][j], 0)), max(m[i][j - 1], 0)) + 1;
          result += m[i][j];
        }
      }
    }
    cout << "Case #" << t << ": ";
    cout << result;
    cout << endl;
  }

  return 0;
}
