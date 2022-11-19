//
// Created by alexey on 01.12.2021.
//

#include <iostream>
#include <vector>

#include "SonarSweep.h"


class A
{
public:
  virtual int func(int a)
  {
    return a;
  }
};

class B: public A
{
public:
  int func([[maybe_unused]] int a) override
  {
    return 0;
  }
};

//class C: public B
//{
//public:
//  int func(int b)
//};
class Solution
{

  std::string get_polyndrom_if_max_even( const std::string & str, std::size_t pos, int maxPolySize )
  {
    if ( pos + 1 >= str.length() )
      return "";

    int leftBorder  = pos;
    int rightBorder = pos + 1;

    for ( ; leftBorder >= 0 && rightBorder < str.length(); --leftBorder, ++rightBorder )
    {
      if ( str[ leftBorder ] != str[ rightBorder ] )
        break;
    }

    const int newPolySize = rightBorder - leftBorder - 1;


    return ( newPolySize > maxPolySize ) ? str.substr( leftBorder + 1, newPolySize ) : "";
  }

  std::string get_polyndrom_if_max_odd( const std::string & str, std::size_t pos, int maxPolySize )
  {
    if ( pos == 0 || pos + 1 >= str.length() )
      return "";

    int leftBorder  = pos - 1;
    int rightBorder = pos + 1;

    for ( ; leftBorder >= 0 && rightBorder < str.length(); --leftBorder, ++rightBorder )
    {
      if ( str[ leftBorder ] != str[ rightBorder ] )
        break;
    }

    const int newPolySize = rightBorder - leftBorder - 1;


    return ( newPolySize > maxPolySize ) ? str.substr( leftBorder + 1, newPolySize ) : "";
  }


public:

  std::string longestPalindrome( std::string s )
  {
    std::string poly;

    for ( std::size_t idx = 0; idx < s.length(); ++idx )
    {
      poly = get_polyndrom_if_max_even( s, idx, poly.size() );
      std::cout << "max: " << poly << "\n";
      poly = get_polyndrom_if_max_odd( s, idx, poly.size() );
      std::cout << "max: " << poly << "\n";
    }

    return poly;
  }


};

#include <iostream>
#include <string>


void put_bracket( int count, std::string sequence, int left, int right )
{
  if ( left == count && right == count )
  {
    std::cout << sequence << "\n";
    return;
  }

  if ( left < count )
    put_bracket( count, sequence + "(", left + 1, right );

  if ( right < left )
    put_bracket( count, sequence + ")", left, right + 1 );

}

#include <array>
#include <numeric>
#include <algorithm>
#include <vector>
#include <queue>

using t_map = std::vector< std::vector< long long > >;

bool bfs( const int startTown, const int endTown, const t_map & map, const int maxLength )
{
  std::queue< std::pair< int, int > > q; // first - town number; second - num road to the town;
  std::vector< bool > visitedTowns ( map.size(), false );

  // Initialize start town
  q.push( std::make_pair( startTown, 0 ) );
  visitedTowns[ startTown ] = true;

  while( !q.empty() )
  {
    // pop the next town
    std::pair< int, int > curTown = q.front();
    q.pop();

    for ( int idx = 0; idx < map.size(); ++idx )
    {
      if ( visitedTowns[ idx ] )
        continue;

      if ( map[ curTown.first ][ idx ] > maxLength )
        continue;

      if ( idx == endTown )
      {
        std::cout << curTown.second + 1;
        return true;
      }

      q.push( std::make_pair( idx, curTown.second + 1 ) );
      visitedTowns[ idx ] = true;
    }
  }

  return false;
}

std::vector< std::pair< long long, long long > > read_towns( const int numTowns )
{
  std::vector< std::pair< long long, long long > > towns;
  towns.reserve( numTowns );

  for ( int idx = 0; idx < numTowns; ++idx )
  {
    int x, y;
    std::cin >> x >> y;

    towns.emplace_back( x, y );
  }

  return towns;
}

int main()
{
  std::size_t numTowns;
  int maxLength;
  int startTown ,endTown;

  std::cin >> numTowns;

  std::vector< std::pair< long long, long long > > towns = read_towns( numTowns );

  std::cin >> maxLength >> startTown >> endTown;

  // Initialize map;
  t_map map ( numTowns, std::vector< long long >( numTowns, -1 ) );

  for( std::size_t idx_1 = 0; idx_1 < towns.size(); ++idx_1 )
  {
    for ( std::size_t idx_2 = 0; idx_2 < towns.size(); ++idx_2 )
    {
      map[ idx_1 ][ idx_2 ] =   std::abs( towns[ idx_1 ].first  - towns[ idx_2 ].first  )
                              + std::abs( towns[ idx_1 ].second - towns[ idx_2 ].second );
    }
  }

  const bool pathFound = bfs( startTown - 1, endTown - 1, map, maxLength );

  if ( !pathFound )
    std::cout << "-1";
}

//  int main()
//{
//  std::cout << "Day 1: Sonar sweep\n";
//
//  SonarSweep sonar;
//
//  std::cout << "Res for TEST 1: " << sonar.task_1( INPUT_FILES "/day_1/test_1.txt" ) << std::endl;
//  std::cout << "Res for TASK 1: " << sonar.task_1( INPUT_FILES "/day_1/task_1.txt" ) << std::endl;
//
//  std::cout << "TASK 2:\n";
//
//  std::cout << "Res for TEST 2: " << sonar.task_2( INPUT_FILES "/day_1/test_1.txt" ) << std::endl;
//  std::cout << "Res for TASK 2: " << sonar.task_2( INPUT_FILES "/day_1/task_1.txt" ) << std::endl;
//
//  B b = B();
//  A a = b;
//  std::cout << static_cast< A* >( &b )->func(5) << std::endl;
//  std::cout << a.func(5) << std::endl;
//
//  std::cout << "L.Code: \n" << Solution().longestPalindrome("babad") << "\n"; // babad
//}
