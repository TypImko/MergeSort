!/bin/sh
#This script will be read be SLURM for arguments, executed by the requested nodes.
make ms
./ms > Merge_Answer
