
#include <iostream>

#include "orbits.h"


int main()
{
  std::cout << "Day 6: Universal Orbit Map\n\n";


  Orbits orbit;

  //auto res = or.run_part_1( INPUT_FILES "/day_6/example_1.txt" );
  //auto res = or.run_part_1( INPUT_FILES "/day_6/part_1.txt" );
  //auto res = or.run_part_2( INPUT_FILES "/day_6/example_2.txt" );
  auto res = orbit.run_part_2( INPUT_FILES "/day_6/part_1.txt" );
  std::cout << "Res : " << res << "\n";

  std::cout << "\nThe End\n";
  std::cin.get();

  return 0;
}
