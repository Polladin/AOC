//
// Created by alexey on 17.12.2021.
//

#include "SmokeBasin.h"

#include <vector>
#include <iostream>

#include "common/file_reader.h"
#include "common/common.h"

using t_2d_array = std::vector< std::vector< int > >;

t_2d_array prepare_input( const std::string & filename )
{
  t_2d_array res;

  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  for( const auto & _line : sInput )
  {
    // Create a container for a line
    std::vector< int > numLine;
    numLine.reserve( _line.size() );

    // Fill the line
    for ( auto _sNum : _line )
      numLine.push_back( _sNum - '0' );

    // Add the line to result array
    res.push_back( std::move( numLine ) );
  }

  return res;
}

bool is_minimum( const t_2d_array & map, const int posX, const int posY )
{
  static const std::vector< std::vector< int > > offsets = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
  const int currentValue = map[ posY ][ posX ];

  for ( const auto & _coords : offsets )
  {
    int newPosX = posX + _coords[0];
    int newPosY = posY + _coords[1];
    if (   newPosX < 0 || newPosY < 0
        || newPosX >= map[0].size() || newPosY >= map.size() )
    {
      continue;
    }

    if ( map[ newPosY ][ newPosX ] <= currentValue )
      return false;
  }

  return true;
}

int SmokeBasin::task_1( const std::string & filename )
{
  int res { 0 };

  t_2d_array input = prepare_input( filename );

  for ( int posY = 0; posY < input.size(); ++posY )
  {
    for( int posX = 0; posX < input[ 0 ].size(); ++posX )
    {
      if ( is_minimum( input, posX, posY ) )
      {
        res += ( 1 + input[ posY ][ posX ] );
//        std::cout << "Find min for " << posX << ":" << posY << " res: " << res << "\n";
      }
    }
  }

  return res;
}


int get_basin_size( const t_2d_array & map, const int posX, const int posY, t_2d_array & mark )
{
  static const std::vector< std::vector< int > > offsets = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
  const int currentValue = map[ posY ][ posX ];
  mark[ posY ][ posX ] = 1;
  int res { 1 };

  for ( const auto & _coords : offsets )
  {
    int newPosX = posX + _coords[ 0 ];
    int newPosY = posY + _coords[ 1 ];
    if(    newPosX < 0 || newPosY < 0
        || newPosX >= map[ 0 ].size() || newPosY >= map.size())
    {
      continue;
    }

    if ( mark[ newPosY ][ newPosX ] == 1 )
      continue;

    if (  map[ newPosY ][ newPosX ] != 9 )
    {
      res += get_basin_size( map, newPosX, newPosY, mark );
    }
  }

  return res;
}

int SmokeBasin::task_2( const std::string &filename )
{
  t_2d_array input = prepare_input( filename );
  t_2d_array mark( input.size(), std::vector< int >( input[ 0 ].size(), 0 ) );

  std::vector< int > res;

  for ( int posY = 0; posY < input.size(); ++posY )
    for( int posX = 0; posX < input[ 0 ].size(); ++posX )
      if ( is_minimum( input, posX, posY ) )
      {
//        t_2d_array mark( input.size(), std::vector< int >( input[ 0 ].size(), 0 ) );
        res.push_back( get_basin_size( input, posX, posY, mark ) );
//        std::cout << "Find min for " << posX << ":" << posY << " res: " << res.back() << "\n";
      }

  std::sort( res.begin(), res.end() );

  return res[ res.size() - 1 ] * res[ res.size() - 2 ] * res[ res.size() - 3 ];
}
