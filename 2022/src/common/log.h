//
// Created by alexey on 04.12.2021.
//

#ifndef ADVENTOFCODE2021_LOG_H
#define ADVENTOFCODE2021_LOG_H

#endif //ADVENTOFCODE2021_LOG_H

#include <vector>
#include <iostream>

namespace mylog {

template < typename T >
[[maybe_unused]] void print_vector( const std::vector< T > & vec )
{
  for ( std::size_t _idx = 0; _idx < vec.size(); ++_idx )
  {
    std::cout << vec[ _idx ];
    if ( _idx + 1 != vec.size() )
      std::cout << ", ";
  }
  std::cout << "\n";
}


} // namespace mylog
