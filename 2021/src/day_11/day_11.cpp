//
// Created by alexey on 21.12.2021.
//

#include "DumboOctopus.h"

#include <iostream>

int main()
{
  std::cout << "Day 11: Dumbo Octopus\n";

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  int resultTest1 = DumboOctopus().task_1( INPUT_FILES "/day_11/test_1.txt" );;
  std::cout << "Res for TEST 1: " << resultTest1 << std::endl;

  int resultTest2 = DumboOctopus().task_1( INPUT_FILES "/day_11/task_1.txt" );;
  std::cout << "Res for TASK 1: " << resultTest2 << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  int resultTest1_2 = DumboOctopus().task_2( INPUT_FILES "/day_11/test_1.txt" );;
  std::cout << "Res for TEST 2: " << resultTest1_2 << std::endl;

  int resultTest2_2 = DumboOctopus().task_2( INPUT_FILES "/day_11/task_1.txt" );;
  std::cout << "Res for TASK 2: " << resultTest2_2 << std::endl;

}