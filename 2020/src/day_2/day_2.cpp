//
// Created by alexpall on 02.12.2020.
//

#include <iostream>

#include "password_philosophy.h"


int main()
{
  std::cout << "Day 1: Report Repair\n";

  PasswordPhilosophy passwordPhilosophy;

  std::cout << "Res test 1: " << passwordPhilosophy.task_1( INPUT_FILES "/day_2/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 1: " << passwordPhilosophy.task_1( INPUT_FILES "/day_2/input_1.txt" ) << std::endl;

  std::cout << "Res test 2: " << passwordPhilosophy.task_2( INPUT_FILES "/day_2/test_1.txt" ) << std::endl;
  std::cout << "Res TASK 2: " << passwordPhilosophy.task_2( INPUT_FILES "/day_2/input_1.txt" ) << std::endl;
}