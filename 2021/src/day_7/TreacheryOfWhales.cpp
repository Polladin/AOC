//
// Created by alexey on 07.12.2021.
//

#include "TreacheryOfWhales.h"

#include <algorithm>
#include <iostream>
#include <limits>


int TreacheryOfWhales::task_1( const std::vector< int > & crabs )
{
  int maxCrab = *( std::max_element( crabs.begin(), crabs.end() ) );
  int minCrab = *( std::min_element( crabs.begin(), crabs.end() ) );

//  std::cout << "Min: " << minCrab << " Max: " << maxCrab << "\n";

  std::vector< int > fuel ( maxCrab + 1, std::numeric_limits< int >::max() );

  for ( int _idx = minCrab; _idx <= maxCrab; ++_idx )
  {
    fuel[ _idx ] = 0;
    for ( auto _crab : crabs )
    {
      fuel[ _idx ] += std::abs( _crab - _idx );
    }
//    std::cout << "Idx: " << _idx << " fuel: " << fuel[ _idx ] << "\n";
  }

  int min = std::numeric_limits< int >::max();
  std::size_t pos = 0;

  for ( std::size_t _idx = minCrab; _idx <= maxCrab; ++_idx )
  {
    if ( min > fuel[ _idx ] )
    {
      pos = _idx;
      min = fuel[ _idx ];
    }
  }

  return fuel[ pos ];
}

int get_arifmetic_seq( int num )
{
  return ( 1 + num ) * num / 2;
}

int TreacheryOfWhales::task_2( const std::vector<int> &crabs )
{
  int maxCrab = *( std::max_element( crabs.begin(), crabs.end() ) );
  int minCrab = *( std::min_element( crabs.begin(), crabs.end() ) );

//  std::cout << "Min: " << minCrab << " Max: " << maxCrab << "\n";

  std::vector< int > fuel ( maxCrab + 1, std::numeric_limits< int >::max() );

  for ( int _idx = minCrab; _idx <= maxCrab; ++_idx )
  {
    fuel[ _idx ] = 0;
    for ( auto _crab : crabs )
    {
      fuel[ _idx ] += get_arifmetic_seq( std::abs( _crab - _idx ) ) ;
    }
//    std::cout << "Idx: " << _idx << " fuel: " << fuel[ _idx ] << "\n";
  }

  int min = std::numeric_limits< int >::max();
  std::size_t pos = 0;

  for ( std::size_t _idx = minCrab; _idx <= maxCrab; ++_idx )
  {
    if ( min > fuel[ _idx ] )
    {
      pos = _idx;
      min = fuel[ _idx ];
    }
  }

  return fuel[ pos ];
}
