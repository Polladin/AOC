//
// Created by alexpall on 10.12.2020.
//

#include "adapter_array.h"

#include <iostream>


int main()
{
  AdapterArray adapterArray;

  std::cout << "Res test 1: " << adapterArray.task_1( INPUT_FILES "/day_10/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << adapterArray.task_1( INPUT_FILES "/day_10/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << adapterArray.task_2( INPUT_FILES "/day_10/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << adapterArray.task_2( INPUT_FILES "/day_10/input_1.txt" ) << std::endl;

}