#include <iostream>
#include <vector>

using namespace std;

void shellsort(vector<int> &v) {
  for (auto vv : v) {
    printf("%d ", vv);
  }
  printf("\n");
  int n = v.size(); // n = 16
  int h = 1;
  while (h < n / 3) {
    h = h * 3 + 1;  // 1, 4, 13
  }
  while (h >= 1) {
    for (int i = h; i < n; i++) {
      for (int j = i; j >= h; j -= h) {
        if (v[j - h] > v[j]) {
          swap(v[j - h], v[j]);
        }
      }
    }
    h = h / 3;      // 13, 4, 1
  }
  for (auto vv : v) {
    printf("%d ", vv);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  vector<int> v{16, 1, 3, 9, 8, 2, 4, 15, 14, 11, 13, 6, 7, 12, 5, 10};
  shellsort(v);
};
