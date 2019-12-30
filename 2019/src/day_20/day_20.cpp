
#include <iostream>

#include "donut_maze.h"


int main()
{
  std::cout << "Day 20: Donut Maze\n\n";

  //auto res = DonutMaze().run_part_1( INPUT_FILES "/day_20/example_3.txt" );
  auto res = DonutMaze().run_part_1( INPUT_FILES "/day_20/part_1.txt" );
  std::cout << "Result : " << res << "\n";

  std::cin.get();

  return 0;
}