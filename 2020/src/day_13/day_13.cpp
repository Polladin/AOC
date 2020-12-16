//
// Created by alexpall on 16.12.2020.
//

#include <iostream>

#include "shuttle_search.h"


int main()
{
  ShuttleSearch shuttleSearch;

  std::cout << "Res test 1: " << shuttleSearch.task_1( INPUT_FILES "/day_13/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << shuttleSearch.task_1( INPUT_FILES "/day_13/input_1.txt" ) << std::endl;

  std::cout << "Res test 1: " << shuttleSearch.task_2( INPUT_FILES "/day_13/test_1.txt" ) << std::endl;
  std::cout << "Res test 2: " << shuttleSearch.task_2( INPUT_FILES "/day_13/test_2.txt" ) << std::endl;
  std::cout << "Res test 3: " << shuttleSearch.task_2( INPUT_FILES "/day_13/test_3.txt" ) << std::endl;
  std::cout << "Res test 4: " << shuttleSearch.task_2( INPUT_FILES "/day_13/test_4.txt" ) << std::endl;
  std::cout << "Res test 5: " << shuttleSearch.task_2( INPUT_FILES "/day_13/test_5.txt" ) << std::endl;
  std::cout << "Res test 6: " << shuttleSearch.task_2( INPUT_FILES "/day_13/test_6.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << shuttleSearch.task_2( INPUT_FILES "/day_13/input_1.txt" ) << std::endl;
}