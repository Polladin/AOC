
#include <iostream>

#include "wires.h"
#include "wires_distance.h"


int main()
{
  std::cout << "Day 3: Crossed Wires\n\n";

  //Wires wr;
  WiresDistance wr;
  
  //int res = wr.run_part_1( INPUT_FILES "/day_3/example_1.txt" );
  int res = wr.run_part_1( INPUT_FILES "/day_3/part_1.txt" );
  std::cout << "Res: " << res << std::endl;

  std::cout << "\nThe End\n";
  std::cin.get();
}