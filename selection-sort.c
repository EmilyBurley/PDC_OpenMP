#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "omp.h"

const int N = 100000;

// An `entry` represents a value in an array, storing both
// the value itself as well as the value's index in the array.
typedef struct entry {
  int index;
  int value;
} entry;

entry INIT_ENTRY = { -1, INT_MAX };

// The custom reduction behavior for `entry` values.
#pragma omp declare reduction(min_entry : entry : \
  omp_out = omp_in.value < omp_out.value ? omp_in : omp_out) \
  initializer(omp_priv={-1,INT_MAX})

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

    #pragma omp parallel for reduction(min_entry:iter_min)
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
  // initialize the input array to all random values
  int* data = (int*)malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    data[i] = random() % (N * 10);
    //data[i] = rand() % 100;
  }

  double start = omp_get_wtime();
  selection_sort(data);
  double duration = omp_get_wtime() - start;

  // check that the array is sorted in increasing order
  // by comparing each pair of consecutive elements
  int valid = 1;
  for (int i = 1; i < N; i++) {
    valid = valid && (data[i] >= data[i - 1]);
  }

  printf("Result valid: %s\n", valid ? "yes" : "no");
  printf("Values sorted: %d\n", N);
  printf("Duration: %.6f seconds\n", duration);
}
