//
// Created by alexpall on 09.12.2020.
//

#include "encoding_error.h"

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "common/file_reader.h"


std::vector< long long > prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Convert input data from string to long long
  std::vector< long long > inputs;
  inputs.reserve( sInputs.size() );

  for ( const auto & _line : sInputs )
    inputs.push_back( std::stoll( _line ) );

  return inputs;
}


bool can_be_constructed( const std::vector< long long > & input, std::size_t preamble, std::size_t currentIdx )
{
  for ( std::size_t idx1 = currentIdx - preamble; idx1 < currentIdx; ++idx1 )
  {
    for ( std::size_t idx2 = currentIdx - preamble; idx2 < currentIdx; ++idx2 )
    {
      if ( idx1 == idx2 )
        continue;

      if ( input[ currentIdx ] == input[ idx1 ] + input[ idx2 ] )
        return true;
    }
  }

  return false;
}


long long EncodingError::task_1( const std::string & filename, std::size_t preamble /* 25 */ )
{
  std::vector< long long > input = prepare_input( filename );

  for ( std::size_t idx = preamble; idx < input.size(); ++idx )
  {
    if ( !can_be_constructed( input, preamble, idx ) )
    {
      std::cout << "Idx: " << idx << " ";
      return input[idx];
    }
  }

  throw std::invalid_argument( "Invalid input data" );
}


long long EncodingError::task_2( const std::string &filename )
{
  std::vector< long long > input = prepare_input( filename );

  // idx = 511;
  // 18272118

  std::size_t lIdx { 0 }, rIdx { 0 };
  long long sum = 0;
  const long long RESULT = 18272118; // 127;

  while ( sum != RESULT )
  {
    if ( sum > RESULT )
    {
      sum -= input[ lIdx ];
      ++lIdx;
    }
    else if( sum < RESULT )
    {
      sum += input[ rIdx ];
      ++rIdx;
    }
  }

  std::cout << "Idx : " << lIdx << " - " << rIdx << std::endl;

  std::sort( input.begin() + lIdx, input.begin() + rIdx );

  return input[ lIdx ] + input[ rIdx - 1 ];
}
