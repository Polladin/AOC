//
// Created by alexpall on 13.12.2020.
//

#include "seating_system.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "common/file_reader.h"


bool is_seat_occupied( const std::vector< std::string > & seats, int vert, int horz, const std::pair< int, int > & offset )
{
  int newVert = vert + offset.first;
  int newHorz = horz + offset.second;

  while( true )
  {
    if (   newVert < 0 || newVert >= seats.size()
        || newHorz < 0 || newHorz >= seats[0].size()  )
      return false;

    if ( seats[ newVert ][ newHorz ] == '.' )
    {
      newVert += offset.first;
      newHorz += offset.second;
      continue;
    }

    return seats[ newVert ][ newHorz ] == '#';
  }
}

int get_occupied( const std::vector< std::string > & seats, std::size_t vert, std::size_t horz )
{
  static std::vector< std::pair< int, int > > offsets = {   { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 }
                                                          , { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

  int res { 0 };

  for ( const auto & _offset : offsets )
    if ( is_seat_occupied( seats, vert, horz, _offset) )
      ++res;

  return res;
}

std::vector< std::string > make_step( const std::vector< std::string > & seats, bool & isChanged )
{
  std::vector< std::string > newSeats { seats };
  isChanged = false;

  for( std::size_t vert = 0; vert < seats.size(); ++vert )
  {
    for ( std::size_t hor = 0; hor < seats[ vert ].size(); ++hor )
    {
      // Empty place
      if ( seats[ vert ][ hor ] == '.' )
        continue;

      int occupiedSeats = get_occupied( seats, vert, hor );

      // Is empty place
      if ( seats[ vert ][ hor ] == 'L' &&  occupiedSeats == 0 )
      {
        newSeats[ vert ][ hor ] = '#';
        isChanged = true;
        continue;
      }

      // Is occupied place
      if ( seats[ vert ][ hor ] == '#' && occupiedSeats >= 5 )
      {
        newSeats[ vert ][ hor ] = 'L';
        isChanged = true;
        continue;
      }
    }
  }

  return newSeats;
}


int SeatingSystem::task_1(const std::string &filename)
{
  // Read the file
  std::vector< std::string > seats = FileReader::read_file( filename );

  bool isChanged = true;

  while( isChanged )
  {
//    std::cout << std::endl;
//    for ( const auto & _line : seats )
//      std::cout << _line << std::endl;
    seats = make_step( seats, isChanged );
//    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
  }

//  for ( const auto & _line : seats )
//    std::cout << _line << std::endl;

  int res { 0 };

  for ( const auto & _line : seats )
    for ( const auto _ch : _line )
      if ( _ch == '#' )
        ++res;

  return res;
}
