
#include <iostream>

#include "cards.h"


int main()
{
  std::cout << "Day 22: Slam Shuffle\n\n";

  //auto res = Cards().run_part_1( INPUT_FILES "/day_22/part_1.txt", 10007 );
  //for ( int i = 0; i < 10; ++i )
  {
    auto res = Cards().run_part_2( INPUT_FILES "/day_22/part_1.txt", 2020, 119315717514047 );
    std::cout << "Result : " << res << "\n";
  }


  std::cin.get();
  return 0;
}