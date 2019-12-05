
#include <iostream>

#include "total_fuel.h"


int main()
{
  std::cout << "Day 1: The Tyranny of the Rocket Equation\n";

  TotalFuel tf;
  //tf.run_part_2( INPUT_FILES "/day_1/examples.txt" );
  tf.run_part_2( INPUT_FILES "/day_1/part_1.txt" );

  std::cin.get();
}