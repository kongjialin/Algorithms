#include <iostream>
#include <vector>

#define INF INT_MAX
using namespace std;

void PrintGraph(vector<vector<int>>& graph) {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph.size(); ++j) {
      if (graph[i][j] == INT_MAX)
        cout << "INF ";
      else
        cout << graph[i][j] << " ";
    }
    cout << endl;
  }
}

/**
 * Floyd Algorithm for finding the shortest paths between all pairs.
 * Take each node as the intermediate node one by one, and use it to
 * update the shortest path between each pair of nodes.
 * Be careful about the possible integer overflow.
 * O(n^3) time.
 * @param graph The adjacency matrix, graph[i][j] == INT_MAX if there is
 *              no edge between node i and j. And dp[i][i] == 0.
 */
void Floyd(vector<vector<int>>& graph) {
  int n = graph.size();
  vector<vector<int>> shortest(graph);
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (shortest[i][k] - shortest[i][j] < -shortest[k][j])
          shortest[i][j] = shortest[i][k] + shortest[k][j];
      }
    }
  }

  PrintGraph(shortest);
}

/**
 * Get the shortest path from node i to j (if there is a path).
 */
vector<int> GetPath(vector<vector<int>>& next, int i, int j) {
  vector<int> path({i});
  while (i != j) {
    i = next[i][j];
    path.push_back(i);
  }
  return path;
}

/**
 * Floyd Algorithm with the routing table.
 * Use an auxiliary matrix next[i][j] to store the next node from i on
 * the path from i to j.
 */
void FloydWithRouting(vector<vector<int>>& graph) {
  int n = graph.size();
  vector<vector<int>> shortest(graph), next(n, vector<int>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      next[i][j] = j;
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (shortest[i][k] - shortest[i][j] < -shortest[k][j]) {
          shortest[i][j] = shortest[i][k] + shortest[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }

  PrintGraph(shortest);
  PrintGraph(next);
}

int main() {
  vector<vector<int>> graph({{0, 5, INF, 10},
                             {INF, 0, 3, INF},
                             {INF, INF, 0, 1},
                             {INF, INF, INF, 0}});
  FloydWithRouting(graph);
  return 0;
}
