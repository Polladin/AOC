//
// Created by alexey on 18.12.2020.
//


#include <iostream>

#include "docking_data.h"


int main()
{
  DockingData dockingData;

  std::cout << "Res test 1: " << dockingData.task_1( INPUT_FILES "/day_14/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << dockingData.task_1( INPUT_FILES "/day_14/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << dockingData.task_2( INPUT_FILES "/day_14/test_2.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << dockingData.task_2( INPUT_FILES "/day_14/input_1.txt" ) << std::endl;

}
