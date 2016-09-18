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
 * https://code.google.com/codejam/contest/6274486/dashboard#s=p0
 */

double p, q;
int r, c, rs, cs, s;
vector<vector<int>> direction({{-1, 0}, {0, 1}, {1, 0}, {0, -1}});

void dfs(vector<vector<double>>& m, vector<vector<char>>& ch, int i, int j, int s, double expect, double& result) {
    if (!s) {
        result = max(result, expect);
        return;
    }
    double prob = ch[i][j] == 'A' ? p : q;
    m[i][j] *= 1 - prob;
    for (int k = 0; k < 4; ++k) {
        int x = i + direction[k][0], y = j + direction[k][1];
        if (x >= 0 && x < r && y >= 0 && y < c)
            dfs(m, ch, x, y, s - 1, expect + m[x][y], result);
    }
    m[i][j] /= 1 - prob;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> r >> c >> rs >> cs >> s;
        cin >> p >> q;
        vector<vector<double>> m(r, vector<double>(c));
        vector<vector<char>> ch(r, vector<char>(c));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> ch[i][j];
                m[i][j] = ch[i][j] == 'A' ? p : q;
            }
        }
        double result = 0;
        m[rs][cs] = m[rs][cs] / (1 - m[rs][cs]);
        dfs(m, ch, rs, cs, s, 0, result);
        cout << "Case #" << t << ": ";
        cout << setprecision(15) << result;
        cout << endl;
    }
    return 0;
}
