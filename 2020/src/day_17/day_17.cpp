//
// Created by alexey on 23.12.2020.
//

#include <iostream>

#include "conway_cubes.h"


int main()
{
  ConwayCubes conwayCubes;

  std::cout << "Res test 1: " << conwayCubes.task_1( INPUT_FILES "/day_17/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << conwayCubes.task_1( INPUT_FILES "/day_17/input_1.txt" ) << std::endl;

//  std::cout << "Res TASK 2: " << ticketTranslation.task_2( INPUT_FILES "/day_16/test_2.txt" ) << std::endl;
//  std::cout << "Res TASK 2: " << ticketTranslation.task_2( INPUT_FILES "/day_16/input_1.txt" ) << std::endl;
}
