
#include <iostream>

#include "stoichiometry.h"


int main()
{
  std::cout << "Day 14: Space Stoichiometry\n\n";

  auto res = Stoichiometry().run_part_2( INPUT_FILES "/day_14/example_3.txt" );
  std::cout << "Ex 3 Res: " << res << "\n\n";

  res = Stoichiometry().run_part_2( INPUT_FILES "/day_14/example_4.txt" );
  std::cout << "Ex 4 Res: " << res << "\n\n";

  res = Stoichiometry().run_part_2( INPUT_FILES "/day_14/example_5.txt" );
  std::cout << "Ex 5 Res: " << res << "\n\n";

  res = Stoichiometry().run_part_2( INPUT_FILES "/day_14/part_1.txt" );
  std::cout << "Part 1 Res: " << res << "\n\n";

  std::cin.get();
  return 0;
}