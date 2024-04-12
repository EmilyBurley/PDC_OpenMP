#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

const int N = 100000;

// An `entry` represents a value in an array, storing both
// the value itself as well as the value's index in the array.
typedef struct entry {
  int index;
  int value;
} entry;

entry INIT_ENTRY = { -1, INT_MAX };

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selection_sort(int *data) {
  entry iter_min;

  for (int i = 0; i < N; i++) {
    iter_min.index = i;
    iter_min.value = data[i];

    for (int j = i + 1; j < N; j++) {
      if (data[j] < iter_min.value) {
        iter_min.value = data[j];
        iter_min.index = j;
      }
    }

    swap(&data[i], &data[iter_min.index]);
  }
}

int main() {

  struct timespec start, stop;

  // initialize the input array to all random values
  int* data = (int*)malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    data[i] = random() % (N * 10);
    //data[i] = rand() % 100;
  }

  clock_gettime(CLOCK_REALTIME, &start);
  selection_sort(data);
  clock_gettime(CLOCK_REALTIME, &stop);

  // check that the array is sorted in increasing order
  // by comparing each pair of consecutive elements
  int valid = 1;
  for (int i = 1; i < N; i++) {
    valid = valid && (data[i] >= data[i - 1]);
  }

  double duration = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 1e9;

  printf("Result valid: %s\n", valid ? "yes" : "no");
  printf("Values sorted: %d\n", N);
  printf("Duration: %.6f seconds\n", duration);
}
