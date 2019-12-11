
#include <iostream>

#include "asteroids_base.h"


int main()
{
  std::cout << "Day 10: Monitoring Station\n\n";

  AsteroidsBase ab;

  //std::cout << "GCD: " << ab.gcd( -12, -8 ) << "\n";
  auto res = AsteroidsBase().run_part_1( INPUT_FILES "/day_10/part_1.txt" );
  std::cout << "Res: " << res.first << "  Coord: " << res.second.X << " : " << res.second.Y << "\n\n";

  auto res2 = AsteroidsBase().run_part_2( INPUT_FILES "/day_10/part_1.txt", res.second );

  std::cin.get();
  return 0;
}