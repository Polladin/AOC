#!/bin/sh


# Create folders with year/src/day_X/ and year/input/day_X/
# mkdir %1/%2/
echo "Create files for year:$1 day:day_$2"

mkdir $1/input/day_$2
mkdir $1/src/day_$2

touch $1/src/day_$2/day_$2.cpp
touch $1/input/day_$2/test_1.txt
touch $1/input/day_$2/task_1.txt
