#pragma once

#include <functional>
#include <algorithm>
#include <iostream>


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


static void print_map( const std::map< t_coord, int, decltype(compare_coords) > & colors, t_coord startPoint )
{
  int maxX{ 0 }, maxY{ 0 };
  int minX{ 0 }, minY{ 0 };

  // Find max min coordinates;
  for ( const auto & _coord : colors )
  {
    maxX = std::max( maxX, _coord.first.x );
    maxY = std::max( maxY, _coord.first.y );

    minX = std::min( minX, _coord.first.x );
    minY = std::min( minY, _coord.first.y );
  }

  // Create Field
  std::vector< std::vector< int > > field( maxY - minY + 1, std::vector< int >( maxX - minX + 1, 10 ) );

  // Filling cells
  for ( auto & _coord : colors )
  {
    field[ _coord.first.y - minY ][ _coord.first.x - minX ] = _coord.second;
  }

  // Print
  for ( int y = field.size() - 1; y >= 0; --y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
    {
      if ( ( x + minX ) == startPoint.x && ( y + minY ) == startPoint.y )
      {
        std::cout << 'X';
        continue;
      }

      switch ( field[ y ][ x ] )
      {
      case 0:
        std::cout << '#';
        break;

      case 1:
        std::cout << '.';
        break;

      case 2:
        std::cout << 'O';
        break;

      case 10:
        std::cout << '?';
        break;

      default:
        throw "Unnown symbol";
      }
    }
    std::cout << "\n";
  }
}