//
// Created by alexey on 01.12.2021.
//

#include <iostream>

#include "SonarSweep.h"


int main()
{
  std::cout << "Day 1: Sonar sweep\n";

  SonarSweep sonar;

  std::cout << "Res for TEST 1: " << sonar.task_1( INPUT_FILES "/day_1/test_1.txt" ) << std::endl;
  std::cout << "Res for TASK 1: " << sonar.task_1( INPUT_FILES "/day_1/task_1.txt" ) << std::endl;

  std::cout << "TASK 2:\n";

  std::cout << "Res for TEST 2: " << sonar.task_2( INPUT_FILES "/day_1/test_1.txt" ) << std::endl;
  std::cout << "Res for TASK 2: " << sonar.task_2( INPUT_FILES "/day_1/task_1.txt" ) << std::endl;
}
