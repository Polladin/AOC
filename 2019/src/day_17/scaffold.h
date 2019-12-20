#pragma once

#include <string>
#include <vector>
#include <queue>

#include "common/common.h"


class Scaffold
{

private:

  using t_field = std::vector< std::vector< long long > >;

public:

  int run_part_1( const std::string & fileName );

  int run_part_2( const std::string & fileName );

private:

  void print_image( const std::vector< long long > & output );

  t_field get_field( const std::string & fileName );

  t_field make_field( const std::vector< long long > & output );

  int calc_intersections( const t_field & field );

  // --------------------- Part 2 -----------------------------------
  
  std::string get_path( const t_field & field );

  t_coord get_start_point( const t_field & field );

  std::pair< char, int > get_next_direction( const t_coord & currentPoint, int currentDirection, const t_field & field );

  int get_stright_path_length( const t_coord & startPoint, int direction, const t_field & field );

  t_coord get_next_point( const t_coord & startPoint, int direction, int len = 1 );

  bool is_point_outbound( const t_coord & point, const t_field & field );

  void add_input_to_que( const std::string & str, std::queue< long long > & que );
};
