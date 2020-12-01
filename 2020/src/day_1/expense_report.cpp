
#include "expense_report.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <array>

#include "common/file_reader.h"


std::size_t get_middle( const std::vector< int > & input )
{
  for ( std::size_t idx = 1; idx < input.size(); ++idx )
  {
    if ( input[ idx - 1 ] + input[ idx ] >= 2020 )
      return idx;
  }

  throw std::invalid_argument("Middle not found");
}


std::size_t get_middle_of_3( const std::vector< int > & input )
{
  for ( std::size_t idx = 2; idx < input.size(); ++idx )
  {
    if ( input[ idx - 1 ] + input[ idx - 2 ] + input[ idx ] >= 2020 )
      return idx;
  }

  throw std::invalid_argument("Middle not found");
}


std::array< std::size_t ,3 > find_sum_2020_of_3( const std::vector< int > & input, std::size_t middleIdx )
{
  for ( std::size_t topBorder = middleIdx; topBorder < input.size(); ++topBorder )
  {
    size_t botBorder = middleIdx - 2;

    while( botBorder >= 0 )
    {
      for ( std::size_t midBorder = topBorder - 1; midBorder > botBorder; --midBorder )
      {
        int sum = input[ botBorder ] + input[ midBorder ] + input[ topBorder ];

        std::cout << midBorder << " " << sum << std::endl;

        if ( sum == 2020 )
          return { botBorder, midBorder, topBorder };

        if ( sum < 2020 )
          break;

        if ( botBorder == 0 )
          break;
      }

      if ( botBorder == 0 )
        break;

      --botBorder;
    }
  }

  throw std::invalid_argument("Sum 2020 not found");
}


std::pair< std::size_t, std::size_t > find_sum_2020( const std::vector< int > & input, std::size_t middleIdx )
{
  std::size_t rBorder = middleIdx;

  while( rBorder < input.size() )
  {
    std::size_t lBorder = middleIdx - 1;
    while( lBorder >= 0 )
    {
      int sum = input[ lBorder ] + input[ rBorder ];

      if ( sum == 2020 )
        return { lBorder, rBorder };

      if ( sum < 2020 )
        break;

      if ( lBorder == 0 )
        break;

      --lBorder;
    }

    ++rBorder;
  }

  throw std::invalid_argument("Sum 2020 not found");
}


int ExpenseReport::task_1( const std::string & filename )
{
  // Read file
  std::vector< int > inputs = prepare_input( filename );

  // Sort array
  std::sort( inputs.begin(), inputs.end() );

  // Find a middle
  std::size_t middleIdx = get_middle( inputs );

//  std::cout << "Middle : " << middleIdx << std::endl;

  // Find indexes with sum = 2020
  std::pair< std::size_t, std::size_t > sum2020Idx = find_sum_2020( inputs, middleIdx );

//  std::cout << "Found idx : " << sum2020Idx.first << " - " << sum2020Idx.second << std::endl;

  return inputs[ sum2020Idx.first ] * inputs[ sum2020Idx.second ];
}


int ExpenseReport::task_2( const std::string & filename )
{
  // Read file
  std::vector< int > inputs = prepare_input( filename );

  // Sort array
  std::sort( inputs.begin(), inputs.end() );

  // Find a middle
  std::size_t middleIdx = get_middle_of_3( inputs );

  // Find indexes with sum = 2020
  std::array< std::size_t ,3 > sum2020Idx = find_sum_2020_of_3( inputs, middleIdx );

  return inputs[ sum2020Idx[0] ] * inputs[ sum2020Idx[1] ] * inputs[ sum2020Idx[2] ];
}


std::vector< int > ExpenseReport::prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Convert input data from string to int
  std::vector< int > inputs;
  inputs.reserve( sInputs.size() );

  for ( const auto & _line : sInputs )
    inputs.push_back( std::stoi( _line ) );

  return inputs;
}
