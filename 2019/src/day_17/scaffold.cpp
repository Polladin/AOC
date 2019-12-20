#include "scaffold.h"

#include <iostream>

#include "day_2/computer.h"

const static int STOP = -1;
const static int UP    = 0;
const static int DOWN  = 1;
const static int LEFT  = 2;
const static int RIGHT = 3;


int Scaffold::run_part_1( const std::string & fileName )
{
  Computer comp;

  comp.prepare_day_7_part_1( fileName );

  std::queue< long long > input;
  std::vector< long long > output;

  comp.run_day_7_part_1( input, output );

  print_image( output );

  t_field screen = make_field( output );

  return calc_intersections( screen );
}

int Scaffold::run_part_2( const std::string & fileName )
{
  t_field screen = get_field( fileName );

  Computer comp;

  comp.prepare_day_7_part_1( fileName );
  comp.memory[ 0 ] = 2;

  // Find a program
  std::string path = get_path( screen );

  // Run program

  std::cout << "Path: " << path << "\n";

  std::queue< long long > input;
  std::vector< long long > output;

  add_input_to_que( "B,A,B,C,B,A,C,A,C,A", input );
  add_input_to_que( "R,10,R,10,L,4"      , input );
  add_input_to_que( "R,10,R,10,R,6,R,4"  , input );
  add_input_to_que( "R,4,L,4,L,10,L,10"  , input );
  add_input_to_que( "n", input );

  /*for ( int i = 0; i < 10; ++i )
  {*/
    comp.run_day_7_part_1( input, output );

    print_image( output );
  //}

  return output.back();
}

void Scaffold::print_image( const std::vector< long long > & output )
{
  t_field screen = make_field( output );

  for ( int y = 0; y < screen.size(); ++y )
  {
    for ( int x = 0; x < screen[ y ].size(); ++x )
    {
      std::cout << char( screen[ y ][ x ] );
    }
    std::cout << "\n";
  }

  std::cout << "\n";
}

Scaffold::t_field Scaffold::get_field( const std::string & fileName )
{
  Computer comp;

  comp.prepare_day_7_part_1( fileName );

  std::queue< long long > input;
  std::vector< long long > output;

  comp.run_day_7_part_1( input, output );

  print_image( output );

  t_field screen = make_field( output );

  return screen;
}


Scaffold::t_field Scaffold::make_field( const std::vector< long long > & output )
{
  t_field screen;

  int currentLine = 0;
  screen.push_back( std::vector< long long >() );

  for ( auto _el : output )
  {
    if ( _el != 10 )
    {
      screen[ currentLine ].push_back( _el );
      continue;
    }

    // _el == 10
    screen.push_back( std::vector< long long >() );
    ++currentLine;

    screen[ currentLine ].reserve( screen[ 0 ].size() );
  }

  for ( auto & _line : screen )
    if ( _line.size() != screen[ 0 ].size() )
      _line.resize( screen[ 0 ].size(), -1 );

  return screen;
}

int Scaffold::calc_intersections( const t_field & field )
{
  int res = 0;

  std::cout << "Screen size : " << field.size() << " x " << field[ 0 ].size() << "\n";

  for ( int y = 1; y < field.size() - 1; ++y )
  {
    for ( int x = 1; x < field[ y ].size() - 1; ++x )
    {
      if ( field[ y     ][ x     ] == 35 
        && field[ y - 1 ][ x     ] == 35 
        && field[ y + 1 ][ x     ] == 35 
        && field[ y     ][ x - 1 ] == 35 
        && field[ y     ][ x + 1 ] == 35 )
      {
        res += x * y;
        std::cout << "Inter : " << x << ", " << y << "\n";
      }
    }
  }

  return res;
}

std::string Scaffold::get_path( const t_field & field )
{
  std::string res;

  // Find start point
  t_coord currentPoint = get_start_point( field );
  int direction = UP;

  // Char with turn : 'L' / 'R'
  char turnTo;

  std::cout << "Field size : " << field[0].size() << "  " << field.size() << "\n";

  while ( true )
  {
    // Get next direction
    std::tie( turnTo, direction ) = get_next_direction( currentPoint, direction, field );

    if ( direction == STOP )
      break;

    // Get stright path length
    int len = get_stright_path_length( currentPoint, direction, field );

    currentPoint = get_next_point( currentPoint, direction, len );

    // Add command
    if ( res.length() != 0 )
      res += ',';
    res += std::string( "" ) + turnTo + ',' + std::to_string( len );
  }

  return res;
}

t_coord Scaffold::get_start_point( const t_field & field )
{
  for ( int y = 0; y < field.size(); ++y )
    for ( int x = 0; x < field[ y ].size(); ++x )
      if ( field[ y ][ x ] == '^' )
        return{ x, y };

  throw "Start point is not found";
}

std::pair<char, int> Scaffold::get_next_direction( const t_coord & currentPoint, int currentDirection, const t_field & field )
{
  static const std::pair<char, int> endPoint{ 'S', STOP };

  switch ( currentDirection )
  {
  case UP:
  case DOWN:

    if (   !is_point_outbound( { currentPoint.x - 1, currentPoint.y }, field ) 
        && field[ currentPoint.y ][ currentPoint.x - 1 ] == '#' )
      return{ currentDirection == UP ? 'L' : 'R', LEFT };

    if (   !is_point_outbound( { currentPoint.x + 1, currentPoint.y }, field )
        && field[ currentPoint.y ][ currentPoint.x + 1 ] == '#' )
      return{ currentDirection == UP ? 'R' : 'L', RIGHT };

    return endPoint;

  case LEFT:
  case RIGHT:

    if (   !is_point_outbound( { currentPoint.x, currentPoint.y - 1 }, field )
        && field[ currentPoint.y - 1 ][ currentPoint.x ] == '#' )
      return{ currentDirection == LEFT ? 'R' : 'L', UP };

    if (   !is_point_outbound( { currentPoint.x, currentPoint.y + 1 }, field )
        && field[ currentPoint.y + 1 ][ currentPoint.x ] == '#' )
      return{ currentDirection == LEFT ? 'L' : 'R', DOWN };

    return endPoint;
  }

  throw "Unknow direction";
}

int Scaffold::get_stright_path_length( const t_coord & startPoint, int direction, const t_field & field )
{
  int len = 0;
  t_coord point = startPoint;

  point = get_next_point( point, direction );

  while ( !is_point_outbound( point, field ) && field[ point.y ][ point.x ] == '#' )
  {
    ++len;
    
    point = get_next_point( point, direction );
  }

  return len;
}

t_coord Scaffold::get_next_point( const t_coord & startPoint, int direction, int len )
{
  switch ( direction )
  {
  case UP:    return{ startPoint.x      , startPoint.y - len };
  case DOWN:  return{ startPoint.x      , startPoint.y + len };
  case LEFT:  return{ startPoint.x - len, startPoint.y     };
  case RIGHT: return{ startPoint.x + len, startPoint.y     };
  }
}

bool Scaffold::is_point_outbound( const t_coord & point, const t_field & field )
{
  if ( point.x < 0 || point.y < 0 )
    return true;

  if ( point.x >= field[ 0 ].size() || point.y >= field.size() )
    return true;

  return false;
}

void Scaffold::add_input_to_que( const std::string & str, std::queue< long long > & que )
{
  for ( int i = 0; i < str.length(); ++i )
  {
    que.push( long long( str[ i ] ) );
  }

  // push new line
  que.push( 10 );
}
