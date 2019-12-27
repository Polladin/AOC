
#include <iostream>

#include "beam.h"


int main()
{
  std::cout << "Day 19: Tractor Beam\n\n";

  //auto res = Vault().run_part_2( INPUT_FILES "/day_18/example_9.txt" );
  auto res = Beam().run_part_1( INPUT_FILES "/day_19/part_1.txt" );
  std::cout << "Result : " << res << "\n";

  std::cin.get();

  return 0;
}