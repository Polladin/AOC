//
// Created by alexey on 01.12.2021.
//

#include "SonarSweep.h"

#include <vector>
#include <iostream>

#include "common/file_reader.h"


static std::vector< int > prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Create an output array
  std::vector< int > input;

  // Convert input strings to numbers
  for ( const auto & str : sInputs )
  {
    input.push_back( std::stoi( str ) );
//    std::cout << "Read input from: " << str << " to: " << std::stoi(str) << std::endl;
  }

  return input;
}


int SonarSweep::task_1( const std::string & filename )
{
  // Get an input array
  std::vector< int > input = prepare_input( filename );

  // Initialize counter
  int increases { 0 };

  // Calculations
  for ( std::size_t idx = 1; idx < input.size(); ++idx )
  {
    if ( input[ idx - 1 ] < input[ idx ] )
      ++increases;
//    std::cout << "Idx: " << idx << " inc: " << increases << std::endl;
  }

  return increases;
}


int SonarSweep::task_2( const std::string & filename )
{
  // Get an input array
  std::vector< int > input = prepare_input( filename );

  // Initialize counter
  int increases { 0 };

  // Calculations
  for ( std::size_t idx = 3; idx < input.size(); ++idx )
  {
    if ( input[ idx - 3 ] + input[ idx - 2 ] + input[ idx - 1 ] < input[ idx - 2 ] + input[ idx - 1 ] + input[ idx ] )
      ++increases;
//    std::cout << "Idx: " << idx << " inc: " << increases << std::endl;
  }

  return increases;
}