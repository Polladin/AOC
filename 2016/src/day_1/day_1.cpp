
#include <iostream>

#include "bunny_hq.h"


int main()
{
  std::cout << "Day 6: Universal Orbit Map\n\n";

  BunnyHQ bhq;
  auto res = bhq.run_part_1( INPUT_FILES "/day_1/part_1.txt" );
  std::cout << "Res: " << res << "\n";

  std::cout << "\nThe End\n";
  std::cin.get();
  return 0;
}