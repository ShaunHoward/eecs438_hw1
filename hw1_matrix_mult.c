/*

EECS 438 HW1

Standard matrix multiplication using row-major and column-major order.

Shaun Howard (smh150@case.edu)

*/

#include <stdio.h>
#include <time.h>


/*
ADD TIMING CODE!!
*/

mat_mul(double* m_one, double* m_two, double* m_product, bool row_major) {
	int i, j, k;

	// begin timer
	clock_t begin = clock();

	if (row_major == true) {}
		// Multiply m_one and m_two using row major indexing order
		// offset = (row x NUM_COLS) + col
		for(i = 0; i < n_rows_one; i++){
		    for(j = 0; j < n_cols_two; j++){
   				for(k = 0; k < n_rows_two; k++){
					m_product[i*n_cols_two+k] += m_one[i*n_cols_one+k] * m_two[k*n_cols_two+j];
				}
			} 
		}
	} else {
		// Multiply m_one and m_two using column major indexing order for array B
		// offset = (col x NUM_ROWS) + row
		for(i = 0; i < n_rows_one; i++){
			for(k = 0; k < n_rows_two; k++){
			    for(j = 0; j < n_cols_two; j++){
					m_product[i*n_cols_two+k] += m_one[i*n_cols_one+k] * m_two[j*n_rows_two+k];
				} 
		    }
		}
	}

	// stop timer
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Matrix multiplication of matrices took %.3f seconds.\n", time_spent);

	// print out the product matrix
	printf("Output Product Matrix\n");
	for(i = 0; i < n_rows_one; i++){
	    for(j = 0; j < n_cols_two; j++){
		    printf("%d ", m_product[i][j]);
	    }
	    printf("\n");
	}
}
 
int main(){
	int main_loop_counter = 0;
	int starting_matrix_size = 50;
	int n_loops = 10:

	for (main_loop_counter=0; main_loop_counter < n_loops; main_loop_counter++) {
	    // multiply all matrices in row major and time MM operations
	    // increase the matrix size during each loop, building up to starting_size * n_loops
	    int curr_mat_size = starting_matrix_size * (main_loop_counter+1) 
		double* m_one = malloc(sizeof(double) * curr_mat_size * curr_mat_size);
		double* m_one = malloc(sizeof(double) * curr_mat_size * curr_mat_size);

		double m_product[n_rows_one][n_cols_two] = {0.0};
		int n_rows_one, n_cols_one;
		int n_rows_two, n_cols_two;

		mat_mul(m_one, m_two, m_product, true);

	for (main_loop_counter=0; main_loop_counter < n_loops; main_loop_counter++) {
	    // multiply all matrices in column major and time MM operations
	    // increase the matrix size during each loop, building up to starting_size * n_loops
		    int curr_mat_size = starting_matrix_size * (main_loop_counter+1) 
		double* m_one = malloc(sizeof(double) * curr_mat_size * curr_mat_size);
		double* m_one = malloc(sizeof(double) * curr_mat_size * curr_mat_size);

		double m_product[n_rows_one][n_cols_two] = {0.0};
		int n_rows_one, n_cols_one;
		int n_rows_two, n_cols_two;

		mat_mul(m_one, m_two, m_product, false);

    return 0;
}
