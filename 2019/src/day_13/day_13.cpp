
#include <iostream>

#include "game.h"


int main()
{
  std::cout << "Day 13: Care Package\n\n";

  auto res = Game().run_part_2( INPUT_FILES "/day_13/part_1.txt" );
  std::cout << "Res: " << res << "\n\n";

  std::cin.get();
  return 0;
}