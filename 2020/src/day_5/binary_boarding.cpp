//
// Created by alexpall on 05.12.2020.
//

#include "binary_boarding.h"

#include <iostream>
#include <algorithm>

#include "common/file_reader.h"


int binary_search( int lowBorder, int highBorder, std::string::const_iterator it, std::string::const_iterator ite )
{
  for(; it != ite; ++it)
  {
    int offset = ( highBorder - lowBorder + 1 ) / 2;

    if ( offset == 1 )
      return ( *it == 'F' || *it == 'L' ) ? lowBorder : highBorder;

    if ( *it == 'F' || *it == 'L' )
      highBorder -= offset;
    else
      lowBorder += offset;
  }

  throw std::invalid_argument( "Failed with binary search" );
}


int get_seat_number( const std::string & binarySeat )
{
  int row = binary_search( 0, 127, binarySeat.begin(), binarySeat.begin() + 7 );
  int col = binary_search( 0, 7, binarySeat.begin() + 7, binarySeat.end() );

//  std::cout << "String: " << binarySeat << " row: " << row << " col: " << col << " Res : " << row * 8 + col << std::endl;

  return row * 8 + col;
}


int BinaryBoarding::task_1( const std::string & filename )
{
  // Read the file
  std::vector< std::string > strSeats = FileReader::read_file( filename );
  std::vector< int > seats;
  seats.reserve( strSeats.size() );

  for ( const auto & _strSeat : strSeats )
    seats.push_back( get_seat_number( _strSeat ) );

  return *std::max_element( seats.begin(), seats.end() );
}


int BinaryBoarding::task_2(const std::string &filename)
{
  // Read the file
  std::vector< std::string > strSeats = FileReader::read_file( filename );
  std::vector< int > seats;
  seats.reserve( strSeats.size() );

  for ( const auto & _strSeat : strSeats )
    seats.push_back( get_seat_number( _strSeat ) );

  std::sort( seats.begin(), seats.end() );

  for ( std::size_t idx = 0; idx + 1 < seats.size(); ++idx )
    if ( seats[ idx ] != seats[ idx + 1 ] - 1 )
      return seats[ idx ] + 1;

  throw std::invalid_argument( "The seat not found" );
}
