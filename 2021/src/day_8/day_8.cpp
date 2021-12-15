//
// Created by alexey on 08.12.2021.
//


#include <iostream>

#include "SevenSegmentSearch.h"


int main()
{
  std::cout << "Day 8: Seven Segment Search\n";

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  int resultTest1 = SevenSegmentSearch().task_1( INPUT_FILES "/day_8/test_1.txt" );;
  std::cout << "Res for TEST 1: " << resultTest1 << std::endl;

  int resultTest2 = SevenSegmentSearch().task_1( INPUT_FILES "/day_8/task_1.txt" );;
  std::cout << "Res for TASK 1: " << resultTest2 << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  int resultTest1_2 = SevenSegmentSearch().task_2( INPUT_FILES "/day_8/test_1.txt" );;
  std::cout << "Res for TEST 2: " << resultTest1_2 << std::endl;

  int resultTest2_2 = SevenSegmentSearch().task_2( INPUT_FILES "/day_8/task_1.txt" );;
  std::cout << "Res for TASK 2: " << resultTest2_2 << std::endl;

}