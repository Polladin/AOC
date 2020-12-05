//
// Created by alexpall on 05.12.2020.
//


#include "binary_boarding.h"

#include <iostream>


int main()
{
  std::cout << "Day 1: Report Repair\n";

  BinaryBoarding binaryBoarding;

  std::cout << "Res test 1: " << binaryBoarding.task_1( INPUT_FILES "/day_5/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << binaryBoarding.task_1( INPUT_FILES "/day_5/input_1.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << binaryBoarding.task_2( INPUT_FILES "/day_5/input_1.txt" ) << std::endl;
}