//
// Created by alexey on 21.12.2021.
//

#include "DumboOctopus.h"

#include <vector>
#include <array>

#include <common/file_reader.h>

using t_2d_array = std::array< std::array< int, 10 >, 10 >;


static t_2d_array prepare_input( const std::string & filename )
{
  t_2d_array res;

  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  for ( std::size_t _row = 0; _row < sInput.size(); ++_row )
    for ( std::size_t _column = 0; _column < sInput[ _row ].length(); ++_column )
      res[ _row ][ _column ] = sInput[ _row ][ _column ] - '0';

  return res;
}


bool is_need_to_flash( const t_2d_array & state )
{
  for ( std::size_t _row = 0; _row < 10; ++_row )
    for ( std::size_t _column = 0; _column < 10; ++_column )
      if ( state[ _row ][ _column ] > 9 )
        return true;

  return false;
}

void flash_cell( t_2d_array & state, int row, int column )
{
  static std::vector< std::pair< int, int > > offsets = {  { 0 , 1 }, { 0 , -1 }, { 1, 0 }, { -1,  0 }
                                                         , { -1, 1 }, { -1, -1 }, { 1, 1 }, {  1, -1 } };

  // Flash the cell
  state[ row ][ column ] = 0;

  // Increase the neighbours
  for ( const auto & _offset : offsets )
  {
    const int newRow = row + _offset.first;
    const int newColumn = column + _offset.second;

    if (   newRow < 0 || newRow >= 10
        || newColumn < 0 || newColumn >= 10 )
      continue;

    // Increase only not flashed cells
    if ( state[ newRow ][ newColumn ] == 0 )
      continue;

    ++state[ newRow ][ newColumn ];
  }
}

int flash_array( t_2d_array & state )
{
  int flashes { 0 };

  for ( std::size_t _row = 0; _row < 10; ++_row )
  {
    for( std::size_t _column = 0; _column < 10; ++_column )
    {
      if( state[ _row ][ _column ] > 9 )
      {
        flash_cell( state, _row, _column );
        ++flashes;
      }
    }
  }

  return flashes;
}

t_2d_array simulate_step( const t_2d_array & state, int & score )
{
  t_2d_array newState;

  // Add 1
  for ( std::size_t _row = 0; _row < 10; ++_row )
    for ( std::size_t _column = 0; _column < 10; ++_column )
      newState[ _row ][ _column ] = state[ _row ][ _column ] + 1;

  // Flash
  while( is_need_to_flash( newState ) )
  {
    score += flash_array( newState );
  }

  return newState;
}


int DumboOctopus::task_1( const std::string & filename )
{
  t_2d_array state = prepare_input( filename );
  int score { 0 };

  for ( std::size_t _step = 0; _step < 100; ++_step )
    state = simulate_step( state, score );

  return score;
}

bool is_synchronized( const t_2d_array & state )
{
  for ( std::size_t _row = 0; _row < 10; ++_row )
    for ( std::size_t _column = 0; _column < 10; ++_column )
      if ( state[ _row ][ _column ] != 0 )
        return false;

  return true;
}

int DumboOctopus::task_2( const std::string &filename )
{
  t_2d_array state = prepare_input( filename );
  int score { 0 };

  for ( std::size_t _step = 0; _step < 100000; ++_step )
  {
    state = simulate_step( state, score );
    if ( is_synchronized( state ) )
      return _step + 1;
  }

  return -1;
}
