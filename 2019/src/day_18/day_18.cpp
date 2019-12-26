
#include <iostream>

#include "vault.h"


int main()
{
  std::cout << "Day 18: Many-Worlds Interpretation\n\n";

  //auto res = Vault().run_part_2( INPUT_FILES "/day_18/example_9.txt" );
  auto res = Vault().run_part_2( INPUT_FILES "/day_18/part_1.txt" );
  std::cout << "Result : " << res << "\n";

  std::cin.get();

  return 0;
}