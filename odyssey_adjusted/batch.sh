#!/bin/bash
#SBATCH --job-name=sudoku_mpi
#SBATCH -n 64 # Number of cores requested
#SBATCH -N 8  # number of nodes
#SBATCH -t 0-00:10 # Runtime in d-HH:MM
#SBATCH -p shared # Partition to submit to
#SBATCH --mem-per-cpu=8000 # Memory per cpu in MB (see also--mem)
#SBATCH -o job_%j.out # Standard out goes to this file
#SBATCH -e job_%j.err # Standard err goes to this file
#SBATCH --mail-type=all # notifications for job done & fail 
##SBATCH --mail-user=<youremail@your.domain> # send-to address

source new-modules.sh
module load gcc/4.8.2-fasrc01 
module load openmpi/1.10.4-fasrc01

mpirun -np $SLURM_NTASKS ./run > sudoku.out
