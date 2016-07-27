#include <stdlib.h>
#include <stdio.h>

#include "rational.c"

#define BUFFER_SIZE (10)

int fm_elim(int rows, int cols, rational* A, rational* c) {
  rational* data_A, *data_c;
  int k, n, part_ind=0, partition_size_A = rows*cols*BUFFER_SIZE, partition_size_c = rows*BUFFER_SIZE;

  data_A = calloc(partition_size_A*2, sizeof(rational));
  data_c = calloc(partition_size_c*2, sizeof(rational));

  for (k = 0; k < rows; k++) {
    for (n = 0; n < cols; n++) {
      data_A[part_ind*partition_size_A + k*cols + n] = A[k*cols + n];
    }
    data_c[part_ind*partition_size_c + k] = c[k];
  }

  free(data_A);
  free(data_c);
  return 1;
}
