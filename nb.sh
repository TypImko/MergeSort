#!/bin/sh
g++ nbody.cpp -o nb
./nb 8 200 5000000 5000000
./nb 100 1 10000 10000
./nb 1000 1 10000 10000