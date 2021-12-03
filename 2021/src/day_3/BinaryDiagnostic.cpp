//
// Created by alexey on 03.12.2021.
//

#include "BinaryDiagnostic.h"

#include <vector>
#include <iostream>
#include <functional>

#include "common/file_reader.h"

static int convert_bin_to_int( const std::string & binNumber )
{
  int res{ 0 }, mult { 1 };

  for ( auto it = binNumber.rbegin(); it != binNumber.rend(); ++it )
  {
    res += mult * ( *it - '0' );
    mult *= 2;
  }

  return res;
}


int BinaryDiagnostic::task_1( const std::string &filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  std::string gamma, epsilon;

  for ( std::size_t _pos = 0; _pos < sInputs[ 0 ].length(); ++_pos )
  {
    int onesMinusZeros { 0 };

    // Calculate the difference between ones and zeros
    for ( const auto & line : sInputs  )
      onesMinusZeros += ( line[ _pos ] == '1' ) ? 1 : -1;

    gamma.push_back( onesMinusZeros > 0 ? '1' : '0' );
    epsilon.push_back( onesMinusZeros > 0 ? '0' : '1' );
  }

  std::cout << "Gamma: " << gamma << " epsilon: " << epsilon << std::endl;
  std::cout << "Gamma: " << convert_bin_to_int( gamma ) << " epsilon: " << convert_bin_to_int( epsilon ) << std::endl;

  return convert_bin_to_int( gamma ) * convert_bin_to_int( epsilon );
}


static int get_the_difference_zeros_and_ones( const std::vector< std::string > & diagnosticOutput, std::size_t pos )
{
  int onesMinusZeros { 0 };

  // Calculate the difference between ones and zeros
  for ( const auto & line : diagnosticOutput  )
    onesMinusZeros += ( line[ pos ] == '1' ) ? 1 : -1;

  return onesMinusZeros;
}


static int get_rating(  const std::vector< std::string > & diagnosticOutput
                      , const std::function< char( int ) > & choose_function    )
{

  // Create a copy of the input data
  std::vector< std::string > filteredArray { diagnosticOutput };

  for( std::size_t _pos = 0; _pos < diagnosticOutput.size(); ++_pos )
  {
    // Get the value to make a filter
    char filterValue = choose_function( get_the_difference_zeros_and_ones( filteredArray, _pos ) );

    // Filter values in the array
    auto it = std::remove_if(   filteredArray.begin(), filteredArray.end()
                             , [ _pos, filterValue ]( const std::string & _value ){ return _value[ _pos ] != filterValue; } );
    filteredArray.erase( it, filteredArray.end() );

    // Stop if we find the result
    if ( filteredArray.size() == 1 )
      break;
  }

  return convert_bin_to_int( filteredArray.front() );
}


int BinaryDiagnostic::task_2( const std::string &filename )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( filename );

  // Oxygen generator rating
  int oxygen = get_rating( sInputs, []( int difference ){ return difference >= 0 ? '1' : '0'; } );

  // C02
  int co2 = get_rating( sInputs, []( int difference ){ return difference >= 0 ? '0' : '1'; } );

  std::cout << "Oxygen: " << oxygen << " co2: " << co2 << std::endl;

  return oxygen * co2;
}