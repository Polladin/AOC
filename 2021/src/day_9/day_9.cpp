//
// Created by alexey on 17.12.2021.
//

#include <iostream>

#include "SmokeBasin.h"


int main()
{
  std::cout << "Day 9: Smoke Basin\n";

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  int resultTest1 = SmokeBasin().task_1( INPUT_FILES "/day_9/test_1.txt" );;
  std::cout << "Res for TEST 1: " << resultTest1 << std::endl;

  int resultTest2 = SmokeBasin().task_1( INPUT_FILES "/day_9/task_1.txt" );;
  std::cout << "Res for TASK 1: " << resultTest2 << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  int resultTest1_2 = SmokeBasin().task_2( INPUT_FILES "/day_9/test_1.txt" );;
  std::cout << "Res for TEST 2: " << resultTest1_2 << std::endl;

  int resultTest2_2 = SmokeBasin().task_2( INPUT_FILES "/day_9/task_1.txt" );;
  std::cout << "Res for TASK 2: " << resultTest2_2 << std::endl;

}