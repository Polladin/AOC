
#include <iostream>

#include "jupiter.h"


int main()
{

  std::cout << "Day 12: The N-Body Problem\n\n";

  //std::cout << "GCD: " << ab.gcd( -12, -8 ) << "\n";
  //auto res = Jupiter().run_part_2( INPUT_FILES "/day_12/part_2.txt" );
  auto res = Jupiter().run_part_2( INPUT_FILES "/day_12/example_2.txt" );
  std::cout << "Res: " << res << "\n\n";

  //auto res2 = AsteroidsBase().run_part_2( INPUT_FILES "/day_10/part_1.txt", res.second );

  std::cin.get();
  return 0;
}