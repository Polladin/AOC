//
// Created by alexpall on 09.12.2020.
//

#include "encoding_error.h"

#include <iostream>


int main()
{
  EncodingError encodingError;

  std::cout << "Res test 1: " << encodingError.task_1(INPUT_FILES "/day_9/test_1.txt", 5) << std::endl;
  std::cout << "Res TASK 1: " << encodingError.task_1(INPUT_FILES "/day_9/input_1.txt") << std::endl;

//  std::cout << "Res test 2: " << encodingError.task_2(INPUT_FILES "/day_9/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << encodingError.task_2(INPUT_FILES "/day_9/input_1.txt") << std::endl;
}