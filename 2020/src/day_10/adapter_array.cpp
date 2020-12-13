//
// Created by alexpall on 10.12.2020.
//

#include "adapter_array.h"

#include <vector>
#include <algorithm>
#include <iostream>

#include "common/file_reader.h"


std::vector< int > prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Convert input data from string to long long
  std::vector< int > inputs;
  inputs.reserve( sInputs.size() );

  for ( const auto & _line : sInputs )
    inputs.push_back( std::stoi( _line ) );

  return inputs;
}


int AdapterArray::task_1( const std::string & filename )
{
  std::vector< int > jolts = prepare_input( filename );
  jolts.push_back( 0 );

  std::sort( jolts.begin(), jolts.end() );
  jolts.push_back( jolts.back() + 3 );

  int jolts1 { 0 }, jolts3 { 0 };

  for ( std::size_t idx = 1; idx < jolts.size(); ++idx )
  {
    if (jolts[idx - 1] + 1 == jolts[idx])
      ++jolts1;
    else if (jolts[idx - 1] + 3 == jolts[idx])
      ++jolts3;
  }

  std::cout << "1: " << jolts1 << " 3: " << jolts3 << std::endl;

  return jolts1 * jolts3;
}

long long AdapterArray::task_2(const std::string &filename)
{
  std::vector< int > jolts = prepare_input( filename );
  jolts.push_back( 0 );

  std::sort( jolts.begin(), jolts.end() );
  jolts.push_back( jolts.back() + 3 );

  std::vector< long long > path ( jolts.size() );
  path[ 0 ] = 1;
  path[ 1 ] = 1;

  for ( std::size_t idx = 2; idx < jolts.size(); ++idx )
  {
    path[ idx ] = path[ idx - 1 ];

    if ( jolts[ idx ] <= jolts[ idx - 2 ] + 3 )
      path[ idx ] += path[ idx - 2];

    if ( idx > 2 && jolts[ idx ] <= jolts[ idx - 3 ] + 3 )
      path[ idx ] += path[ idx - 3 ];
  }

  return path.back();
}
