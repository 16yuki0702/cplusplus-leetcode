#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// https://www.hackerearth.com/practice/notes/heaps-and-priority-queues/

void max_heapify(int arr[], int i, int N) {
  int left = 2 * i;
  int right = 2 * i + 1;
  int largest = -1;
  if (left <= N && arr[left] > arr[i]) {
    largest = left;
  } else {
    largest = i;
  }
  if (right <= N && arr[right] > arr[largest]) {
    largest = right;
  }
  if (largest != i) {
    swap(arr[i], arr[largest]);
    max_heapify(arr, largest, N);
  }
}

void min_heapify(int arr[], int i, int N) {
  int left = 2 * i;
  int right = 2 * i + 1;
  int smallest = -1;
  if (left <= N && arr[left] < arr[i]) {
    smallest = left;
  } else {
    smallest = i;
  }
  if (right <= N && arr[right] < arr[smallest]) {
    smallest = right;
  }
  if (smallest != i) {
    swap(arr[i], arr[smallest]);
    min_heapify(arr, smallest, N);
  }
}

void call_max_heapify() {
  printf("max_heapify : start\n");

  // first element is dummy
  int arr[] = {-1, 1, 4, 3, 7, 8, 9, 10};
  int N = sizeof(arr) / sizeof(arr[0]) - 1;

  for (auto a : arr) {
    printf("%d ", a);
  }
  printf("\n");

  for (int i = N / 2; i >= 1; i--) {
    max_heapify(arr, i, N);
  }

  for (auto a : arr) {
    printf("%d ", a);
  }
  printf("\n");
  printf("max_heapify : end\n\n");
}

void call_min_heapify() {
  printf("min_heapify : start\n");

  // first element is dummy
  int arr[] = {-1, 10, 8, 9, 7, 6, 5, 4};
  int N = sizeof(arr) / sizeof(arr[0]) - 1;

  for (auto a : arr) {
    printf("%d ", a);
  }
  printf("\n");

  for (int i = N / 2; i >= 1; i--) {
    min_heapify(arr, i, N);
  }

  for (auto a : arr) {
    printf("%d ", a);
  }
  printf("\n");
  printf("min_heapify : end\n\n");
}

int main(int argc, char *argv[]) {
  call_max_heapify();
  call_min_heapify();
};
