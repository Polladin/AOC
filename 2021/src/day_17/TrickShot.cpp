//
// Created by alexey on 11.01.2022.
//

#include "TrickShot.h"

#include <vector>
#include <regex>
#include <iostream>
#include <set>

#include "common/file_reader.h"

struct Comp
{
  bool operator() ( const std::pair< int, int > & lhs, const std::pair< int, int > & rhs ) const
          { return lhs.first == rhs.first ? lhs.second < rhs.second
                                          : lhs.first < rhs.first;
          };
};

using t_velocity = std::set< std::pair< int, int >, Comp >;

struct Area
{
  Area( int x1, int x2, int y1, int y2 )
    : x{ x1, x2 }
    , y{ y1, y2 }
  {}

  std::pair< int, int > x;
  std::pair< int, int > y;
};


Area prepare_input( const std::string & filename )
{
  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  std::regex word_regex(R"(target area: x=([-]?\d+)..([-]?\d+), y=([-]?\d+)..([-]?\d+))");
  std::smatch pieces_match;
  std::regex_match( sInput[ 0 ], pieces_match, word_regex );

  if ( pieces_match.size() != 5 )
    throw std::invalid_argument( "Must be in format: target area: x=253..280, y=-73..-46" );

  return {   std::stoi( pieces_match[ 1 ] )
           , std::stoi( pieces_match[ 2 ] )
           , std::stoi( pieces_match[ 3 ] )
           , std::stoi( pieces_match[ 4 ] ) };
}


int get_x_length( int velocity, int steps )
{
  int length = 0;

  for ( ; velocity > 0 && steps > 0; --velocity, --steps )
    length += velocity;

  return length;
}

std::vector< int > amount_x_in_area( const std::pair< int, int > velocityRange, const std::pair< int, int > & limits, const int steps )
{
  std::vector< int > velocities;

  for ( int velocity = velocityRange.first; velocity <= velocityRange.second; ++velocity )
  {
    const int length = get_x_length( velocity, steps );

    if ( length >= limits.first && length <= limits.second )
      velocities.push_back( velocity );
  }

  return velocities;
}


std::vector< int > get_y_steps( int velocity, const std::pair< int, int > & limits )
{
  int currentStep { 0 };
  std::vector< int > steps;
  int length { 0 };

  while ( length >= limits.second )
  {
    if ( length <= limits.first )
      steps.push_back( currentStep );

    length += velocity;
    ++currentStep;
    --velocity;
  }

  return steps;
}

int amount_y_in_area( const Area & area )
{
  t_velocity velocities;

  for ( int yVelocity = area.y.first; yVelocity <= -area.y.first; ++yVelocity )
  {
    std::vector< int > steps = get_y_steps( yVelocity, { area.y.second, area.y.first } );

    if ( steps.empty() )
      continue;

    for ( int _step : steps )
    {
      std::vector< int > xVelocities = amount_x_in_area( { 1, area.x.second }, { area.x.first, area.x.second }, _step );

      for ( int _xVelocity : xVelocities )
        velocities.emplace( _xVelocity, yVelocity );
    }
  }

  return velocities.size();
}


int TrickShot::task_1( const std::string & filename )
{
  Area area = prepare_input( filename );

  std::cout << "x=" << area.x.first << ".." << area.x.second << " y=" << area.y.first << ".." << area.y.second << "\n";

  return ( std::abs( area.y.first ) - 1 ) * std::abs( area.y.first ) / 2;
}

int TrickShot::task_2( const std::string &filename )
{
  Area area = prepare_input( filename );

  return amount_y_in_area( area );
}
