#include <iostream>
using namespace std;

struct Node {
  double value;
  Node* next;
  Node(double v = 0.0, Node* n = NULL) : value(v), next(n) {}
};

void BucketSort(double arr[], int n) {
  Node* buckets[10];
  for (int i = 0; i < 10; ++i)
    buckets[i] = new Node(0, NULL); // dummy node for insert sort
  for (int i = 0; i < n; ++i) { // insert into the corresponding bucket, keeping
                                // the order
    int index = arr[i] * 10;
    Node* p = new Node(arr[i], NULL);
    Node* previous = buckets[index];
    while (previous->next && previous->next->value <= arr[i])
      previous = previous->next;
    p->next = previous->next;
    previous->next = p;
  }
  Node* tmp = NULL;
  int j = 0;
  for (int i = 0; i < 10; ++i) { // generate output
    tmp = buckets[i];
    buckets[i] = buckets[i]->next;
    delete tmp;
    while (buckets[i]) {
      tmp = buckets[i];
      buckets[i] = buckets[i]->next;
      arr[j++] = tmp->value;
      delete tmp;
    }
  }
}

int main() {
  srand(time(0));
  const int NUM = 30;
  double arr[NUM];
  for (int i = 0; i < NUM; ++i) {
    while (true) {
      arr[i] = rand() / (double)RAND_MAX;
      if (arr[i] != 0.0 && arr[i] != 1.0)
        break;
    }
  }
  for (int i = 0; i < NUM; ++i)
    cout << arr[i] << "   ";
  cout << endl << endl;
  BucketSort(arr, NUM);
  for (int i = 0; i < NUM; ++i)
    cout << arr[i] << "   ";
  cout << endl;
  return 0;
}
