
#include "bunny_hq.h"

#include "common/file_reader.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <array>


int BunnyHQ::run_part_1( const std::string & fileName )
{
  std::vector< t_move > movements = prepare_input( fileName );

  std::array< int, 2 > endPoint = move_to( movements );

  return std::abs( endPoint[0] ) + std::abs( endPoint[1] );
}

std::vector< BunnyHQ::t_move > BunnyHQ::prepare_input( const std::string & fileName )
{
  std::vector< t_move > res;

  std::vector< std::string > sInputs = FileReader::read_file( fileName );

  // Split by comma
  std::istringstream iss( sInputs[ 0 ] );
  std::string inputMovement;

  while ( std::getline( iss, inputMovement, ',' ) )
  {
    // Remove all whitespaces
    inputMovement.erase( std::remove_if( inputMovement.begin(), inputMovement.end(), std::isspace ), inputMovement.end() );

    // Get move direction and step length
    res.emplace_back( inputMovement[0], std::stoi( inputMovement.substr( 1 ) ) );
  }

  return res;
}

std::array< int, 2 > BunnyHQ::move_to( const std::vector< t_move > & movements )
{
  std::array< int, 2 > endPos{0, 0};
  int coordinate = 0;
  int direction = 1;

  for ( const auto & _move : movements )
  {
    switch ( _move.first )
    {
    case 'L': 
      if ( coordinate == 0 ) 
        direction = -direction;
      break;

    case 'R': 
      if ( coordinate == 1 )
        direction = -direction;
      break;

    default:
      throw "Unrecognized direction";
    }

    coordinate = ( coordinate + 1 ) % 2;
    endPos[ coordinate ] += ( direction * _move.second );
  }

  return endPos;
}
