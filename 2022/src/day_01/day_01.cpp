
#include <iostream>

#include "calorie_counting.h"

int main()
{
  std::cout << "Day 1: Calorie Counting\n";

  std::cout << "\n------------------- TASK 1: -------------------\n\n";

  int resultTest1 = CalorieCounting().part_1( INPUT_FILES "/day_01/test_1.txt" );
  std::cout << "Res for TEST 1: " << resultTest1 << std::endl;

  int resultTask1 = CalorieCounting().part_1( INPUT_FILES "/day_01/task_1.txt" );
  std::cout << "Res for TASK 1: " << resultTask1 << std::endl;

  std::cout << "\n------------------- TASK 2: -------------------\n\n";

  int resultTest1_2 = CalorieCounting().part_2( INPUT_FILES "/day_01/test_1.txt" );
  std::cout << "Res for TEST 1: " << resultTest1_2 << std::endl;

  int resultTask1_2 = CalorieCounting().part_2( INPUT_FILES "/day_01/task_1.txt" );
  std::cout << "Res for TASK 1: " << resultTask1_2 << std::endl;
}
