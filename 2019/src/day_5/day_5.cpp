
#include <iostream>

#include "day_2/computer.h"

int main()
{
  std::cout << "Day 5: Sunny with a Chance of Asteroids\n\n";

  Computer cmp;


  std::queue< long long > in;
  std::vector< long long > out;
  in.push( 5 );

  // auto res = cmp.run_day_5_part_1( INPUT_FILES "/day_5/example_7.txt", in, out);
  auto res = cmp.run_day_5_part_1( INPUT_FILES "/day_5/part_1.txt", in, out);
  std::cout << "Res: " << res << "\n";

  std::cout << "Output:\n   >>>  ";
  for ( auto code : out )
    std::cout << code << ", ";

  std::cout << "\n";

  std::cout << "\nThe End\n";
  std::cin.get();

  return 0;
}
