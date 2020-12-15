//
// Created by alexpall on 16.12.2020.
//

#include "rain_risk.h"

#include <vector>
#include <stdexcept>
#include <iostream>

#include "common/file_reader.h"


using t_move = std::pair< char, int >;
using t_movements = std::vector< t_move >;


t_movements prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  // Create an output array
  t_movements movements;
  movements.reserve( sInput.size() );

  // Read from each line
  for ( auto _line : sInput )
  {
    // Get a direction
    char direction = _line[ 0 ];

    // Get the number
    int number = std::stoi( _line.substr( 1 ) );

    movements.emplace_back( direction, number );
  }

  return movements;
}


static std::vector< std::pair< int, int > > directionsMap =
        { {  0,  1 } /* E */
        , {  1,  0 } /* S */
        , {  0, -1 } /* W */
        , { -1,  0 } /* N */, };

void make_step( std::pair< int, int > & position, int & direction, const t_move & move )
{
  switch( move.first )
  {
    // Absolute direction
    case 'E':
      position.second += move.second;
      break;

    case 'W':
      position.second -= move.second;
      break;

    case 'N':
      position.first -= move.second;
      break;

    case 'S':
      position.first += move.second;
      break;

    // Relative direction
    case 'F':
      position.first  += directionsMap[ direction ].first  * move.second;
      position.second += directionsMap[ direction ].second * move.second;
      break;

    case 'R':
      direction = ( direction + move.second / 90 ) % ( int )directionsMap.size();
      break;

    case 'L':
      direction = ( direction - move.second / 90 + ( int )directionsMap.size() ) % ( int )directionsMap.size();
      break;

    default:
      throw std::invalid_argument( "Wrong inputs" );
  }
}

static std::vector< std::pair< int, int > > rotationMap =
                   // cos      sin
                { {   1,  0 } /*   0 */
                , {   0,  1 } /*  90 */
                , {  -1,  0 } /* 180 */
                , {   0, -1 } /* 270 */, };

void make_step_2( std::pair< int, int > & position, std::pair< int, int > & waypoint, const t_move & move )
{
  std::pair< int, int > newWaypoint;
  int rotationIdx;

  switch( move.first )
  {
    // Absolute direction
    case 'E':
      waypoint.second += move.second;
      break;

    case 'W':
      waypoint.second -= move.second;
      break;

    case 'N':
      waypoint.first -= move.second;
      break;

    case 'S':
      waypoint.first += move.second;
      break;

      // Relative direction
    case 'F':
      position.first  += waypoint.first  * move.second;
      position.second += waypoint.second * move.second;
      break;

    case 'L':
      newWaypoint.first = waypoint.first  * rotationMap[ move.second / 90 ].first
                        - waypoint.second * rotationMap[ move.second / 90 ].second;
      newWaypoint.second = waypoint.first  * rotationMap[ move.second / 90 ].second
                         + waypoint.second * rotationMap[ move.second / 90 ].first;
      waypoint = newWaypoint;
      break;

    case 'R':
      rotationIdx = ( 4 - move.second / 90 ) % 4;
      newWaypoint.first = waypoint.first  * rotationMap[ rotationIdx ].first
                        - waypoint.second * rotationMap[ rotationIdx ].second;
      newWaypoint.second = waypoint.first  * rotationMap[ rotationIdx ].second
                         + waypoint.second * rotationMap[ rotationIdx ].first;
      waypoint = newWaypoint;
      break;

    default:
      throw std::invalid_argument( "Wrong inputs" );
  }
}


int RainRisk::task_1( const std::string & filename )
{
  t_movements movements = prepare_input( filename );

  std::pair< int, int > position;
  int direction { 0 };

  for ( const auto _movement : movements )
  {
    make_step( position, direction, _movement );
  }

  return std::abs( position.first ) + std::abs( position.second );
}


int RainRisk::task_2( const std::string & filename )
{
  t_movements movements = prepare_input( filename );

  std::pair< int, int > position;
  std::pair< int, int > waypoint { -1, 10 };

  for ( const auto _movement : movements )
  {
//    std::cout << "Move " << _movement.first << " " << _movement.second << " pos: " << position.first << " " << position.second << " way: " << waypoint.first << " " << waypoint.second << "\n";
    make_step_2( position, waypoint, _movement );
  }

  return std::abs( position.first ) + std::abs( position.second );
}
