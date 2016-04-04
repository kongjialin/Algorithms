#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // std::pair

using namespace std;

void PrintResult(vector<int>& distance, int source) {
  cout << "Source: " << source << endl;
  cout << "Vertex     Distance from Source" << endl;
  for (int i = 0; i < distance.size(); ++i)
    cout << i << "               " << distance[i] << endl;
}

/* @param graph Adjacency list, the first field of the pair is the node No.,
 *              and the second field of the pair is the distance.
 * Time complexity: O(n^2).
 */
void Dijkstra(vector<vector<pair<int, int>>>& graph, int source) {
  int n = graph.size();
  vector<bool> finished(n, false);
  vector<int> distance(n, INT_MAX);
  distance[source] = 0;
  for (int count = 0; count < n - 1; ++count) {
    int min_distance = INT_MAX, min_index;
    for (int j = 0; j < n; ++j) {
      if (!finished[j] && distance[j] < min_distance) {
        min_distance = distance[j];
        min_index = j;
      }
    }
    finished[min_index] = true;
    vector<pair<int, int>>& pairs = graph[min_index];
    for (int j = 0; j < pairs.size(); ++j) {
      if (!finished[pairs[j].first])
        distance[pairs[j].first] = min(min_distance + pairs[j].second,
                                       distance[pairs[j].first]);
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
  Dijkstra(graph, 0);
  return 0;
}
