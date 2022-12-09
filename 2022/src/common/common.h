#pragma once

#include <functional>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>




struct t_coord
{
  t_coord()
    : x{ 0 }, y{ 0 }
  {}

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

struct PointCmp
{
    bool operator() ( const t_coord & lhs, const t_coord & rhs ) const
    {
        return lhs.x == rhs.x ? lhs.y < rhs.y
                              : lhs.x < rhs.x;
    }
};

static std::function< bool( const t_coord &, const t_coord & ) >
  compare_coords =
  []( const t_coord & lhs, const t_coord & rhs )
  { return lhs.x == rhs.x ? lhs.y < rhs.y
                          : lhs.x < rhs.x;
  };

static std::function< bool( const std::pair< long long, long long > &, const std::pair< long long, long long > & ) >
compare_longs =
[]( const std::pair< long long, long long > & lhs, const std::pair< long long, long long > & rhs )
{ return lhs.first == rhs.first ? lhs.second < rhs.second
  : lhs.first < rhs.first;
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
  for ( std::size_t y = field.size() - 1; y >= 0; --y )
  {
    for ( std::size_t x = 0; x < field[ y ].size(); ++x )
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

namespace common {

// trim from start
static inline std::string & ltrim( std::string & s )
{
  s.erase( s.begin(), std::find_if( s.begin(), s.end(), std::not1( std::ptr_fun< int, int >( std::isspace ) ) ) );
  return s;
}

// trim from end
static inline std::string & rtrim( std::string & s )
{
  s.erase( std::find_if( s.rbegin(), s.rend(), std::not1( std::ptr_fun< int, int >( std::isspace ) ) ).base(), s.end() );
  return s;
}

// trim from both ends
static inline std::string & trim( std::string & s )
{
  return ltrim(rtrim(s) );
}

// Split line
static std::vector< std::string > split_line( const std::string & line, char delimiter )
{
  std::vector< std::string > res;

  std::size_t pos = line.find( delimiter, 0 );
  std::size_t startPos = 0;

  while( pos != std::string::npos )
  {
    if( startPos != pos )
      res.push_back( line.substr( startPos, pos - startPos ) );

    startPos = pos + 1;
    pos = line.find( delimiter, pos + 1 );
  }

  res.push_back( line.substr( startPos ) );
  return res;
}

} //namespace common
