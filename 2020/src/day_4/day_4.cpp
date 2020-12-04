//
// Created by alexpall on 04.12.2020.
//

#include "passport_processing.h"

#include <iostream>


int main()
{
  std::cout << "Day 1: Report Repair\n";

  PassportProcessing passportProcessing;

  std::cout << "Res test 1: " << passportProcessing.task_1( INPUT_FILES "/day_4/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << passportProcessing.task_1( INPUT_FILES "/day_4/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << passportProcessing.task_2( INPUT_FILES "/day_4/test_2.txt" ) << std::endl;
  std::cout << "Res test 3: " << passportProcessing.task_2( INPUT_FILES "/day_4/test_3.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << passportProcessing.task_2( INPUT_FILES "/day_4/input_2.txt" ) << std::endl;
}