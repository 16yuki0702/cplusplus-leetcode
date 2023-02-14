#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// https://www.geeksforgeeks.org/segment-tree-efficient-implementation/

const int N = 16;

void printSegmentTree(int tree[]) {
  printf("\n%d\n", tree[1]);
  int level = 2;
  while (level < 32) {
    for (int i = level; i < 2 * level; i++) {
      printf("%d ", tree[i]);
    }
    level <<= 1;
    printf("\n");
  }
}

void updateSegmentTree(int tree[], int p, int val) {
  tree[p + N] = val;
  //p = p & 1 ? p - 1 : p; 
  p = (p + N) / 2;
  for (; p >= 1; p >>= 1) {
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
  }
}

void segmentTree() {
  int tree[N * 2] = {0};
  // build leaf node
  for (int i = 0; i < N; i++) {
    tree[i + N] = i + 1;
  }
  // build parent node
  for (int i = N - 1; i > 0; i--) {
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
  }
  printSegmentTree(tree);
  updateSegmentTree(tree, 1, 3);
  printSegmentTree(tree);
  updateSegmentTree(tree, 10, 100);
  printSegmentTree(tree);
  updateSegmentTree(tree, 13, 200);
  printSegmentTree(tree);
}

int main(int argc, char *argv[]) {
  segmentTree();
};
