#pragma once

#include <string>
#include <map>

#include "common/common.h"


class PaintingRobots
{
private:

  using t_colors = std::map< t_coord, int, decltype( compare_coords ) >;

public:

  int run_part_1( const std::string & fileName );

  int run_part_2( const std::string & fileName );

private:

  int get_current_color( const t_coord & currentPos, t_colors & colors );

  void change_position( t_coord & currentPos, int & currentDirection, int robotOutDirection );

  void show_paint( const t_colors & colors );

};