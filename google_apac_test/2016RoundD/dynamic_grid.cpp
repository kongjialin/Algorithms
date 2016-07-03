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

vector<vector<int>> direction({{-1, 0}, {0, 1}, {1, 0}, {0, -1}});

int bfs(vector<vector<char>>& board, int r, int c) {
  vector<vector<bool>> visited(r, vector<bool>(c, false));
  int result = 0;
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (board[i][j] == '1' && !visited[i][j]) {
        queue<pair<int, int>> q;
        visited[i][j] = true;
        q.push(make_pair(i, j));
        while (!q.empty()) {
          int x = q.front().first, y = q.front().second;
          q.pop();
          for (int k = 0; k < 4; ++k) {
            int new_x = x + direction[k][0], new_y = y + direction[k][1];
            if (new_x >= 0 && new_x < r && new_y >= 0 && new_y < c && board[new_x][new_y] == '1'
                && !visited[new_x][new_y]) {
              visited[new_x][new_y] = true;
              q.push(make_pair(new_x, new_y));
            }
          }
        }
        ++result;
      }
    }
  }
  return result;
}

int main() {
  int T;
  cin >> T;

  for (int t = 1; t <= T; ++t) {
    int r, c;
    cin >> r >> c;
    vector<vector<char>> board(r, vector<char>(c));
    for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j)
        cin >> board[i][j];

    cout << "Case #" << t << ":" << endl;
    int n, x, y;
    char z;
    cin >> n;
    for (int i = 0; i < n; ++i) {
      char m;
      cin >> m;
      if (m == 'M') {
        cin >> x >> y >> z;
        board[x][y] = z;
      } else {
        cout << bfs(board, r, c) << endl;
      }
    }
  }
  return 0;
}
