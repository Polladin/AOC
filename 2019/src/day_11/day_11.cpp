
#include <iostream>

#include "painting_robots.h"


int main()
{
  std::cout << "Day 11: Space Police\n\n";

  auto res = PaintingRobots().run_part_1( INPUT_FILES "/day_11/part_1.txt" );
  std::cout << "Res : " << res << "\n\n";

  std::cin.get();
  return 0;
}