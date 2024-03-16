#include <omp.h>
#include <stdio.h>

int main() {
  int nthreads, tid;

  #pragma omp parallel private(tid)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("%d threads forked in total.\n", nthreads);
    }

    printf("Hello World from thread %d\n", tid);
  }
}
