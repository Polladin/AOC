#pragma once

#include <string>
#include <vector>
#include <array>
#include <list>


class Wires
{
private:

  //static const size_t GRID_X_SIZE = 50000;
  //static const size_t GRID_Y_SIZE = 50000;
  static const size_t X_START_POS = 0;
  static const size_t Y_START_POS = 0;

  using t_wire_part = std::pair< char, int >;
  using t_wire      = std::vector< t_wire_part >;

  using t_wire_cells = std::list< std::pair< int, int > >;
  using t_grid      = std::vector< t_wire_cells >;

  using t_intersections = std::vector< std::pair< int, int > >;

public:

  int run_part_1( const std::string & fileName );

private:

  std::vector< t_wire > prepare_input( const std::string & inputFile );

  // Add Wire
  t_intersections add_wire( const t_wire & wire, t_grid & grid, int wireNum );
  
  // Add Wire Part ( return intersection points )
  t_intersections fill_wire_part( const t_wire_part & wirePart, t_wire_cells & wireCells, int posX, int posY, t_grid & grid, int wireNum );
  
  std::pair< int, int > get_wire_part_endpoint( const t_wire_part & wirePart, int posX, int posY );

  void wire_part_next_pos( const t_wire_part & wirePart, int & posX, int & posY );

  // Create GRID
  t_grid get_grid();

  // get nearest intersections
  std::pair< int, int > get_nearest_intersection( t_intersections & intersections, int startX = 0, int startY = 0 );

  // Is Ocuppated cell
  bool is_cell_occupated( int posX, int posY, t_grid & grid );

  // Print the grid
  void print_grid( t_grid & grid );

};