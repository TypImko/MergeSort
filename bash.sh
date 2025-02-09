!/bin/sh
#SBATCH --MergeSortJob
#SBATCH --partition=Centaurus
#SBATCH --time=00:10:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1

#This script will be read be SLURM for arguments, executed by the requested nodes.
work
