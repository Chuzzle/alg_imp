#include <stdlib.h>
#include <stdio.h>

#include "rational.c"

#define BUFFER_SIZE (10)

int fm_elim(int rows, int cols, rational* A, rational* c) {
  rational* data_A, *data_c, *working_number;
  int k, n, k_new, k2, part_ind = 0, partition_size_A = rows*cols*BUFFER_SIZE, partition_size_c = rows*BUFFER_SIZE;
  int indicators[rows*BUFFER_SIZE], num_lower, num_upper, rows_new=0, cols_new;

  data_A = calloc(partition_size_A*2, sizeof(rational)); //The matrices have two partitions, so two matrices can be accessed simultaneously.
  data_c = calloc(partition_size_c*2, sizeof(rational));
  // Copying the initial matrices into the working matrices
  for (k = 0; k < rows; k++) {
    for (n = 0; n < cols; n++) {
      data_A[part_ind*partition_size_A + k*cols + n] = A[k*cols + n];
    }
    data_c[part_ind*partition_size_c + k] = c[k];
  }

  //Start of the algorithm.
  while (cols > 1) {
    num_upper = 0;
    num_lower = 0;
    for (k = 0; k < rows; k++) {
      working_number = &data_A[partition_size_A*part_ind + k*cols + cols];
      printf("%d / %d, cols = %d \n", working_number->enu, working_number->den, cols);
      // Identify which rows have a negative/positive/zero coefficient, to determine which will yield a lower bound and which will yield an upper bound
      if (working_number->enu > 0) {
        num_upper++;
        indicators[k] = 1;
      } else if (working_number->enu < 0) {
        num_lower++;
        indicators[k] = -1;
      } else {
        indicators[k] = 0;
      }
      // On the same loop, divide each coefficient in that row so we have a 1 at the "right" place
      for (n = 0; n < cols; n++) {
        divide(&data_A[partition_size_A*part_ind + k*cols + n], working_number);
      }
      // Same for the c vector
      divide(&data_c[partition_size_c*part_ind + k], working_number);
    }

    // Find the new rows
    rows_new = rows - (num_lower + num_upper) + num_lower*num_upper;
    if (rows_new == 0) {
      free(data_A);
      free(data_c);
      return 1;
    } else if (rows_new >= partition_size_c){
      printf("Out of memory D:");
      exit(1);
    }
    // Construct the new matrix. Note that I will need different row-indices for this.
    k_new = 0;
    cols_new = cols-1;
    for(k = 0; k < rows; k++) {
      if (indicators[k] == 1) {
        for(k2 = 0; k2 < rows; k2++) {
          if (indicators[k2] == -1) {
            for (n = 0; n < cols_new; n++) {
              data_A[(part_ind%2)*partition_size_A + k_new*cols_new + n] = sub(&data_A[part_ind*partition_size_A + k*cols + n], &data_A[part_ind*partition_size_A + k2*cols + n]);
            }
            k_new++;
          }
        }
      } else if (indicators[k] == 0) {
        for (n = 0; n < cols_new; n++) {
          data_A[(part_ind%2)*partition_size_A + k_new*cols_new + n] = data_A[part_ind*partition_size_A + k*cols + n];
          k_new++;
        }
      }
    }
    rows = rows_new;
    cols = cols_new;
    part_ind++;
  }

  free(data_A);
  free(data_c);
  return 1;
}
