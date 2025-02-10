#!/bin/sh
#This script will be read be SLURM for arguments, executed by the requested nodes.
g++ ms.cpp -o Merge
./Merge 10
./Merge 100
./Merge 1000
./Merge 10000
./Merge 100000
./Merge 1000000
./Merge 10000000
./Merge 100000000
./Merge 1000000000