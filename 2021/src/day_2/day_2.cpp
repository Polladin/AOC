//
// Created by alexey on 02.12.2021.
//

#include <iostream>

#include "Dive.h"


int main()
{
  std::cout << "Day 2: Dive\n";

  Dive dive;

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  std::cout << "Res for TEST 1: " << dive.task_1( INPUT_FILES "/day_2/test_1.txt" ) << std::endl;
  std::cout << "Res for TASK 1: " << dive.task_1( INPUT_FILES "/day_2/task_1.txt" ) << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  std::cout << "Res for TEST 2: " << dive.task_2( INPUT_FILES "/day_2/test_1.txt" ) << std::endl;
  std::cout << "Res for TASK 2: " << dive.task_2( INPUT_FILES "/day_2/task_1.txt" ) << std::endl;
}