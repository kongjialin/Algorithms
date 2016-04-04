#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // std::pair
#include <queue>

using namespace std;

void PrintResult(vector<int>& distance, int source) {
  cout << "Source: " << source << endl;
  cout << "Vertex     Distance from Source" << endl;
  for (int i = 0; i < distance.size(); ++i)
    cout << i << "               " << distance[i] << endl;
}

/* @param graph Adjacency list, the first field of the pair is the node No.,
 *              and the second field of the pair is the distance.
 * Time complexity: .
 */
void SPFA(vector<vector<pair<int, int>>>& graph, int source) {
  int n = (int)graph.size();
  vector<bool> visited(n, false);
  vector<int> distance(n, INT_MAX);
  queue<int> Q;
  Q.push(source);
  distance[source] = 0;
  while(!Q.empty()) {
    int u = Q.front();
    Q.pop();
    visited[u] = false;
    for(int i = 0; i < graph[u].size(); ++i) {
      int v = graph[u][i].first;
      if (distance[u] + graph[u][i].second < distance[v]) {
        distance[v] = distance[u] + graph[u][i].second;
        if(!visited[v]) {
          visited[v] = true;
          Q.push(v);
        }
      }
    }
  }
  PrintResult(distance, source);
}

int main() {
  vector<vector<pair<int, int>>> graph({{{1, 4}, {7, 8}},
      {{0, 4}, {2, 8}, {7, 11}},
      {{1, 8}, {3, 7}, {5, 4}, {8, 2}},
      {{2, 7}, {4, 9}, {5, 14}},
      {{3, 9}, {5, 10}},
      {{2, 4}, {4, 10}, {6, 2}},
      {{3, 14}, {5, 2}, {7, 1}, {8, 6}},
      {{0, 8}, {1, 11}, {6, 1}, {8, 7}},
      {{2, 2}, {6, 6}, {7, 7}}});
  SPFA(graph, 0);
  return 0;
}

