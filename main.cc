#include <iostream>
#include <vector>
using namespace std;

void insertSort() {
  int v[10] = {3, 1, 10, 9, 2, 4, 6, 8, 7, 5};
  for (int i = 1; i < 10; i++) {
    int j = i - 1, m = v[i];
    while (j >= 0 && v[j] > m) {
      v[j+1] = v[j];
      j--;
    }
    v[j+1] = m;
  }
  for (int vv: v) {
    cout << vv << endl;
  }
}

void quickSort(vector<int>& s, int left, int right) {
  if (left >= right) {
    return;
  }
  int p = left;
  swap(s[int((left + right) / 2)], s[right]);
  for (int i = left; i < right; i++) {
    if (s[i] < s[right]) {
      swap(s[i], s[p]);
      p++;
    }
  }
  swap(s[p], s[right]);
  quickSort(s, left, p - 1);
  quickSort(s, p + 1, right);
} 

int main(int argc, char *argv[]) {
  vector<int> s = {3, 1, 10, 0, 9, 2, 4, 6, 8, 7, 5, 11, 15, 14, 12, 13};
  /*
  string s = "test-string-desuka";
  for (auto c: s) {
    cout << c << endl;
  }
  cout << s.substr(1, s.length()) << endl;
  */
  //insertSort();
  quickSort(s, 0, s.size() - 1);
  //for (auto v: s) {
  //  cout << v << endl;
  //}
  cout << (1 << 32) << endl;
  cout << (~0 ^ (1 << 32)) << endl;
};
