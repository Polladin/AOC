#pragma once

#include <functional>

struct t_coord
{
  t_coord( int _x, int _y )
    : x{ _x }, y{ _y }
  {}

  int x, y;
};


static std::function< bool( const std::pair< int, int > &, const std::pair< int, int > & ) > 
  compare_pairs =
    []( const std::pair< int, int > & lhs, const std::pair< int, int > & rhs )
    { return lhs.first == rhs.first ? lhs.second < rhs.second
                                    : lhs.first < rhs.first;    
    };


static std::function< bool( const t_coord &, const t_coord & ) >
  compare_coords =
  []( const t_coord & lhs, const t_coord & rhs )
  { return lhs.x == rhs.x ? lhs.y < rhs.y
                          : lhs.x < rhs.x;
  };


static long long gcd( long long a, long long b )
{
  while ( a % b != 0 )
  {
    a = a % b;
    std::swap( a, b );
  }

  return b;
}


static long long lcm( long long a, long long b )
{
  return a * b / gcd( a, b );
}