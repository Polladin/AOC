
#include <iostream>

#include "oxygen.h"


int main()
{
  std::cout << "Day 14: Space Stoichiometry\n\n";

  auto res = Oxygen().run_part_1( INPUT_FILES "/day_15/part_1.txt" );
  std::cout << "Part 1 Res: " << res << "\n\n";

  std::cin.get();
  return 0;
}