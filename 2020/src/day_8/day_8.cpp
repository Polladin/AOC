//
// Created by alexpall on 08.12.2020.
//

#include "handheld_halting.h"

#include <iostream>


int main()
{
  std::cout << "Day 1: Report Repair\n";

  HandheldHalting handheldHalting;

  std::cout << "Res test 1: " << handheldHalting.task_1( INPUT_FILES "/day_8/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << handheldHalting.task_1( INPUT_FILES "/day_8/input_1.txt" ) << std::endl;


  std::cout << "Res test 2: " << handheldHalting.task_2( INPUT_FILES "/day_8/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << handheldHalting.task_2( INPUT_FILES "/day_8/input_1.txt" ) << std::endl;
}