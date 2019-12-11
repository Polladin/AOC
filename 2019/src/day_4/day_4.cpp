
#include <iostream>

#include "get_password.h"


int main()
{
  std::cout << "Day 4: Secure Container\n\n";

  GetPassword gp;

  auto res = gp.run_part_1( 109165, 576723 );

  std::cout << "Res: " << res << std::endl;

  std::cout << "\nThe End\n";
  std::cin.get();
}