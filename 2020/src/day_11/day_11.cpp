//
// Created by alexpall on 13.12.2020.
//

#include "seating_system.h"

#include <iostream>


int main()
{
  SeatingSystem seatingSystem;

  std::cout << "Res test 1: " << seatingSystem.task_1( INPUT_FILES "/day_11/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << seatingSystem.task_1( INPUT_FILES "/day_11/input_1.txt" ) << std::endl;

//  std::cout << "Res test 2: " << seatingSystem.task_2( INPUT_FILES "/day_10/test_1.txt" ) << std::endl;
//  std::cout << "Res TASK 2: " << seatingSystem.task_2( INPUT_FILES "/day_10/input_1.txt" ) << std::endl;

}