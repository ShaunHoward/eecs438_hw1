/*

EECS 438, HW1

Run either a standard row-major order or row-major order for m_one and column-major order for m_two matrix multiplication.
It starts with a square matrix of N=2000 and increases each dimension by 100 over 10 loops.
Matrices contain generated double-precision floating point numbers.
The first and only argument is either 1 for row major or 0 for mixed row/column major.

author: Shaun Howard (smh150@case.edu)

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define bool values
typedef int bool;
#define true 1
#define false 0

bool PRINT_OUTPUTS = false;


void mat_mul(double* m_one, double* m_two, double* m_product, bool row_major, int n_rows_one,
		     int n_cols_one, int n_rows_two, int n_cols_two) {
	int i, j, k;

	if (n_rows_two != n_cols_one){
		// sanity check to see if matrices can be multiplied
		printf("Inner matrix dimensions are not the same, cannot continue.");
		return;
	}

	if (PRINT_OUTPUTS) {
		// print out first input matrix
		printf("First input matrtix:\n");
		for(i = 0; i < n_rows_one; i++){
		    for(j = 0; j < n_cols_one; j++){
			    printf("%f ", m_one[i*n_cols_one+j]);
		    }
		    printf("\n");
		}

		printf("\n");

		// print out first input matrix
		printf("Second input matrix:\n");
		for(i = 0; i < n_rows_two; i++){
		    for(j = 0; j < n_cols_two; j++){
			    printf("%f ", m_two[i*n_cols_two+j]);
		    }
		    printf("\n");
		}
		printf("\n");
	}

	// begin timer
	clock_t begin = clock();

	if (row_major == true) {
		// Multiply m_one and m_two using row-major indexing order
		// offset = (row x NUM_COLS) + col
		for(i = 0; i < n_rows_one; i++){
		    for(j = 0; j < n_cols_two; j++){
		    	// initialize product value at i,j to 0.0
		    	m_product[i*n_cols_two+j] = 0.0;
   				for(k = 0; k < n_rows_two; k++){
   					// here, we know n_cols_one == n_rows_two
					m_product[i*n_cols_two+j] += m_one[i*n_cols_one+k] * m_two[k*n_cols_two+j];
				}
			} 
		}
	} else {
		// Multiply m_one with row-major order and m_two with column-major order
		// offset = (col x NUM_ROWS) + row
		for(i = 0; i < n_rows_one; i++){
		    for(j = 0; j < n_cols_two; j++){
		    	// initialize product value at i,j to 0.0
		    	m_product[i*n_cols_two+j] = 0.0;
		    	double *col = &m_two[j*n_rows_two];
   				for(k = 0; k < n_rows_two; k++){
					m_product[i*n_cols_two+j] += m_one[i*n_cols_one+k] * col[k];
					//m_product[i*n_cols_two+j] += m_one[i*n_cols_one+k] * m_two[j*n_rows_two+k];
				} 
		    }
		}
	}

	// stop timer
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	if (time_spent < 0.01)
		printf("Matrix multiplication of matrices took %.5f milliseconds.\n", time_spent*1000);
	else
		printf("Matrix multiplication of matrices took %.5f seconds.\n", time_spent);


	if (PRINT_OUTPUTS){
		// print out the product matrix
		printf("Output Product Matrix\n");
		for(i = 0; i < n_rows_one; i++){
		    for(j = 0; j < n_cols_two; j++){
			    printf("%f ", m_product[i*n_cols_two+j]);
		    }
		    printf("\n");
		}
		printf("\n");
	}
	return;
}
 
int main(int argc, char *argv[]){
	/*
	Run either a standard row-major order or row-major order for m_one and column-major order for m_two matrix multiplication.
	It starts with a square matrix of N=2000 and increases each dimension by 100 over 10 loops.
	Matrices contain generated double-precision floating point numbers.
	The first and only argument is either 1 for row major or 0 for mixed row/column major.
	*/
	int main_loop_counter = 0;
	int starting_matrix_size = 2000;
	int mat_size_incr = 100;
	int n_loops = 10;
	int i, j;
    int curr_mat_size = starting_matrix_size;
    bool row_major = atoi(argv[1]);

    if (row_major)
	    printf("Starting matrix multiplication with row-major indexing.\n");
	else
	    printf("Starting matrix multiplication with row-major indexing for m_one and column-major indexing for m_two.\n");


	for (main_loop_counter=0; main_loop_counter < n_loops; main_loop_counter++) {
	    // multiply all matrices in chosen order and time MM operations
	    // increase the matrix size by mat_size_incr after each loop

     	// store matrix sizes
		int n_rows_one = curr_mat_size, n_cols_one = curr_mat_size;
		int n_rows_two = curr_mat_size, n_cols_two = curr_mat_size;

	    // create curr_mat_size x curr_mat_size matrix arrays
		double* m_one = malloc(sizeof(double) * n_rows_one * n_cols_one);
		double* m_two = malloc(sizeof(double) * n_rows_two * n_cols_two);
		double* m_product = malloc(sizeof(double) * n_rows_one * n_cols_two);

		// initialize arrays with somewhat random, but predictable values
		for(i=0; i<n_rows_one;i++)
			for(j=0; j<n_cols_one; j++)
                m_one[i*n_cols_one+j]=i+j;


        if (row_major == true) {
	        // use same initialization as for m_one, but add one to each value, in row major order
			for(i=0; i<n_rows_two;i++)
				for(j=0; j<n_cols_two;j++)
	                m_two[i*n_cols_two+j]=i+j+1;
	    } else {
	        // use same initialization as for m_one, but add one to each value, in column-major order
			for(j=0; j<n_cols_two;j++)
				for(i=0; i<n_rows_two;i++)
	                m_two[j*n_rows_two+i]=i+j+1;
	    }

		// compute matrix multiplication
		mat_mul(m_one, m_two, m_product, row_major, n_rows_one, n_cols_one, n_rows_two, n_cols_two);
		free(m_one);
		free(m_two);
		free(m_product);
		curr_mat_size += mat_size_incr;
	}

    return 0;
}
