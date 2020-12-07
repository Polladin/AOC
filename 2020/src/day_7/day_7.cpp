//
// Created by alexpall on 07.12.2020.
//


#include "handy_haversacks.h"

#include <iostream>


int main()
{
  std::cout << "Day 1: Report Repair\n";

  HandyHaversacks handyHaversacks;

  std::cout << "Res test 1: " << handyHaversacks.task_1( INPUT_FILES "/day_7/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << handyHaversacks.task_1( INPUT_FILES "/day_7/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << handyHaversacks.task_2( INPUT_FILES "/day_7/test_1.txt" ) << std::endl;
  std::cout << "Res test 3: " << handyHaversacks.task_2( INPUT_FILES "/day_7/test_2.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << handyHaversacks.task_2( INPUT_FILES "/day_7/input_1.txt" ) << std::endl;

}