
#include <iostream>

#include "springdroid.h"


int main()
{
  std::cout << "Day 21: Springdroid Adventure\n\n";

  auto res = Springdroid().run_part_2( INPUT_FILES "/day_21/part_1.txt" );

  std::cin.get();
  return 0;
}