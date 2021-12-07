//
// Created by alexey on 07.12.2021.
//

#include <iostream>

#include "Lanternfish.h"

static std::vector< int > task_1_data {5,1,1,4,1,1,4,1,1,1,1,1,1,1,1,1,1,1,4,2,1,1,1,3,5,1,1,1,5,4,1,1,1,2,2,1,1,1,2,1,1,1,2,5,2,1,2,2,3,1,1,1,1,1,1,1,1,5,1,1,4,1,1,1,5,4,1,1,3,3,2,1,1,1,5,1,1,4,1,1,5,1,1,5,1,2,3,1,5,1,3,2,1,3,1,1,4,1,1,1,1,2,1,2,1,1,2,1,1,1,4,4,1,5,1,1,3,5,1,1,5,1,4,1,1,1,1,1,1,1,1,1,2,2,3,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,5,1,1,1,1,4,1,1,1,1,4,1,1,1,1,3,1,2,1,2,1,3,1,3,4,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,4,1,1,2,2,1,2,4,1,1,3,1,1,1,5,1,3,1,1,1,5,5,1,1,1,1,2,3,4,1,1,1,1,1,1,1,1,1,1,1,1,5,1,4,3,1,1,1,2,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,3,3,1,2,2,1,4,1,5,1,5,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,5,1,1,1,4,3,1,1,4};


int main()
{
  std::cout << "Day 4: Giant Squid\n";

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  int resultTest1 = Lanternfish().task_1( {3,4,3,1,2}, 80 );
  std::cout << "Res for TEST 1: " << resultTest1 << std::endl;

  int resultTest2 = Lanternfish().task_1( task_1_data, 80 );
  std::cout << "Res for TASK 1: " << resultTest2 << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  long long resultTest1_2 = Lanternfish().task_1( {3,4,3,1,2}, 256 );
  std::cout << "Res for TEST 2: " << resultTest1_2 << std::endl;

  long long resultTest2_2 = Lanternfish().task_1( task_1_data, 256 );
  std::cout << "Res for TASK 2: " << resultTest2_2 << std::endl;

}