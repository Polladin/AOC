
#include <iostream>

#include "cards.h"
#include "slamshuffle.h"


int main()
{
    std::cout << "Day 22: Slam Shuffle\n\n";

  //auto res = Cards().run_part_1( INPUT_FILES "/day_22/part_1.txt", 10007 );
  //for ( int i = 0; i < 10; ++i )
//  {
//    auto res = Cards().run_part_2( INPUT_FILES "/day_22/part_1.txt", 2020, 119315717514047 );
//    std::cout << "Result : " << res << "\n";
//  }

//    for ( int i = 0; i < 10; ++i )
//        std::cout << "Result: " << SlamShuffle().task_1( INPUT_FILES "/day_22/example_4.txt", i, 10 ) << "\n";



//    Cards().run_part_1( INPUT_FILES "/day_22/part_1.txt", 10007 );

    std::cout << "Result: " << SlamShuffle().task_1( INPUT_FILES "/day_22/part_1.txt", 2019, 10007 ) << "\n";

    std::cout << "Result task 2: " <<SlamShuffle().task_2( INPUT_FILES "/day_22/part_1.txt", 6978, 10007 ) << "\n";

    std::cout << "Result task 2: " <<SlamShuffle().task_2( INPUT_FILES "/day_22/part_1.txt", 2020, 119315717514047 ) << "\n";

//    SlamShuffle().test();

//    SlamShuffle().task_2( INPUT_FILES "/day_22/part_1.txt", 2020, 119315717514047 );

//  std::cin.get();
    return 0;
}
