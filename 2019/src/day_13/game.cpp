#include "game.h"

#include "day_2/computer.h"

#include <iostream>


int Game::run_part_1( const std::string & fileName )
{
  Computer comp;

  comp.prepare_day_7_part_1( fileName );

  std::queue< long long > in;
  std::vector< long long > out;

  comp.run_day_7_part_1( in, out );

  int res = 0;
  for ( int i = 2; i < out.size(); i += 3 )
    res += ( out[ i ] == 2 ) ? 1 : 0;

  print_field( out );

  return res;
}


int Game::run_part_2( const std::string & fileName )
{
  Computer comp;

  comp.prepare_day_7_part_1( fileName );
  comp.memory[ 0 ] = 2;

  std::queue< long long > in;
  std::vector< long long > out;

  bool isHalted{ false };
  t_field field;

  isHalted = comp.run_day_7_part_1( in, out );;

  set_field( out, field );

  while ( !isHalted )
  {
    // Print field
    print_field( field );

    // Prepare input;
    in = std::queue< long long >();
    in.push( ball.first == paddle.first ? 0 : ( ball.first > paddle.first ? 1 : - 1) );

    // Run program
    isHalted = comp.run_day_7_part_1( in, out );
    apply_step( out, field );

    for ( auto _el : out )
      std::cout << _el << " ";
    std::cout << "\n";

  }

  return 0;
}


void Game::print_field( const std::vector< long long > & gameOutput )
{
  std::vector< t_cell > coords;

  for ( int i = 0; i < gameOutput.size(); i += 3 )
    coords.emplace_back( gameOutput[ i ], gameOutput[ i + 1 ], gameOutput[ i + 2 ] );

  auto maxCoords = get_max_coords( coords );

  for ( int y = 0; y <= maxCoords.second; ++y )
  {
    for ( int x = 0; x <= maxCoords.first; ++x )
      print_symbol(  get_val( coords, x, y ) );

    std::cout << "\n";
  }
  std::cout << "\n\n";

}

void Game::print_field( const t_field & field )
{
  for ( int y = 0; y < field.size(); ++y )
  {
    for ( int x = 0; x < field[ y ].size(); ++x )
      print_symbol( field[ y ][ x ] );

    std::cout << "\n";
  }
  std::cout << "\n\n";
}

void Game::print_symbol( int val )
{
  switch ( val )
  {
  case -1:
    std::cout << "x";
    break;

  case 0:
    std::cout << ".";
    break;

  case 1:
    std::cout << "-";
    break;

  case 2:
    std::cout << "u";
    break;

  case 3:
    std::cout << "_";
    break;

  case 4:
    std::cout << "o";
    break;
  default:
    throw "Somthing wrong";
  }
}

void Game::set_field( const std::vector<long long>& gameOutput, t_field & field )
{
  std::vector< t_cell > coords;

  for ( int i = 0; i < gameOutput.size(); i += 3 )
  {
    coords.emplace_back( gameOutput[ i ], gameOutput[ i + 1 ], gameOutput[ i + 2 ] );

    if ( gameOutput[ i + 2 ] == 4 )
      ball = std::make_pair( gameOutput[ i ], gameOutput[ i + 1 ] );
    if ( gameOutput[ i + 2 ] == 3 )
      paddle = std::make_pair( gameOutput[ i ], gameOutput[ i + 1 ] );
  }

  auto maxCoords = get_max_coords( coords );

  // Resize field;
  field.resize( maxCoords.second + 1 );
  for ( int idx = 0; idx < field.size(); ++idx )
    field[ idx ].resize( maxCoords.first + 1 );

  for ( int y = 0; y <= maxCoords.second; ++y )
    for ( int x = 0; x <= maxCoords.first; ++x )
      field[ y ][ x ] = get_val( coords, x, y );
}

std::pair<int, int> Game::get_max_coords( const std::vector< t_cell >& coords )
{
  int maxX = coords[ 0 ].x;
  int maxY = coords[ 0 ].y;
  
  for ( const auto & _cell : coords )
  {
    maxX = std::max( maxX, _cell.x );
    maxY = std::max( maxY, _cell.y );
  }

  return { maxX, maxY };
}

int Game::get_val( const std::vector< t_cell >& coords, int x, int y )
{
  for ( const auto _cell : coords )
    if ( _cell.x == x && _cell.y == y )
      return _cell.val;

  return -1;
}

void Game::apply_step( const std::vector<long long>& gameOutput, t_field & field )
{
  for ( int i = 0; i < gameOutput.size(); i += 3 )
  {
    if ( gameOutput[ i ] == -1 && gameOutput[ i + 1 ] == 0 )
    {
      score = gameOutput[ i + 2 ];
      continue;
    }

    // Ball
    if ( gameOutput[ i + 2 ] == 4 )
    {
      ballDirection = ball.first < gameOutput[ i ] ? 1 : -1;

      ball = std::make_pair( gameOutput[ i ], gameOutput[ i + 1 ] );
    }
    
    // Paddle
    if ( gameOutput[ i + 2 ] == 3 )
      paddle = std::make_pair( gameOutput[ i ], gameOutput[ i + 1 ] );

    field[ gameOutput[ i + 1 ] ][ gameOutput[ i ] ] = gameOutput[ i + 2 ];
  }
}

