//
// Created by alexey on 23.12.2020.
//

#include "conway_cubes.h"

#include <vector>
#include <array>
#include <tuple>
#include <iostream>

#include "common/file_reader.h"

const std::size_t SIZE = 30;
const std::size_t ZERO = 10;
using t_field = std::array< std::array< std::array< std::array< int, SIZE >, SIZE >, SIZE >, SIZE >;

void clear_field( t_field & field )
{
  for ( auto & w : field)
    for ( auto & z : w )
     for( auto & y : z )
      for ( auto & x : y )
        x = 0;
}

t_field prepare_input( const std::string & filename )
{
  t_field res;
  clear_field( res );

  std::vector< std::string > sInput = FileReader::read_file( filename );

  for ( std::size_t y = 0; y < sInput.size(); ++y )
  {
    for ( std::size_t x = 0; x < sInput[ y ].length(); ++x )
    {
      if ( sInput[ y ][ x ] == '#' )
        res[ ZERO ][ ZERO ][ y + ZERO ][ x + ZERO ] = 1;
    }
  }

  return res;
}

std::vector< std::tuple< int, int, int, int > > get_offsets()
{
  std::vector< std::tuple< int, int, int, int > > offsets;

  for ( int w : { -1, 0, 1 } )
    for ( int z : { -1, 0, 1 } )
      for ( int y : { -1, 0, 1 } )
        for ( int x : { -1, 0, 1 } )
          if ( w != 0 || x != 0 || y != 0 || z != 0 )
            offsets.emplace_back( w, z, y, x );

  return offsets;
}

int get_neighbors( const t_field & field, int x, int y, int z, int w )
{
  static std::vector< std::tuple< int, int, int, int > > offsets = get_offsets();

  int neighbors { 0 };

  for ( const auto & _offset : offsets )
    neighbors += field[ w + std::get< 0 >( _offset ) ][ z + std::get< 1 >( _offset ) ][ y + std::get< 2 >( _offset ) ][ x + std::get< 3 >( _offset ) ];

//  if ( neighbors > 0 )
//    std::cout << "x: " << x << " y: " << y << " z:" << z << std::endl;
  return neighbors;
}

t_field make_step( const t_field & field )
{
  t_field newField;
  clear_field( newField );

//  for( std::size_t y = ZERO - 2; y < ZERO + 8; ++y )
//  {
//    for( std::size_t x = ZERO - 2; x < ZERO + 8; ++x )
//    {
//      std::cout << field[ ZERO ][ y ][ x ];
//    }
//    std::cout << std::endl;
//  }
//  std::cout << std::endl;

  for( std::size_t w = 1; w < SIZE - 1; ++w )
  {
    for( std::size_t z = 1; z < SIZE - 1; ++z )
    {
      for( std::size_t y = 1; y < SIZE - 1; ++y )
      {
        for( std::size_t x = 1; x < SIZE - 1; ++x )
        {
          int neighbors = get_neighbors( field, x, y, z, w );

          if(   ( field[ w ][ z ][ y ][ x ] == 1 && ( neighbors == 2 || neighbors == 3 ))
             || ( field[ w ][ z ][ y ][ x ] == 0 && neighbors == 3 ))
          {
            newField[ w ][ z ][ y ][ x ] = 1;
          }
        }
      }
    }
  }

  return newField;
}

int get_cube_sum( const t_field & field )
{
  int res { 0 };

  for ( auto & w : field )
    for ( auto & z : w )
      for( auto & y : z )
        for ( auto & x : y )
          res += x;

  return res;
}

int ConwayCubes::task_1( const std::string &filename )
{
  t_field field = prepare_input( filename );

  for ( int i = 0; i < 6; ++i )
    field = make_step( field );

  return get_cube_sum( field );
}
