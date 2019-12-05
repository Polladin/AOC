#include "wires.h"

#include "common/file_reader.h"
#include "common/common.h"

#include <sstream>
#include <iostream>
#include <algorithm>


int Wires::run_part_1( const std::string & fileName )
{
  // Read and convert input data
  std::vector< Wires::t_wire > inputWires = prepare_input( fileName );

  // Create grid
  auto grid = get_grid();

  // Add the first wire
  add_wire( inputWires[ 0 ], grid, 1 );
  auto intersections = add_wire( inputWires[ 1 ], grid, 2 );

  std::pair< int, int > point = get_nearest_intersection( intersections, X_START_POS, Y_START_POS );
  point.first -= X_START_POS;
  point.second -= Y_START_POS;
  //std::cout << "X: " << point.first << "   Y: " << point.second << std::endl;

  return point.first + point.second;
}


std::vector< Wires::t_wire > Wires::prepare_input( const std::string & inputFile )
{
  // Read the file
  std::vector< std::string > sInputs = FileReader::read_file( inputFile );
  // Result container
  
  std::vector< Wires::t_wire > wires;

  for ( const auto & _wire : sInputs )
  {
    // Container for wire
    t_wire inputWire;
    // Container for a wire part
    std::string inputWirePart;

    // A stream to split vlues by comma
    std::istringstream iss( _wire );
    
    // Read values are splitted by comma
    while ( std::getline( iss, inputWirePart, ',' ) )
      inputWire.emplace_back( inputWirePart[0], std::stoi( inputWirePart.substr( 1 ) ) );

    wires.emplace_back( std::move( inputWire ) );
  }

  return wires;
}



Wires::t_intersections Wires::add_wire( const t_wire & wire, t_grid & grid, int wireNum )
{
  int posX = X_START_POS;
  int posY = Y_START_POS;

  t_intersections intersections;
  t_wire_cells wireCells;

  for ( const auto & _wire_part : wire )
  {
    // Fill the grip with new part of the wire
    t_intersections partIntersections = fill_wire_part( _wire_part, wireCells, posX, posY, grid, wireNum );

    // Copy intersections
    std::copy( partIntersections.begin(), partIntersections.end(), std::back_inserter( intersections ) );

    // Move to the end of the wire part
    std::tie< int, int >( posX, posY ) = get_wire_part_endpoint( _wire_part, posX, posY );
  }

  // print_grid( grid );

  wireCells.sort( compare_pairs );

  grid.emplace_back( std::move( wireCells ) );

  return intersections;
}

Wires::t_intersections Wires::fill_wire_part( const t_wire_part & wirePart, t_wire_cells & wireCells, int posX, int posY, t_grid & grid, int wireNum )
{
  // Create container for intersections
  std::vector< std::pair< int, int > > intersections;

  // Get end position
  std::pair< int, int > endPos = get_wire_part_endpoint( wirePart, posX, posY );

  while ( posX != endPos.first || posY != endPos.second )
  {
    // Get next position
    wire_part_next_pos( wirePart, posX /* out */, posY /* out */ );

    // Don't change start position
    if ( posX == X_START_POS && posY == Y_START_POS )
      continue;
   
    // Is intersection
    if ( is_cell_occupated( posX, posY, grid ) )
      intersections.emplace_back( posX, posY );
    /*if ( grid[ posX ][ posY ] != 0 )
      intersections.emplace_back( posX, posY );*/

    // Fill the cell
    wireCells.emplace_back( posX, posY );
    //grid[ posX ][ posY ] = grid[ posX ][ posY ] == 0 ? wireNum : -1;
  }

  return intersections;
}

std::pair< int, int > Wires::get_wire_part_endpoint( const t_wire_part & wirePart, int posX, int posY )
{
  switch ( wirePart.first )
  {
  case 'L': return std::make_pair( posX - wirePart.second, posY );
  case 'R': return std::make_pair( posX + wirePart.second, posY );
  case 'U': return std::make_pair( posX, posY + wirePart.second );
  case 'D': return std::make_pair( posX, posY - wirePart.second );
  }
  throw "Unrecognized direction.";
}


void Wires::wire_part_next_pos( const t_wire_part & wirePart, int & posX, int & posY )
{
  switch ( wirePart.first )
  {
  case 'L': posX -= 1; break;
  case 'R': posX += 1; break;
  case 'U': posY += 1; break;
  case 'D': posY -= 1; break;
  default:
    throw "Unrecognized direction.";
  }
}



Wires::t_grid Wires::get_grid()
{
  t_grid res;

  //res.resize( GRID_X_SIZE );
  //for ( int xIdx = 0; xIdx < GRID_X_SIZE; ++xIdx )
  //  res[ xIdx ].resize( GRID_Y_SIZE );

  //for ( int xIdx = 0; xIdx < GRID_X_SIZE; ++xIdx )
  //  for ( int yIdx = 0; yIdx < GRID_Y_SIZE; ++yIdx )
  //    res[ xIdx ][ yIdx ] = 0;

  return res;
}

std::pair<int, int> Wires::get_nearest_intersection( t_intersections & intersections, int startX, int startY )
{
  std::sort( intersections.begin(), intersections.end(), 
    [ startX, startY ]( const std::pair< int, int > & lhs, const std::pair< int, int > & rhs )
    { return   ( std::abs( lhs.first - startX ) + std::abs( lhs.second - startY) )
             < ( std::abs( rhs.first - startX ) + std::abs( rhs.second - startY ) ); } );

  return intersections.front();
}

bool Wires::is_cell_occupated( int posX, int posY, t_grid & grid )
{
  std::pair< int, int > point( posX, posY );

  for ( const auto & _wire_cells : grid )
  {
    bool isExist = std::binary_search(  _wire_cells.begin(), _wire_cells.end()
                                      , point
                                      , compare_pairs );

    if ( isExist )
      return true;
  }

  return false;
}


void Wires::print_grid( t_grid & grid )
{
  //for ( int posY = grid[0].size() - 1; posY >= 0; --posY )
  //{
  //  for ( int posX = 0; posX < grid.size(); ++posX )
  //  {
  //    if( posX == X_START_POS && posY == Y_START_POS )
  //      std::cout << 'o';
  //    else if ( grid[ posX ][ posY ] == -1 )
  //      std::cout << 'x';
  //    else if ( grid[ posX ][ posY ] == 0 )
  //      std::cout << '.';
  //    else
  //      std::cout << '-';
  //  }
  //  std::cout << "\n";
  //}
  //std::cout << "################################\n\n";
}
