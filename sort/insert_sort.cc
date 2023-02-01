#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void insertSort() {
  int v[10] = {3, 1, 10, 9, 2, 4, 6, 8, 7, 5};
  for (int vv: v) {
    printf("%d ", vv);
  }
  printf("\n");
  for (int i = 1; i < 10; i++) {
    int j = i - 1, m = v[i];
    while (j >= 0 && v[j] > m) {
      v[j+1] = v[j];
      j--;
    }
    v[j+1] = m;
  }
  for (int vv: v) {
    printf("%d ", vv);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  insertSort();
};
