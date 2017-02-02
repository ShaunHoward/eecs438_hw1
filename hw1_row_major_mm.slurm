#!/bin/bash
#SBATCH -n 1
#SBATCH -p normal
#SBATCH -o=hw1_row_major_out.txt
#SBATCH -t 00:10:00
./hw1_matrix_mult 1
