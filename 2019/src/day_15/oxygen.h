#pragma once

#include <string>
#include <vector>
#include <map>
#include <queue>

#include "common/common.h"
#include "day_2/computer.h"


class Oxygen
{

private:

  using t_colors = std::map< t_coord, int, decltype( compare_coords ) >;
  using t_back_path = std::map< t_coord, std::vector< int >, decltype( compare_coords ) >;

public:

  int run_part_1( const std::string & fileName );

private:

  int bfs( const t_coord & startCoordinate, std::vector< int > pathToStartNode, std::vector< int > & pathToOxygen, t_coord & oxygenCoordinate );
  bool push_not_visited_nodes( const t_coord & currentNode, t_colors & colors, t_back_path & backPath, std::queue< t_coord > & que );
  void move_robot( const std::vector< int > & directions );

  int visit_node( std::pair< t_coord, int > node );

  int get_color( const t_colors & colors, const t_coord & pos );
  std::vector< std::pair< t_coord, int > > get_neighbors( const t_coord & pos );

private:

  Computer comp;

};