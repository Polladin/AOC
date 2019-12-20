
#include <iostream>

#include "scaffold.h"


int main()
{
  std::cout << "Day 16: Flawed Frequency Transmission\n\n";

  auto res = Scaffold().run_part_2( INPUT_FILES "/day_17/part_1.txt" );
  std::cout << "Result : " << res << "\n";

  std::cin.get();
  return 0;
}
