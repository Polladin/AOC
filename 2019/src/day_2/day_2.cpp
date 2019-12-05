
#include "computer.h"

#include <iostream>


int main()
{
  std::cout << "Day 2: 1202 Program Alarm\n";

  Computer comp;

  // int res = comp.run_part_1( INPUT_FILES "/day_2/examples.txt" );
  // int res = comp.run_part_1( INPUT_FILES "/day_2/part_1.txt" );
  int res = comp.run_part_2( INPUT_FILES "/day_2/part_1.txt", 19690720 );
  std::cout << "Res: " << res << "\n";


  std::cout << "The End\n";
  std::cin.get();
}