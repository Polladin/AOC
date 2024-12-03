#!/bin/sh


# Create folders with year/src/day_X/ and year/input/day_X/
# mkdir %1/%2/
echo "Create files for year:2024 day:day_$1"

mkdir 2024/input/day_$1
mkdir 2024/src/day_$1

touch 2024/src/day_$1/day_$1.cpp
touch 2024/src/day_$1/$2.cpp
touch 2024/src/day_$1/$2.h
touch 2024/input/day_$1/test_1.txt
touch 2024/input/day_$1/task_1.txt
