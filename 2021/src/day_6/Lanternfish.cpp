//
// Created by alexey on 07.12.2021.
//

#include "Lanternfish.h"

#include <iostream>
#include <algorithm>
#include <numeric>


std::vector< long long > Lanternfish::grow_fish( const std::vector< long long > & fish )
{
  std::vector< long long > newFish ( 9, 0 );

  for ( std::size_t _idx = 1; _idx < 9; ++_idx )
    newFish[ _idx - 1 ] = fish[ _idx ];

  newFish[ 6 ] += fish[ 0 ];
  newFish[ 8 ] = fish[ 0 ];

  return newFish;
}

std::vector< long long > merge_fish( const std::vector< int > & fish )
{
  std::vector< long long > fishWithSameDay( 9, 0 );

  for ( auto _fish : fish )
    ++fishWithSameDay[ _fish ];

  return fishWithSameDay;
}

long long Lanternfish::task_1( const std::vector< int > & fish, int days )
{
  std::vector< long long > fishWithSameDay = merge_fish( fish );

  for ( int i = 0; i < days; ++i )
  {
//    std::cout << "Fish: ";
//    for ( auto _fish : fishWithSameDay )
//      std::cout << _fish << " ";
//    std::cout << "\n";
//    std::cout << "Step: " << i << " size: " << fish.size() << "\n";
    fishWithSameDay = grow_fish( fishWithSameDay );
  }

  return std::accumulate( fishWithSameDay.begin(), fishWithSameDay.end(), 0ll );
}
