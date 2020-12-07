//
// Created by alexpall on 07.12.2020.
//

#include "custom_customs.h"

#include <iostream>


int main()
{
  std::cout << "Day 1: Report Repair\n";

  CustomCustoms customCustoms;

  std::cout << "Res test 1: " << customCustoms.task_1( INPUT_FILES "/day_6/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << customCustoms.task_1( INPUT_FILES "/day_6/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << customCustoms.task_2( INPUT_FILES "/day_6/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << customCustoms.task_2( INPUT_FILES "/day_6/input_1.txt" ) << std::endl;
}