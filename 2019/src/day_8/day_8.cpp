
#include <iostream>

#include "image_layers.h"


int main()
{
  std::cout << "Day 8: Space Image Format\n\n";

  ImageLayers il;

  il.run_part_2( INPUT_FILES "/day_8/part_1.txt" );
  //std::cout << "Res : " << res << "\n";

  std::cout << "\nThe End\n";
  std::cin.get();
  return 0;
}