#!/bin/bash
#SBATCH -n 1
#SBATCH -p normal
#SBATCH -o hw1_b_col_major_out.txt
#SBATCH -t 00:60:00
./hw1 0
