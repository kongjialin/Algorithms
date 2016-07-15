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
 * https://code.google.com/codejam/contest/11274486/dashboard#s=p1
 * Use a priority queue (min heap) of boundaries, and each time pop the
 * cell with the minimum height, whose neighbors' water can be decided.
 * Then push the BFS-processed neighbors into the queue, and update the
 * boundaries, until all the cells are visited.
 */

struct Cell {
  int i;
  int j;
  int height;
  Cell(int ii, int jj, int h) : i(ii), j(jj), height(h) {}
};

class Compare {
 public:
  bool operator()(const Cell& c1, const Cell& c2) {
    return c1.height > c2.height;
  }
};

int main() {
  int T;
  cin >> T;
  vector<vector<int>> direction({{-1, 0}, {0, 1}, {1, 0}, {0, -1}});
  for (int t = 1; t <= T; ++t) {
    int r, c;
    cin >> r >> c;
    vector<vector<int>> h(r, vector<int>(c));
    for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j)
        cin >> h[i][j];
    priority_queue<Cell, vector<Cell>, Compare> Q;
    vector<vector<bool>> visited(r, vector<bool>(c, false));
    for (int i = 0; i < r; ++i) {
      Q.push(Cell(i, 0, h[i][0]));
      Q.push(Cell(i, c - 1, h[i][c - 1]));
      visited[i][0] = true;
      visited[i][c - 1] = true;
    }
    for (int j = 1; j < c - 1; ++j) {
      Q.push(Cell(0, j, h[0][j]));
      Q.push(Cell(r - 1, j, h[r - 1][j]));
      visited[0][j] = true;
      visited[r - 1][j] = true;
    }
    cout << "Case #" << t << ": ";
    int water = 0;
    while (!Q.empty()) {
      Cell cell(Q.top());
      Q.pop();
      for (int k = 0; k < 4; ++k) {
        int x = cell.i + direction[k][0], y = cell.j + direction[k][1];
        if (x > 0 && x < r && y > 0 && y < c && !visited[x][y]) {
          visited[x][y] = true;
          if (cell.height > h[x][y]) {
            water += cell.height - h[x][y];
            h[x][y] = cell.height;
          }
          Q.push(Cell(x, y, h[x][y]));
        }
      }
    }
    cout << water;
    cout << endl;
  }
  return 0;
}
