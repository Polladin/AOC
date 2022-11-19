
#include "fft.h"

#include "common/file_reader.h"

#include <iostream>
#include <algorithm>


static const std::vector< int > PATTERN = { 0, 1, 0, -1 };


std::vector<int> FFT::run_part_1( const std::string & fileName )
{
  std::vector< int > digits = prepare_input( fileName );

  // Create linear patterns
  std::vector< std::vector< int > > mult;
  
  for ( int idx = 0; idx < digits.size(); ++idx )
    mult.emplace_back( make_pattern( idx, digits.size() ) );

  // Calc
  for ( int i = 0; i < 100; ++i )
  {
    digits = calc_phase_1( digits, mult );
  }

  return digits;
}


std::vector<long long> FFT::run_part_2( const std::string & fileName )
{
  std::vector< int > digits = prepare_input( fileName );
  
  // Get offset
  long long offset = 0;
  for ( int i = 0; i < 7; ++i )
    offset = offset * 10 + digits[ i ];

  // Reverse number
  std::reverse( digits.begin(), digits.end() );

  //
  long long lastDigitPos = digits.size() * 10000 - offset;

  //
  std::vector< long long > res( lastDigitPos );

  // Initialize
  for ( int i = 0; i < res.size(); ++i )
    res[ i ] = digits[ i % digits.size() ];

  for ( int epoch = 0; epoch < 100; ++epoch )
  {
    for ( int i = 1; i < res.size(); ++i )
      res[ i ] = res[ i ] + res[ i - 1 ];

    for ( int i = 1; i < res.size(); ++i )
      res[ i ] = std::abs( res[ i ] ) % 10;

  }

  return res;
}


std::vector<int> FFT::prepare_input( const std::string & fileName )
{
  std::vector< int > res;

  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( fileName );

  for ( auto _char : sInputs[ 0 ] )
    res.push_back( _char - '0' );

  return res;
}


std::vector< int > FFT::make_pattern( int idx, int countDigits )
{
  std::vector< int > res;
  std::vector< int > customPattern;

  for ( auto _el : PATTERN )
    for ( int i = 0; i < idx + 1; ++i )
      customPattern.push_back( _el );

  int currenpPatternPos = 1;

  while ( res.size() < countDigits )
  {
    res.push_back( customPattern[ currenpPatternPos ] );
    currenpPatternPos = ( currenpPatternPos + 1 ) % customPattern.size();
  }

  return res;
}

std::vector<int> FFT::calc_phase_1( const std::vector< int > & digits, const std::vector< std::vector< int > > & mult )
{
  std::vector< int > res( digits.size(), 0 );

  for ( int idx = 0; idx < digits.size(); ++idx )
  {
    for ( int idx2 = 0; idx2 < digits.size(); ++idx2 )
      res[ idx ] += digits[ idx2 ] * mult[ idx ][ idx2 ];

    res[ idx ] = std::abs( res[ idx ] ) % 10;
  }

  return res;
}
