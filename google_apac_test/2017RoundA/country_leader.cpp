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
 * https://code.google.com/codejam/contest/11274486/dashboard#s=p0
 * Be careful when dealing with operation or comparison between size_t and negative int !!!
 */
int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int n;
    cin >> n;
    cin.get(); // skip the endline symbol!
    string leader;
    int count = 0; // negative number will be converted into very big unsigned type when
                   // comparing with size_t, so don't use negative number.
    for (int i = 0; i < n; ++i) {
      string name;
      getline(cin, name);
      unordered_set<char> hashset;
      for (int j = 0; j < name.size(); ++j) {
        if (name[j] != ' ')
          hashset.insert(name[j]);
      }
      if (count < hashset.size() || (count == hashset.size() && name < leader)) {
        leader = name;
        count = hashset.size();
      }
    }

    cout << "Case #" << t << ": ";
    cout << leader;
    cout << endl;
  }
  return 0;
}
