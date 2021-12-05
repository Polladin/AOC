//
// Created by alexey on 04.12.2021.
//


#include <iostream>

#include "GiantSquid.h"


int main()
{
  std::cout << "Day 4: Giant Squid\n";

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  int resultTest1 = GiantSquid().task_1( INPUT_FILES "/day_4/test_1.txt" );;
  std::cout << "Res for TEST 1: " << resultTest1 << std::endl;

  int resultTest2 = GiantSquid().task_1( INPUT_FILES "/day_4/task_1.txt" );;
  std::cout << "Res for TASK 1: " << resultTest2 << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  int resultTest1_2 = GiantSquid().task_2( INPUT_FILES "/day_4/test_1.txt" );;
  std::cout << "Res for TEST 2: " << resultTest1_2 << std::endl;

  int resultTest2_2 = GiantSquid().task_2( INPUT_FILES "/day_4/task_1.txt" );;
  std::cout << "Res for TASK 2: " << resultTest2_2 << std::endl;

}