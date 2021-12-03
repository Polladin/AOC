//
// Created by alexey on 03.12.2021.
//

#include <iostream>

#include "BinaryDiagnostic.h"


int main()
{
  std::cout << "Day 3: Binary Diagnostic\n";

  BinaryDiagnostic binaryDiagnostic;

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  int resultTest1 = binaryDiagnostic.task_1( INPUT_FILES "/day_3/test_1.txt" );;
  std::cout << "Res for TEST 1: " << resultTest1 << std::endl;

  int resultTask1 = binaryDiagnostic.task_1( INPUT_FILES "/day_3/task_1.txt" );;
  std::cout << "Res for TASK 1: " << resultTask1 << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  int resultTest2 = binaryDiagnostic.task_2( INPUT_FILES "/day_3/test_1.txt" );;
  std::cout << "Res for TEST 2: " << resultTest2 << std::endl;

  int resultTask2 = binaryDiagnostic.task_2( INPUT_FILES "/day_3/task_1.txt" );;
  std::cout << "Res for TASK 2: " << resultTask2 << std::endl;
}