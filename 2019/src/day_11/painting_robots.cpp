
#include "painting_robots.h"

#include "day_2/computer.h"

#include <iostream>
#include <array>
#include <fstream>


int PaintingRobots::run_part_1( const std::string & fileName )
{
  // Robot brain
  Computer comp;

  // Initialize brain
  comp.prepare_day_7_part_1( fileName );

  // Input / Output 
  std::queue< long long > input;
  std::vector< long long > output;

  // Initialize current coordinates and direction
  t_coord currentPos { 0, 0 };
  int direction = 0; /* 0 : UP; 1 : RIGHT; 2 : DOWN; 3 : LEFT */

  // Field colors
  t_colors colors( compare_coords );

  bool isHalted = false;

  while ( !isHalted )
  {
    // Clear input
    input = std::queue< long long >();

    // Initialize input
    int cellColor = get_current_color( currentPos, colors );
    input.push( cellColor );

    // Run program
    isHalted = comp.run_day_7_part_1( input, output );

    if ( isHalted )
      break;

    // Change color of current cell
    colors[ currentPos ] = output[ 0 ];

    // Change current position
    change_position( currentPos, direction, output[ 1 ] );
  }

  show_paint( colors );

  return colors.size();
}

int PaintingRobots::run_part_2( const std::string & fileName )
{
  // Robot brain
  Computer comp;

  // Initialize brain
  comp.prepare_day_7_part_1( fileName );

  // Input / Output 
  std::queue< long long > input;
  std::vector< long long > output;

  // Initialize current coordinates and direction
  t_coord currentPos{ 0, 0 };
  int direction = 0; /* 0 : UP; 1 : RIGHT; 2 : DOWN; 3 : LEFT */

  // Field colors
  t_colors colors( compare_coords );
  colors[ currentPos ] = 1;

  bool isHalted = false;

  while ( !isHalted )
  {
    // Clear input
    input = std::queue< long long >();

    // Initialize input
    int cellColor = get_current_color( currentPos, colors );
    input.push( cellColor );

    // Run program
    isHalted = comp.run_day_7_part_1( input, output );

    if ( isHalted )
      break;

    // Change color of current cell
    colors[ currentPos ] = output[ 0 ];

    // Change current position
    change_position( currentPos, direction, output[ 1 ] );
  }

  show_paint( colors );

  return colors.size();
}

int PaintingRobots::get_current_color( const t_coord & currentPos, t_colors & colors )
{
  auto it = colors.find( currentPos );
  if ( it != colors.end() )
    return it->second;

  return 0; // Black
}

void PaintingRobots::change_position( t_coord & currentPos, int & currentDirection, int robotOutDirection )
{
  // 0 - means it should turn left 90 degrees
  // 1 - means it should turn right 90 degrees

  currentDirection = ( 4 + currentDirection + ( robotOutDirection == 0 ? -1 : 1 ) ) % 4;

  switch ( currentDirection )
  {
  case 0: // 0 : UP
    ++currentPos.y;
    break;

  case 1: // 1 : RIGHT
    ++currentPos.x;
    break;

  case 2: // 2 : DOWN
    --currentPos.y;
    break;

  case 3: // 3 : LEFT 
    --currentPos.x;
    break;
  }

}

void PaintingRobots::show_paint( const t_colors & colors )
{
  int maxX{ 0 }, maxY{ 0 };
  int minX{ 0 }, minY{ 0 };

  // Find max min coordinates;
  for ( const auto & _coord : colors )
  {
    maxX = std::max( maxX, _coord.first.x );
    maxY = std::max( maxY, _coord.first.y );
    
    minX = std::min( minX, _coord.first.x );
    minY = std::min( minY, _coord.first.y );
  }

  // Create Field
  std::vector< std::vector< int > > field( maxY - minY + 1, std::vector< int >( maxX - minX + 1, 0 ) );

  // Filling cells
  for ( auto & _coord : colors )
  {
    field[ _coord.first.y - minY ][ _coord.first.x - minX ] = _coord.second;
  }

  std::ofstream ofs( "img.txt" );

  // Print
  for ( int y = field.size() - 1; y >= 0 ; --y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
      std::cout << ( field[ y ][ x ] == 0 ? ' ' : 'x' );
    std::cout << "\n";
  }

  for ( int y = field.size() - 1; y >= 0; --y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
      ofs << ( field[ y ][ x ] == 0 ? ' ' : 'x' );
    ofs << "\n";
  }

  std::cout << "\n\n";
}

