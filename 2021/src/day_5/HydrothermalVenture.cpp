//
// Created by alexey on 06.12.2021.
//

#include "HydrothermalVenture.h"

#include <vector>
#include <regex>

#include "common/common.h"
#include "common/file_reader.h"

using t_input =  std::vector< std::pair< t_coord, t_coord > >;


static t_input prepare_input( const std::string & filename )
{
  t_input input;

  // Read the file
  std::vector< std::string > sInput = FileReader::read_file( filename );

  const std::regex regexpCoord(R"((\d+),(\d+) -> (\d+),(\d+))" );
  std::smatch regexMatch;

  for ( const auto & _line : sInput )
  {
    // Read coordinated
    if ( !std::regex_match( _line, regexMatch, regexpCoord ) )
      throw std::invalid_argument( "Invalid input data" );

    input.emplace_back(  t_coord( std::stoi( regexMatch[ 1 ] ), std::stoi( regexMatch[ 2 ] ) )
                       , t_coord( std::stoi( regexMatch[ 3 ] ), std::stoi( regexMatch[ 4 ] ) ) );
  }

  return input;
}

struct Limits
{
  int xMin { 0 }, xMax { 0 }, yMin { 0 }, yMax { 0 };
};

static Limits get_max_min( t_input & data )
{
  Limits limits;
  limits.xMin = limits.xMax = data[ 0 ].first.x;
  limits.yMin = limits.yMax = data[ 0 ].first.y;

  for ( const auto & _rule : data )
  {
    // X
    limits.xMax = std::max( std::max( _rule.first.x, _rule.second.x ), limits.xMax );
    limits.xMin = std::min( std::min( _rule.first.x, _rule.second.x ), limits.xMin );

    // Y
    limits.yMax = std::max( std::max( _rule.first.y, _rule.second.y ), limits.yMax );
    limits.yMin = std::min( std::min( _rule.first.y, _rule.second.y ), limits.yMin );
  }

  return limits;
}

static void fill_field( const t_input & inputData, std::vector< std::vector< int > > & field, const Limits & limits )
{
  std::cout << "Size : " << field.size() << " x " << field[0].size() << "\n";
  for ( const auto & inputLine : inputData )
  {
//    std::cout << "Fill for : (" << inputLine.first.x << ", " << inputLine.first.y << ") (" << inputLine.second.x << ". " << inputLine.second.y << ")\n";

    // Only for vertical and horizontal lines
    if (   inputLine.first.x != inputLine.second.x
        && inputLine.first.y != inputLine.second.y )
      continue;

    std::size_t xStart = std::min( inputLine.first.x, inputLine.second.x ) - limits.xMin;
    std::size_t xEnd   = std::max( inputLine.first.x, inputLine.second.x ) - limits.xMin;
    std::size_t yStart = std::min( inputLine.first.y, inputLine.second.y ) - limits.yMin;
    std::size_t yEnd   = std::max( inputLine.first.y, inputLine.second.y ) - limits.yMin;


    for ( std::size_t _y = yStart; _y <= yEnd ; ++_y )
      for ( std::size_t _x = xStart; _x <= xEnd; ++_x )
        {
//        std::cout << "Fill _x=" << _x + limits.xMin << " y=" << _y + limits.yMin << "\n";
        ++field[ _y ][ _x ];
      }
  }
}

static void fill_field_task2( const t_input & inputData, std::vector< std::vector< int > > & field, const Limits & limits )
{
  std::cout << "Size : " << field.size() << " x " << field[0].size() << "\n";
  for ( const auto & inputLine : inputData )
  {
    // Horizontal or Vertical
    if (   inputLine.first.x == inputLine.second.x
        || inputLine.first.y == inputLine.second.y )
    {
      std::size_t xStart = std::min( inputLine.first.x, inputLine.second.x ) - limits.xMin;
      std::size_t xEnd   = std::max( inputLine.first.x, inputLine.second.x ) - limits.xMin;
      std::size_t yStart = std::min( inputLine.first.y, inputLine.second.y ) - limits.yMin;
      std::size_t yEnd   = std::max( inputLine.first.y, inputLine.second.y ) - limits.yMin;


      for ( std::size_t _y = yStart; _y <= yEnd ; ++_y )
        for ( std::size_t _x = xStart; _x <= xEnd; ++_x )
          ++field[ _y ][ _x ];

      continue;
    }

    // Diagonals
    int xStart = inputLine.first.x  - limits.xMin;
    int xEnd   = inputLine.second.x - limits.xMin;
    int yStart = inputLine.first.y  - limits.yMin;
    int yEnd   = inputLine.second.y - limits.yMin;

    int xOffset = ( inputLine.first.x < inputLine.second.x ) ? 1 : -1;
    int yOffset = ( inputLine.first.y < inputLine.second.y ) ? 1 : -1;

    while ( xStart != xEnd + xOffset )
    {
      ++field[ yStart ][ xStart ];
      xStart += xOffset;
      yStart += yOffset;
    }
  }
}

void print_array( const std::vector< std::vector< int > > & field )
{
  for ( const auto _line : field )
  {
    for( auto _elem : _line )
      std::cout << _elem << " ";
    std::cout << "\n";
  }
  std::cout << "\n";
}

int HydrothermalVenture::task_1( const std::string & filename )
{
  // Read input data
  t_input inputData = prepare_input( filename );

  // Get limits
  Limits limits = get_max_min( inputData );

  // Create an array size
  int xLen = limits.xMax - limits.xMin;
  int yLen = limits.yMax - limits.yMin;
  std::vector< std::vector< int > > field ( yLen + 1, std::vector< int >( xLen + 1, 0 ) );

  // Fill the array
  fill_field( inputData, field, limits );

//  print_array( field );

  // Calculate result
  int res { 0 };
  for ( const auto _line : field )
    for ( auto _elem : _line )
      if ( _elem > 1 )
        ++res;

  return res;
}

int HydrothermalVenture::task_2( const std::string &filename )
{
  // Read input data
  t_input inputData = prepare_input( filename );

  // Get limits
  Limits limits = get_max_min( inputData );

  // Create an array size
  int xLen = limits.xMax - limits.xMin;
  int yLen = limits.yMax - limits.yMin;
  std::vector< std::vector< int > > field ( yLen + 1, std::vector< int >( xLen + 1, 0 ) );

  // Fill the array
  fill_field_task2( inputData, field, limits );

//  print_array( field );

  // Calculate result
  int res { 0 };
  for ( const auto _line : field )
    for ( auto _elem : _line )
      if ( _elem > 1 )
        ++res;

  return res;
}
