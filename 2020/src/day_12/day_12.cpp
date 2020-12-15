//
// Created by alexpall on 16.12.2020.
//

#include "rain_risk.h"

#include <iostream>


int main()
{
  RainRisk rainRisk;

  std::cout << "Res test 1: " << rainRisk.task_1( INPUT_FILES "/day_12/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << rainRisk.task_1( INPUT_FILES "/day_12/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << rainRisk.task_2( INPUT_FILES "/day_12/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << rainRisk.task_2( INPUT_FILES "/day_12/input_1.txt" ) << std::endl;

}